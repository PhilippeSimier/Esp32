# Les interruptions 

Une interruption est un processus qui est déclenché de manière asynchrone par un événement extérieur. Elle interrompt momentanément l’exécution du code en cours, pour exécuter du code plus critique.

Les interruptions permettent de détecter un événement en temps réel tout en laissant le processeur du microcontrôleur faire d’autres tâches. Ainsi le fonctionnement d’une interruption est le suivant :

 - → Détection d’un événement
 - → Interruption du programme principal 
 - → Exécution du code de l’interruption ISR
 - → Le programme principal reprend là où il s’est arrêté.

# Détecter l’interruption 

`attachInterrupt(GPIOPin, fonction_ISR, Mode);`

Avec `Mode` , le mode de détection qui peut être `LOW` , `HIGH` , `RISING` , `FALLING` ou `CHANGE`

La **fonction_ISR** nécessite une fonction de rappel statique de type `void(*)()`
il n'est donc pas possible d'appeler une méthode d'une classe `void(*)(*)`, en raison de son argument implicite this.

Pour appeler une méthode statique d'une classe vous devez utiliser 
`void attachInterruptArg(uint8_t pin, void (*)(void*), void * arg, int mode);`
La méthode ISR reste **statique**,  mais cette fois elle peut recevoir un argument qui peut être un pointeur sur un objet de la classe. Elle peut donc accéder aux attributs de l'objet pointé. La classe Compteur  illustre cette possibilité. 

# La Fonction ISR
La routine de service d’interruption doit être une fonction statique qui renvoie void et ne prend aucun argument ou un argument pointeur générique `void*`. Il est conseillé d’ajouter le flag `IRAM_ATTR` pour que le code de la fonction soit stocké dans la RAM (et non pas dans la Flash), afin que la fonction s’exécute plus rapidement. 

Il faut garder en tête que la fonction associée à une interruption doit s’exécuter le plus rapidement possible pour ne pas perturber le programme principal. Le code doit être le plus concis possible. 

On ne peut pas utiliser la fonction `delay()` ni `Serial.println()` avec une interruption. On peut néanmoins afficher des messages dans le moniteur série en remplaçant `Serial.println()` par `ets_printf()` qui est compatible avec les interruptions.

Seules les routines de service d'interruption de priorité la plus basse (c'est-à-dire le niveau 1) peuvent utiliser `float`, les interruptions de priorité supérieure ne prennent pas en charge l'utilisation du FPU.
Le code suivant permet de travailler avec des variables à virgule flottante (type float) dans une ISR. le code enregistre l'état des registres du  FPU au début de la fonction ISR et les restaure à la fin.
```cpp
uint32_t cp0_regs[18];

void IRAM_ATTR Filter::interuption() {
    // Enter Critical
    portENTER_CRITICAL_ISR(&afeCriticalMutex);
    xthal_set_cpenable(1); // enable FPU
	xthal_save_cp0(cp0_regs); // Save FPU registers

	// Travailler avec FPU

	xthal_restore_cp0(cp0_regs); // Restore FPU
	xthal_set_cpenable(0); // and turn it back off
	// Exit critical
    portEXIT_CRITICAL_ISR(&afeCriticalMutex);
}	
```

# Exemple simple avec des fonctions
```cpp
void IRAM_ATTR fonction_ISR() {
    ets_printf("Boutton pressé\n");
    // Code de la fonction
}

void setup() {
    Serial.begin(115200);
    pinMode(33, INPUT_PULLUP);
    attachInterrupt(33, fonction_ISR, FALLING);
}

void loop() {
}
```
# Autre exemple  dans une classe
Nous souhaitons écrire une classe pour compter des impulsions sur une broche GPIO.  
Déclaration de la classe Compteur  **Compteur.h** 
La méthode isr doit toujours être statique toutefois elle reçoit un argument void * 
 ```cpp
 #include <Arduino.h>
#include <esp32-hal-gpio.h>

class Compteur {
    
public:
    Compteur(uint8_t sensePin, int _debounce = 200);
    int getValue(void);
    void reset(void);

private:
            
    static IRAM_ATTR void isr(void * arg);            
    int lastMillis;
    int debounce;
    volatile int nb;    
};
 ```

 ```cpp
 #include "Compteur.h"
// Le constructeur
Compteur::Compteur(uint8_t sensePin, int _debounce) :
lastMillis(0),
debounce(_debounce),        
nb(0)       
{ 
    pinMode(sensePin, INPUT_PULLUP);  
    attachInterruptArg(sensePin, Compteur::isr, this, FALLING);
}
// La méthode statique ISR 
void IRAM_ATTR Compteur::isr(void * arg) {
    Compteur* pt = static_cast<Compteur*>(arg);  // cast le pointeur générique en pointeur sur Compteur
    if (millis() - pt->lastMillis > pt->debounce) { //Software anti-rebond
        ets_printf("triggered\r\n");
        pt->nb++;
    }
    pt->lastMillis = millis();
}

int Compteur::getValue(void) {
    return this->nb;
}
 ```
 Le programme principal
 ```cpp
 #include <Arduino.h>
#include <Compteur.h>

Compteur C1(33, 250);
Compteur C2(13, 250);

void setup() {
    Serial.begin(115200);   
}

void loop() {
    
    Serial.printf("compteur : %d\r\n", C1.getValue());
    Serial.printf("compteur : %d\r\n", C2.getValue());
    delay(10000);
}
 ```
 
