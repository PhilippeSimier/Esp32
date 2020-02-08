# Conversion ADC & DAC

## Présentation

L'ESP32 possède deux convertisseurs ADC1 et ADC2 SAR ( registre d'approximation successive ) 12 bits prenant en charge un total de **18 canaux de mesure** (entrées analogiques). 
ADC2 est utilisé par le pilote Wi-Fi. Par conséquent, l'application ne peut utiliser ADC2 que lorsque le pilote Wi-Fi n'a pas démarré.

| ADC1           |              ADC2                    |
|----------------|------------------------------|
| GPIO 36 => ADC1_CH0 | GPIO 4 ==> ADC2_CH0 |
| GPIO 37 => ADC1_CH1 | GPIO 0 ==> ADC2_CH1 |
| GPIO 38 => ADC1_CH2 | GPIO 2 ==> ADC2_CH2 |
| GPIO 39 => ADC1_CH3 | GPIO 15 => ADC2_CH3 |
| GPIO 32 => ADC1_CH4 | GPIO 13 => ADC2_CH4 |
| GPIO 33 => ADC1_CH5 | GPIO 12 => ADC2_CH5 |
| GPIO 34 => ADC1_CH6 | GPIO 14 => ADC2_CH6 |
| GPIO 35 => ADC1_CH7 | GPIO 27 => ADC2_CH7 |
|    | GPIO 25 => ADC2_CH8 |
|    | GPIO 26 => ADC2_CH9 |

 ![Brochage du kit esp32](/02_ES_Analogiques/brochage_esp32.png) 
 
## Lecture d'une entrée analogique

    int analog_value = analogRead (36);
    //ou
    int analog_value = adc1_get_raw(ADC1_CHANNEL_0)

# Configuration

Le convertisseur ADC peut être configuré avant la lecture.
La configuration de l’ADC permet de définir l’atténuation du convertisseur qui va définir la plage de tension à convertir :

 - 0 dB  pour une tension d’entrée de 0.1v à 1v sur un port.  (ADC_ATTEN_DB_0)
 - 2.5 dB pour une tension d’entrée de 0.1v à 1.34v sur un port. (ADC_ATTEN_DB_2_5)
 - 6 dB pour une tension d’entrée de 0.15v à 2v sur un port.  (ADC_ATTEN_DB_6)
 - 11 dB pour une tension d’entrée de 0.15v à 3.6v sur un port.  (ADC_ATTEN_DB_11)

Il est également possible de définir la résolution en bits concernant la conversion :

 - 9 bits : plage de valeurs de 0 à 511. (ADC_WIDTH_BIT_9)
 - 10 bits : plage de valeurs de 0 à 1023. (ADC_WIDTH_BIT_10)
 - 11 bits : plage de valeurs de 0 à 2047.  (ADC_WIDTH_BIT_11)
 - 12 bits : plage de valeurs de 0 à 4095.  (ADC_WIDTH_BIT_12)

Pour ADC1, configurez la précision et l'atténuation souhaitées en appelant les fonctions :  **adc1_config_width()** et   **adc1_config_channel_atten()**.

Exemple de code :
```cpp
#include <driver/adc.h>

void setup()
{
  Serial.begin(115200);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_0);
}

void loop()
{

  int value = adc1_get_raw(ADC1_CHANNEL_6);
  Serial.println(value);
  delay(1000);
}
```

# Minimiser le bruit
Le convertisseur peut être sensible au bruit, ce qui entraîne de grandes différences dans les lectures de l'ADC. Pour minimiser le bruit, on peut connecter un condensateur de 0,1 uF à l'entrée ADC utilisée. Le multi-échantillonnage peut également être utilisé pour atténuer davantage les effets du bruit. Pour ce faire faire plusieurs conversion mémorisé dans un tableau puis trier le tableau, enfin prendre la valeur médiane.

# Changelog

**08/01/2020 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


