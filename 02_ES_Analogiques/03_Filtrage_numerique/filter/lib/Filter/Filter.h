/* 
 * File:   Filter.h
 * Author: philippe
 *
 * Created on 18 juillet 2022, 12:49
 */

#ifndef FILTER_H
#define FILTER_H

#include <Arduino.h>
#include <driver/adc.h>
#include <driver/dac.h>
#include <esp_attr.h>
#include <math.h>
#include <xtensa/hal.h>   // Pour FPU dans ISR



#define SAMPLING_FREQUENCY 5000      //fréquence d'échantillonage par défaut en Hz
#define TAILLE_TAMPON 16     // Taille du tempon ici 8
#define MASQUE_TAMPON 15     // Masque = TAILLE_TAMPON-1

class Filter {
public:
    Filter(float _splFreq = SAMPLING_FREQUENCY,
            adc1_channel_t _adc1Channel = ADC1_CHANNEL_6,
            dac_channel_t _dacChannel = DAC_CHANNEL_1
            );

    Filter(const Filter& orig);
    virtual ~Filter();

    void begin();

    void setLPFOrdre1(float fc);
    void setLPFordre2(float fc, float Q = 0.707);
    void setHPFordre2(float fc, float Q = 0.707);
    void setNotch(float fc, float Q = 1.0);
    void setPeak(float fc, float Q = 1.0, float G = 6.0);

    void setEquaReccurence(float _a[3], float _b[3]);
    void printEquaReccurence(Stream* client);


private:
    hw_timer_t * timer;
    void IRAM_ATTR interuption();
    static void marshall();
    static Filter* anchor;

    int splFreq; // Fréquence d'échantillonage   
    adc1_channel_t adc1Channel;
    dac_channel_t dacChannel;

    uint8_t n;
    uint32_t cp0_regs[18];

    float x[TAILLE_TAMPON]; // tampon pour les x_n
    float y[TAILLE_TAMPON]; // tampon pour les y_n

    float a[3]; // tableau des coefficients a
    float b[3]; // tableau des coefficients b

};

#endif /* FILTER_H */

