# Économiser l’énergie 

L’ESP32 possède des modes d’économie d’énergie appelés **Deep Sleep, Light Sleep** qui permettent « d’endormir l’ESP32 ».  Pendant ces modes, l’ESP32 peut effectuer des tâches simples et se faire réveiller pour effectuer des tâches plus complexes.

Ces modes d’économie d’énergie sont utiles quand l’ESP32 est alimenté par batterie et qu'il « travaille » ponctuellement. (Par exemple, lire une valeur d’un capteur et l’envoyer par WiFi toutes les 10 minutes).

# Les différents modes

### Light Sleep
 
En mode **Light Sleep**, les 2 processeurs sont mis **en pause** en désactivant leurs impulsions d'horloge, tandis que le RTC et le coprocesseur ULP sont maintenus actifs. Cela se traduit par une consommation d'énergie  d'environ 0,8 mA. 
la fonction `esp_light_sleep_start()` permet d'entrer en sommeil léger.

### Deep Sleep
En mode **deep sleep**, les processeurs, la majeure partie de la RAM et tous les périphériques numériques sont éteints. Les seules parties de la puce qui restent opérationnelles sont :

-   Coprocesseur ULP
-   Contrôleur RTC
-   Périphériques RTC
-   Mémoire RTC rapide et lente

L'ESP32 consomme environ 0,15 mA (si le coprocesseur ULP est allumé) à 10µA.
La fonction `esp_deep_sleep_start()`permet d'entrer en sommeil profond.

Avec le CPU, la mémoire principale de la puce est également désactivée. En conséquence, tout ce qui est stocké dans cette mémoire est effacé.

Étant donné que la mémoire RTC est conservée, son contenu est préservé même pendant le sommeil profond et peut être récupéré après le réveil de la puce. C'est pourquoi la puce stocke les données de connexion Wi-Fi et Bluetooth dans la mémoire RTC avant d'entrer en veille profonde.

Si vous souhaitez utiliser les données après le redémarrage, stockez-les dans la mémoire RTC en définissant une variable globale avec l'attribut `RTC_DATA_ATTR`. Par exemple :

```cpp 
RTC_DATA_ATTR int myVar = 0;
```
Après être sortie du sommeil profond, la puce redémarre avec une réinitialisation et recommence l'exécution du programme depuis le début.


## Sources de réveil

Après avoir mis l’ESP32 en mode Deep Sleep, il y a plusieurs moyens de le réveiller :

-   Utiliser un timer (chronomètre) interne pour réveiller l’ESP32 à un moment choisi (réveil interne)  
-   Utiliser les capteurs capacitifs tactiles
-   Utiliser le réveil externe (ext0 & ext1)

Plusieurs sources de réveil peuvent être combinées, auquel cas la puce se réveillera lorsque l'une des sources sera déclenchée.

La fonction `esp_sleep_enable_timer_wakeup(time_in_us)` permet de configurer la minuterie comme source de réveil. Cette fonction accepte une durée en microsecondes (μs).

La fonction `esp_sleep_enable_touchpad_wakeup()` permet  de configurer le réveil à l'aide de la broche tactile.

**Source de réveil externe ext0**
L'ESP32 peut être configuré pour se réveiller du sommeil  lorsque **l'une des broches** RTC_GPIO change de niveau logique.
La fonction `esp_sleep_enable_ext0_wakeup(GPIO_PIN, LOGIC_LEVEL)` permet d'activer cette source de réveil. Cette fonction prend deux paramètres, le numéro de broche GPIO et le niveau logique (LOW ou HIGH) par lequel on veut déclencher le réveil.

**Source de réveil externe ext1**
L'ESP32 peut être configuré pour se réveiller du sommeil profond à l'aide **de plusieurs broches**. N'oubliez pas que ces broches doivent figurer parmi les broches RTC GPIO.
La  fonction `esp_sleep_enable_ext1_wakeup(BUTTON_PIN_MASK, LOGIC_LEVEL)` permet d'activer cette source de réveil. Cette fonction prend deux paramètres. Le premier est un masque de bits qui indique à l'ESP32 quelles broches nous voulons utiliser et le deuxième paramètre peut être l'un des deux niveaux logiques  pour déclencher le réveil.

## Utilisation

Lorsqu’on utilise le mode **Deep Sleep**, il faut :

-   Configurer les sources de réveil de l’ESP32
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

