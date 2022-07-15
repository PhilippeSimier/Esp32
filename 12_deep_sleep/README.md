## Économiser de l’énergie 

L’ESP32 possède un mode d’économie d’énergie appelé **Deep Sleep** qui permet « d’endormir l’ESP32 ».  Pendant ce mode, l’ESP32 peut effectuer des tâches simples et se faire réveiller pour effectuer des tâches plus complexes.

Ce mode d’économie d’énergie est utile quand l’ESP32 est alimenté par batterie et qu'il « travaille » ponctuellement. (Par exemple, lire une valeur d’un capteur et l’envoyer par WiFi toutes les 10 minutes).

En mode **Deep Sleep**, les 2 CPU de l’ESP32 ne fonctionnent plus et c’est le processeur **ULP** (Ultra Low Processor) qui prend le relais. C’est un processeur qui consomme très peu d’énergie et qui peut exécuter certaines actions. La Flash et la RAM ne sont plus alimentées non plus, seule la mémoire RTC est encore alimentée et peut être utilisée. Le Wifi et le Bluetooth sont aussi bien sûrs désactivés. Grâce à cette mémoire RTC on peut toujours accéder aux périphériques, interruptions, timers et capteurs internes.

## Sources de réveil

Après avoir mis l’ESP32 en mode Deep Sleep, il y a plusieurs moyens de le réveiller :

-   Utiliser un timer (chronomètre) interne pour réveiller l’ESP32 à un moment choisi (réveil interne)  
-   Utiliser les capteurs capacitifs tactiles
-   Utiliser les broches GPIO RTC

## Utilisation

Lorsqu’on utilise le mode **Deep Sleep**, il faut :

-   Configurer les sources de réveil de l’ESP32    
-   Éventuellement choisir les périphériques à éteindre  pendant le mode Deep Sleep. Par défaut, l’ESP32 éteint tous les périphériques qui ne sont pas nécessaires pour détecter la demande de réveil.  
-   Utiliser la fonction  `esp_deep_sleep_start()` pour rentrer dans le mode Deep Sleep.


```cpp
   //Affiche la raison du réveil
   print_wakeup_reason();

   //Configuration du timer
   esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
```

La fonction print_wakeup-reason()
```cpp
void print_wakeup_reason(){
   esp_sleep_wakeup_cause_t source_reveil;

   source_reveil = esp_sleep_get_wakeup_cause();

   switch(source_reveil){
      case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Réveil causé par un signal externe avec RTC_IO"); break;
      case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Réveil causé par un signal externe avec RTC_CNTL"); break;
      case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Réveil causé par un timer"); break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Réveil causé par un touchpad"); break;
      default : Serial.printf("Réveil pas causé par le Deep Sleep: %d\n",source_reveil); break;
   }
}
```
