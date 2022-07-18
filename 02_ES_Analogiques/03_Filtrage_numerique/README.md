#  Les filtres RII

## Introduction
Les filtres à **réponse impulsionnelle infinie** (RII) sont utiles pour  les applications de mesure avec capteur, qui nécessitent la suppression du bruit de mesure et l'annulation de composants indésirables, tels que les interférences de ligne électrique.
Les filtres RII sont généralement choisis pour les applications où la phase linéaire n’est pas trop importante et où **la mémoire est limitée**.

La classe **Filter** met en œuvre un filtre biquad IIR sur un esp32,  les calculs sont  effectués sur des variable en virgule flottante.

#### Avantages du filtre RII
-   Peut être utilisé pour imiter les caractéristiques des filtres analogiques en utilisant des transformations de mappage dans le plan p-z
- Faible empreinte de mise en œuvre : nécessite moins de coefficients et de mémoire que les filtres FIR

#### Inconvénients
-   Caractéristiques de phase non linéaires.
-   Moins stables numériquement que leurs homologues RIF (réponse impulsionnelle finie), en raison des chemins de rétroaction.

## Définition

On peut écrire la fonction de transfert comme un rapport de deux polynômes.

 - Les **pôles** sont les racines du dénominateur.
 - Les **zéros** sont les  racines du numérateur
 - La **fréquence de Nyquist** est la moitié de la fréquence
   d'échantillonnage.
 - La fréquence de coupure (fc) est proportionnelle à la fréquence de Nyquist.

L’équation peut être écrite en termes d’un nombre fini de **pôles  p**  et de **zéros  q**, comme défini par l’équation de différence linéaire à coefficient constant donnée par:

![Equation de recurrence](/02_ES_Analogiques/03_Filtrage_numerique/documentation/equationReccurence.png)


où  a(k)  et  b(k)  sont les coefficients polynomiaux du dénominateur et du numérateur du filtre, dont les racines sont respectivement égales aux  **pôles**  et aux  **zéros**  du filtre. Ainsi, une relation entre l’équation de différence et la transformée en z (fonction de transfert) peut donc être définie en utilisant la propriété de retard de la transformée en z telle que,

![Equation de recurrence](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/equationZ.png)


Comme on le voit, la  **fonction de transfert**  est une représentation du filtre dans le domaine fréquentiel.

les **pôles** agissent sur les **données de sortie**, et les **zéros** sur les **données d’entrée**. Puisque les pôles agissent sur les données de sortie et affectent la stabilité, il est essentiel que leurs rayons **restent à l’intérieur du cercle unitaire** (c’est-à-dire <1) pour la stabilité. Les rayons des zéros sont moins critiques, car ils n’affectent pas la stabilité du filtre.

## Filtre biquad IIR

L'implémentation du filtre IIR proposée ici est dite **biquad** , car la fonction de transfert a **deux pôles** et **deux zéros**, comme illustré  dans la figure ci dessous.

![filtre IIR biquad](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/filtreBiquad.png)

Ce qui nous donne l'équation de récurrence :

![equation biquad](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/reccursive_equation.png)

## Implémentation (C++)

L'implémentation du filtrage en temps réel, sur un microcontrôleur ESP32, pose des problèmes spécifiques liés aux ressources disponibles sur ce type d'unité (quantité de mémoire, vitesse de calcul, calculs en virgule flottante). 

