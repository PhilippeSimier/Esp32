/* 
 * File:   Afficheur.h
 * From Author: philippe SIMIER Lycée Touchard Washington
 * Modified by Anthony Le Cren
 * Created on 11 février 2022, 11:15
 * Classe Afficheur pour afficheur OLED
 * 
 * https://www.online-utility.org/image/convert/to/XBM
 */

#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h>
#include <SSD1306Wire.h>
#include "OLEDDisplayUi.h"
#include "images.h"

class Afficheur {
public:

    Afficheur();
    virtual ~Afficheur();

    void afficher(String message);
    int update();


private:
    static void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
    static void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
    static void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
    static void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
    static void msOverlay(OLEDDisplay *display,  OLEDDisplayUiState* state);


    int frameCount; // Nombre de pages à afficher
    int overlaysCount;
    SSD1306Wire display;
    OLEDDisplayUi ui;
    FrameCallback frames[4];
    OverlayCallback overlays[1]; //affichage commun par dessus toutes les pages
    

    static Afficheur* anchor;   
};



#endif /* AFFICHEUR_H */