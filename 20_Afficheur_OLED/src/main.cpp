/*
 * Programme test Ecran OLED SSD1306
 * pio lib -g install 2978
*/

#include <Arduino.h>
#include <SSD1306Wire.h>

const int sda = 4;
const int scl = 15;

SSD1306Wire display(0x3c, sda , scl, GEOMETRY_128_64);

void setup()
{
    display.init();

    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "Test Ecran");
    display.drawString(0, 32, "Ligne 2");
    display.display();
}

void loop()
{
}
