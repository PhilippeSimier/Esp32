/* 
 * File:   Led.h
 * Author: philippe SIMIER Touchard washington
 *
 * Created on 14 février 2022, 15:40
 */

#ifndef LED_H
#define LED_H

#include <NeoPixelBus.h>  // Led RGB WS2812

#define PIN_RGB     19    // GPIO19 pour carte Clavier SNIR 
#define NUMPIXELS   4     // Quatre leds pour carte Clavier SNIR

#define ROUGE   RgbColor(8,0,0)
#define RED 	RgbColor(8,0,0)

#define BLEU    RgbColor(0,0,8)
#define BLUE    RgbColor(0,0,8)

#define VERT    RgbColor(0,8,0)
#define GREEN   RgbColor(0,8,0)

class Led : public NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0800KbpsMethod> // Spécialisation de NeoPixelBus 
{

public:
    
    Led(word _numPixels = NUMPIXELS );
    virtual ~Led();
    
    void allumer(const RgbColor &couleur, word id = 0);
    void eteindre(word id = 0);
    

private:

};




#endif /* LED_H */

