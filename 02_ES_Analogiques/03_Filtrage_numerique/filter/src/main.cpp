/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <driver/adc.h>
#include <driver/dac.h>
#include <Arduino.h>
#include <Filter.h>

Filter leFiltre(5000, ADC1_CHANNEL_6, DAC_CHANNEL_1);

void setup() {

    Serial.begin(115200);

    leFiltre.setLPFOrdre1(500);
    leFiltre.printEquaReccurence(&Serial);
    leFiltre.begin();

}

void loop() {
    char c = 0;
    // Coefficients pour un filtre PB du second ordre  m = 0.1
    float a1[3] = {0.0      , -1.55193 , 0.89181};
    float b1[3] = {0.084971 ,  0.16994 , 0.084971};
    
    // Coefficients pour un filtre PB du premier ordre  fc=50
    float a2[3] = {1.0      , -0.9390625, 0.0};
    float b2[3] = {0.030468 , 0.030468 , 0.0};
    
    // Coefficient pour un filtre PB 2 pôles Chebyshev
    float a3[3] = {1.0      , -1.916900, 0.92043911};
    float b3[3] = {0.000884 , 0.001769 , 0.000884};
    
    // Coefficient pour un filtre PH 2 pôles Chebyshev
    float a4[3] = {1.0      , -1.128311, 0.415951};
    float b4[3] = {0.636065 , -1.272131 , 0.636065};   
    
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '0':
                Serial.println("Filtre PB premier ordre fc = 50hz");
                
                leFiltre.setEquaReccurence(a2,b2);
                leFiltre.printEquaReccurence(&Serial);
                break;
            
            case '1':
                Serial.println("Filtre Passe bas 1er ordre fc 100Hz");
                leFiltre.setLPFOrdre1(100);
                leFiltre.printEquaReccurence(&Serial);
                break;

            case '2':
                Serial.println("Filtre Passe bas 1er ordre fc 200Hz");
                leFiltre.setLPFOrdre1(200);
                leFiltre.printEquaReccurence(&Serial);
                break;

            case '3':
                Serial.println("Filtre Passe bas 1er ordre fc 500Hz");
                leFiltre.setLPFOrdre1(500);
                leFiltre.printEquaReccurence(&Serial);
                break;
                
            case '4':
                Serial.println("Filtre Passe bas du second ordre m = 0.1");
                
                leFiltre.setEquaReccurence(a1,b1);
                leFiltre.printEquaReccurence(&Serial);
                break;
                
            case '5':
                Serial.println("Filtre Passe bas 2 pôles Chebyshev fc = 50hz");
                
                leFiltre.setEquaReccurence(a3,b3);
                leFiltre.printEquaReccurence(&Serial);
                break; 
                
            case '6':
                Serial.println("Filtre Passe haut 2 pôles Chebyshev fc = 500hz");
                
                leFiltre.setEquaReccurence(a4,b4);
                leFiltre.printEquaReccurence(&Serial);
                break; 
                
            case '7':
                Serial.println("Filtre Passe bas 2eme ordre fc = 50hz, Q = 0.707");
                
                leFiltre.setLPFordre2(50);
                leFiltre.printEquaReccurence(&Serial);
                break; 
                
            case '8':
                Serial.println("Filtre Passe haut 2eme ordre fc = 500hz, Q = 0.707");
                
                leFiltre.setHPFordre2(500);
                leFiltre.printEquaReccurence(&Serial);
                break;
            
            case 'n':
                Serial.println("Filtre Notch fc = 50hz, Q = 1");
                
                leFiltre.setNotch(50);
                leFiltre.printEquaReccurence(&Serial);
                break; 
                
            case 'p':
                Serial.println("Filtre Peak fc = 50hz, Q = 2, Gain = 6dB");
                
                leFiltre.setPeak(50.0 , 2.0 , 6.0);
                leFiltre.printEquaReccurence(&Serial);
                break;    
                
            case 'e':
                leFiltre.printEquaReccurence(&Serial);
                break;
        }
    }
}