Les coefficients des polynômes sont enregistrés dans les tableaux a et b. Les coefficients sont réels. 3 coefficients bn et 3 coefficients an  (a0  = 1)
```cpp
float a[3]; // tableau des coefficients a coefficients (zéros)
float b[3]; // tableau des coefficients b coefficients (pôles)
```
Pour faire le calcul, on doit mémoriser xn-2 xn-1 yn-1 yn-2. On dit que cette réalisation nécessite des variables d'état. D'une manière générale, le nombre de variables d'état est égal au nombre de bloc z-1.
Les variables d'états x et y sont enregistrées dans des tableaux.
```cpp
float x[TAILLE_TAMPON]; // tampon pour les x_n
float y[TAILLE_TAMPON]; // tampon pour les y_n
```
Les échantillons sont prélevés à intervalle de temps régulier (la période d'échantillonnage Te), sous le contrôle d'un timer. 
```cpp
timer = timerBegin(0, 80, true); // Configuration du timer0 en micro seconde 

timerAttachInterrupt(timer, Filter::marshall, true); // Attache une fonction a l'interuption provoquée par le timer

timerAlarmWrite(timer, 1000000 / splFreq, true); // Configuration de la période d'échantillonage en micro seconde

timerAlarmEnable(timer); // Lancement du timer
```
Le timer déclenche à intervalle de temps régulier une interruption qui lance l’exécution de la fonction statique **marshall**. Cette fonction est rattachée à la méthode **interuption()** grace au pointeur **anchor**.
La fonction **interruption()** doit effectuer les calculs en virgule flottante sur 32 bits, et la durée des calculs ne doit pas dépasser la période d'échantillonnage. 
```cpp
void IRAM_ATTR Filter::interuption() {

xthal_set_cpenable(1); // enable FPU
xthal_save_cp0(cp0_regs); // Save FPU registers

x[n] = adc1_get_raw(adc1Channel) -2047; // Lecture de la valeur sur adc1

// Calcul de l'équation de récurrence filtre IIR

y[n] = b[0] * x[ n];
y[n] += b[1] * x[(n - 1) & MASQUE_TAMPON];
y[n] += b[2] * x[(n - 2) & MASQUE_TAMPON];
y[n] -= a[1] * y[(n - 1) & MASQUE_TAMPON];
y[n] -= a[2] * y[(n - 2) & MASQUE_TAMPON];

dac_output_voltage(dacChannel, (y[n] + 2047) / 16); //envoi de la valeur entière vers le dac

n = (n + 1) & MASQUE_TAMPON; // incrémentation circulaire de n

xthal_restore_cp0(cp0_regs); // Restore FPU
xthal_set_cpenable(0); // and turn it back off
}
```
Le signal d'entrée analogique est compris entre 0 et 3V avec un offset de 1.5V . La conversion d'entrée se fait sur 12 bits (valeur numérique comprise de 0 à 4095).
La valeur de l'offset (2047) est retirée avant les calculs. La composante continue du signal se mesure donc par rapport à l'offset de 1.5V.

En fin de chaîne, une conversion numérique-analogique (CNA) est effectuée  avec une résolution 8 bits. la valeur de l'offset est ajouté et la valeur obtenue est divisée par 16. (décalage de 4 bits).
Le signal analogique de sortie est donc lui aussi compris entre 0 et 3V avec un offset de 1.5V.

## Calcul des coefficients

Une feuille de calcul excel est proposée pour calculer les coefficients du biquad et obtenir le diagramme de bode.
Il existe également une calculatrice en ligne  qui permet d'obtenir les mêmes valeurs.
https://www.earlevel.com/main/2021/09/02/biquad-calculator-v3/
Attention sur la calculatrice en ligne les notations a et b sont inversées.

### 1 Exemple de calcul pour un filtre passe bas (LPF)

 - Fréquence d'échantillonnage (Hz) : fs = **5000**
 - Fréquence de coupure Fc (Hz) : fc = **50**
 - Q :  1/sqrt(2) = **0.707**
 - Gain : **0 dB**
 
```cpp
float a[3] = { 1.0 , -1.91118 , 0.91496 };
float b[3] = { 0.00094 , 0.00189 , 0.00094 };
```
 - **w0** = 2 * pi (fc/fs)
 - **alpha** = sin( w0) / (2* Q)
 - **a0** = 1 + alpha
 - **a[1]** = ( -2 * cos(w0)) / a0
 - **a[2]** = (1-alpha) / a0
 - **b[0]** = ((1 - cos(w0)) / 2) / a0
 - **b[1]** = (1- cos(w0) / a0
 - **b[2]** = ((1 - cos(w0)) / 2) / a0

Diagramme de  Bode :

![filtre lpf](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/filtre_lpf.png)

### 2 Exemple de calcul pour un filtre passe haut (HPF)


 - Fréquence d'échantillonnage (Hz) : fs = **5000**
 - Fréquence de coupure Fc (Hz) : fc = **500**
 - Q :  1/sqrt(2) = **0.707**
 - Gain : **0 dB**

```cpp
float a[3] = { 1.0 , -1.14293 , 0.41274 };
float b[3] = { 0.63892 , -1.27783 , 0.63892 };
```

 - **w0** = 2 * pi (fc/fs)
 - **alpha** = sin( w0) / (2* Q)
 - **a0** = 1 + alpha
 - **a[1]** = ( -2 * cos(w0)) / a0
 - **a[2]** = (1 - alpha) / a0
 - **b[0]** = ((1 + cos(w0)) / 2) / a0
 - **b[1]** = (-1 - cos(w0)) / a0
 - **b[2]** = ((1 + cos(w0)) / 2) / a0

Diagramme de  Bode :

![filtre hpf](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/filtre_hpf.png)

### 3 Exemple de calcul pour un filtre coupe bande (notch)

- Fréquence d'échantillonnage (Hz) : fs = **5000**
 - Fréquence  centrale Fc (Hz) : fc = **50**
 - Q :   = **1**
 - Gain : **0 dB**
 
 ```cpp
float a[3] = { 1.0 , -1.93529 , 0.93912 };
float b[3] = { 0.96956 , -1.93529 , 0.96956 };
```

 - **w0** = 2 * pi (fc/fs)
 - **alpha** = sin( w0) / (2* Q)
 - **a0** = 1 + alpha
 - **a[1]** = (-2.0 * cos(w0)) / a0 
 - **a[2]** = (1 - alpha) / a0
 - **b[0]** = 1  / a0
 - **b[1]** = (-2.0 * cos(w0)) / a0
 - **b[2]** = 1  / a0
 
Diagramme de  Bode :
![filtre notch](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/filtre_notch.png)

### 3 Calcul pour un filtre peak 

- Fréquence d'échantillonnage (Hz) : fs = **5000**
 - Fréquence  centrale Fc (Hz) : fc = **50**
 - Q :   = **2**
 - Gain : **6 dB**
 ```cpp
float a[3] = { 1.0 , -1.97412 , 0.97802 };
float b[3] = { 1.01094 , -1.97412 , 0.96708 };
```

Diagramme de  Bode :
![filtre peak](/02_ES_Analogiques/03_Filtrage_numerique/testFiltre/documentation/filtre_peak.png)
