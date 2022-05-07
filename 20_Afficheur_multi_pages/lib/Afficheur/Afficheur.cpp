/* 
 * File:   Afficheur.cpp
 * Author: ale
 * 
 * programme de démonstration pour la classe OLEDDisplayUi
 * Created on 7 avril 2022, 19:54
 */

#include "Afficheur.h"

// Constructeur de Afficheur
// Sur la carte Ballon adresse 0x3c connecté sur SDA et SCL

Afficheur::Afficheur() :
frameCount(4),
overlaysCount(1),
display(SSD1306Wire(0x3c, SDA, SCL, GEOMETRY_128_64)),
ui(OLEDDisplayUi(&display)),
frames{Afficheur::drawFrame1, Afficheur::drawFrame2, Afficheur::drawFrame3, Afficheur::drawFrame4},
overlays{Afficheur::msOverlay}

{
    anchor = this;
    
    // Customize the active and inactive symbol
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);
    
    // You can change this to  TOP, LEFT, BOTTOM, RIGHT
    ui.setIndicatorPosition(BOTTOM);

    // Defines where the first frame is located in the bar.
    ui.setIndicatorDirection(LEFT_RIGHT);
    
    // You can change the transition that is used
    // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
    ui.setFrameAnimation(SLIDE_UP);

    ui.setOverlays(overlays, overlaysCount);
    ui.setFrames(frames, frameCount);
    ui.init();
    ui.disableIndicator();
    display.flipScreenVertically();


}

Afficheur::~Afficheur() {
}

/**
 * Brief méthode pour afficher un message
 * @param message 
 */
void Afficheur::afficher(String message) {

    display.clear();
    display.drawStringMaxWidth(0, 0, 110, message);
    display.display();
}

/**
 * Methode pour retourner le budget temps
 * @return 
 */
int Afficheur::update() {
    return ui.update();
}

void Afficheur::msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(128, 0, String(millis()));

}

void Afficheur::drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    anchor->ui.disableIndicator();
    display->drawXbm(x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

void Afficheur::drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
    // Besides the default fonts there will be a program to convert TrueType fonts into this format
    anchor->ui.disableIndicator();
    
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(0 + x, 10 + y, "Arial 10");

    display->setFont(ArialMT_Plain_16);
    display->drawString(0 + x, 20 + y, "Arial 16");

    display->setFont(ArialMT_Plain_24);
    display->drawString(0 + x, 34 + y, "Arial 24");
}

void Afficheur::drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    
    anchor->ui.disableIndicator();
    // Text alignment demo
    display->setFont(ArialMT_Plain_10);

    // The coordinates define the left starting point of the text
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0 + x, 11 + y, "Left aligned (0,10)");

    // The coordinates define the center of the text
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 22 + y, "Center aligned (64,22)");

    // The coordinates define the right end of the text
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->drawString(128 + x, 33 + y, "Right aligned (128,33)");
}

void Afficheur::drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    // Demo for drawStringMaxWidth:
    // with the third parameter you can define the width after which words will be wrapped.
    // Currently only spaces and "-" are allowed for wrapping
    anchor->ui.disableIndicator();
    
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawStringMaxWidth(0 + x, 10 + y, 128,
            "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");

}


Afficheur* Afficheur::anchor = NULL;