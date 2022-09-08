
/* 
 * File:   Ecran.cpp
 * Author: Philippe SIMIER
 * 
 * Created on 1 février 2022, 23:57
 */

#include <Ecran.h>

Ecran::Ecran() :
SSD1306Wire(0x3C, SDA, SCL, GEOMETRY_128_64)
{
    init();
    flipScreenVertically();
    setFont(Dialog_plain_16);
}

void Ecran::AfficherMessage(const String _message, const int _ligne) {
    int nbPixels = (128 - getStringWidth(_message)) / 2;
    setColor(BLACK);
    fillRect(0, 32 * _ligne, 128, 32);
    setColor(WHITE);
    drawString(nbPixels, _ligne * 32, _message);
    display();
}
