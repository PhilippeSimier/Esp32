/* 
 * File:   LDR.cpp
 * Author: Philippe Simier Lycée Touchard Washington Le Mans
 * Programme test entrée Analogique connectée sur LDR ou potentomètre
 * Created on 12 septembre 2022, 15:14
 */

#include <Arduino.h>
#include <driver/adc.h>

void setup() {

    // Démarre la liaison série 115200 bauds prise USB
    Serial.begin(115200);
    while (!Serial);

    // plage de valeurs de 0 à 4095. (ADC_WIDTH_BIT_12)
    adc1_config_width(ADC_WIDTH_BIT_12);
    //11 dB pour une tension d’entrée de 0.15v à 3.6v sur l'entrée analogique
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

}

void loop() {

    // Lecture de l'entrée analogique GPIO 36 => ADC1_CHANNEL_0
    int value = adc1_get_raw(ADC1_CHANNEL_0);
    // Mise à l'échelle
    int y = map(value, 0, 4095, 0, 100);
    Serial.print(y);
    Serial.println(" %");
    delay(1000);

}

