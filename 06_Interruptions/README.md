# Les interruptions 

Une interruption est un processus qui est déclenché de manière asynchrone par un événement extérieur, qui interrompt momentanément l’exécution du code en cours, pour exécuter du code plus critique.

Les interruptions permettent de détecter un événement en temps réel tout en laissant le processeur du microcontrôleur faire d’autres tâches. Ainsi le fonctionnement d’une interruption est le suivant :

 -  → Détection d’un événement
 -  → Interruption du programme principal 
 - → Exécution du code de l’interruption 
 - → Le programme principal reprend là où il s’est arrêté.

# Détecter l’interruption 

`attachInterrupt(GPIOPin, fonction_ISR, Mode);`

Avec `Mode` , le mode de détection qui peut être `LOW` , `HIGH` , `RISING` , `FALLING` ou `CHANGE`

# La Fonction ISR
La routine de service d’interruption doit être une fonction qui renvoie void 
et ne prend aucun argument. Il est conseillé d’ajouter le flag `IRAM_ATTR` pour que le code de la fonction soit stocké dans la RAM (et non pas dans la Flash), afin que la fonction s’exécute plus rapidement. 

Il faut garder en tête que la fonction associée à une interruption doit s’exécuter le plus rapidement possible pour ne pas perturber le programme principal. Le code doit être le plus concis possible. On ne peut pas utiliser la fonction `delay()` ni `Serial.println()` avec une interruption. On peut néanmoins afficher des messages dans le moniteur série en remplaçant `Serial.println()` par `ets_printf()` qui est compatible avec les interruptions.

# Exemple
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

