/* 
 * File:   Filter.cpp
 * Author: philippe
 * 
 * Created on 18 juillet 2022, 12:49
 */

#include "Filter.h"


Filter::Filter(float _splFreq,
        adc1_channel_t _adc1Channel,
        dac_channel_t _dacChannel
        ) :
splFreq(_splFreq),
adc1Channel(_adc1Channel),
dacChannel(_dacChannel),
timer(NULL),
n(0) {
    anchor = this;

    a[0] = 1.0;
    a[1] = 0.0;
    a[2] = 0.0;
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;

}

Filter::Filter(const Filter& orig) {
}

Filter::~Filter() {
}

void Filter::begin() {

    dac_output_enable(dacChannel);

    adc1_config_width(ADC_WIDTH_BIT_12); // Configuration de la résolution
    adc1_config_channel_atten(adc1Channel, ADC_ATTEN_DB_11); // Configuration de l'atténuation tension d'entrée /4

    timer = timerBegin(0, 80, true); // Configuration du timer
    timerAttachInterrupt(timer, Filter::marshall, true); // Attache une fonction au timer
    timerAlarmWrite(timer, 1000000 / splFreq, true); // Configuration de la fréquence d'échantillonage
    timerAlarmEnable(timer); // Lancement du timer

}

void Filter::marshall() {
    anchor->interuption();
}

void IRAM_ATTR Filter::interuption() {

    xthal_set_cpenable(1); // enable FPU
    xthal_save_cp0(cp0_regs); // Save FPU registers

    x[n] = adc1_get_raw(adc1Channel) - 2047; // Lecture de la valeur sur adc1

    // Calcul de l'équation de récurrence filtre IIR
    y[n] = b[0] * x[ n];
    y[n] += b[1] * x[(n - 1) & MASQUE_TAMPON];
    y[n] += b[2] * x[(n - 2) & MASQUE_TAMPON];
    y[n] -= a[1] * y[(n - 1) & MASQUE_TAMPON];
    y[n] -= a[2] * y[(n - 2) & MASQUE_TAMPON];


    dac_output_voltage(dacChannel, (y[n] + 2047) / 16); //envoi de la valeur entière vers le dac
    n = (n + 1) & MASQUE_TAMPON; // incrémentation de n

    xthal_restore_cp0(cp0_regs); // Restore FPU  
    xthal_set_cpenable(0); // and turn it back off
}

/**
 * @brief méthode pour calculer les coefficients 
 * d'un filtre passe bas du premier ordre
 *
 * @param fc la fréquence de coupure en Hz
 */
void Filter::setLPFOrdre1(float fc) {


    float A = splFreq / (M_PI * fc);

    b[0] = 1 / (1 + A);
    b[1] = b[0];
    b[2] = .0;

    a[1] = (1 - A) / (1 + A);
    a[2] = .0;
}

/**
 * Methode pour obtenir l'équation de récurrence sous forme litérale
 * @param client le flux de sortie
 */
void Filter::printEquaReccurence(Stream* client) {

    client->print("Yn = ");
    if (std::fpclassify(b[0]) != FP_ZERO) {
        client->printf("%.5f", b[0]);
        client->print(" Xn ");
    }
    if (std::fpclassify(b[1]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.5f", b[1]);
        client->print(" Xn_1 ");
    }
    if (std::fpclassify(b[2]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.5f", b[2]);
        client->print(" Xn_2 ");
    }
    if (std::fpclassify(a[1]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.5f", a[1]);
        client->print(" Yn_1 ");
    }
    if (std::fpclassify(a[2]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.5f", a[2]);
        client->println(" Yn_2");
    }
    client->println(" ");
}

/**
 * Methode pour fixer les coefficients de l'équation de réccurence
 * les coefficients sont calculés avec la feuille de calcul. 
 * @param _a le tableau des coefficients a
 * @param _b le tableau des coefficients b
 */
void Filter::setEquaReccurence(float _a[3], float _b[3]) {
    for (int i = 0; i < 3; i++) {
        a[i] = _a[i];
        b[i] = _b[i];
    }
}

/**
 * @brief Méthode pour calculer un filtre biquad passe bas
 * @param fc  Fréquence de coupure du filtre passe bas
 * @param Q   Attenuation à la fréquence de coupure 0.707 pour -3dB
 */
void Filter::setLPFordre2(float fc, float Q) {

    float w0, alpha, a0;

    w0 = 2 * M_PI * (fc / splFreq);
    alpha = sin(w0) / (2 * Q);
    a0 = 1 + alpha;

    a[1] = (-2.0 * cos(w0)) / a0;
    a[2] = (1.0 - alpha) / a0;
    b[0] = ((1.0 - cos(w0)) / 2.0) / a0;
    b[1] = (1.0 - cos(w0)) / a0;
    b[2] = ((1.0 - cos(w0)) / 2.0) / a0;

}

/**
 * @brief Méthode pour calculer un filtre biquad passe haut
 * @param fc  Fréquence de coupure du filtre passe haut
 * @param Q   Attenuation à la fréquence de coupure 0.707 pour -3dB
 */
void Filter::setHPFordre2(float fc, float Q) {

    float w0, alpha, a0;

    w0 = 2 * M_PI * (fc / splFreq);
    alpha = sin(w0) / (2 * Q);
    a0 = 1 + alpha;

    a[1] = (-2.0 * cos(w0)) / a0;
    a[2] = (1.0 - alpha) / a0;
    b[0] = ((1.0 + cos(w0)) / 2.0) / a0;
    b[1] = (-1.0 - cos(w0)) / a0;
    b[2] = ((1.0 + cos(w0)) / 2.0) / a0;
}

/**
 * @brief filtre notch (de l'anglais notch qui signifie encoche).
 *        filtre coupe-bande aussi appelé filtre réjecteur de bande
 * @param fc fréquence centrale 
 * @param Q
 */
void Filter::setNotch(float fc, float Q) {

    float w0, alpha, a0;

    w0 = 2 * M_PI * (fc / splFreq);
    alpha = sin(w0) / (2 * Q);
    a0 = 1 + alpha;

    a[1] = (-2.0 * cos(w0)) / a0;
    a[2] = (1.0 - alpha) / a0;
    b[0] = 1.0 / a0;
    b[1] = (-2.0 * cos(w0)) / a0;
    b[2] = 1.0 / a0;
}

/**
 * @brief filtre Peak (de l'anglais peak qui signifie crête).
 *        Un filtre peak fait un pic dans la réponse en fréquence 
 *        la hauteur du pic est fonction du gain G
 *        la largeur du pic est fonction du facteur Q
 * @param fc fréquence centrale 
 * @param Q
 */

void Filter::setPeak(float fc, float Q, float G) {

    float A, w0, alpha, a0;

    A = pow(10, G / 40);
    w0 = 2 * M_PI * (fc / splFreq);
    alpha = sin(w0) / (2 * Q);
    a0 = 1 + alpha / A;

    a[1] = (-2.0 * cos(w0)) / a0;
    a[2] = (1.0 - alpha / A) / a0;
    b[0] = (1.0 + alpha * A) / a0;
    b[1] = (-2.0 * cos(w0)) / a0;
    b[2] = (1.0 - alpha * A) / a0;

}


Filter* Filter::anchor = NULL;

