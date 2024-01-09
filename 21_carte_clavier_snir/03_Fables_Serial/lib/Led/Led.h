/* 
 * File:   Led.h
 * Author: philippe SIMIER Touchard washington
 *
 * Created on 14 février 2022, 15:40
 */

#ifndef LED_H
#define LED_H

#include <NeoPixelBus.h>  // Led RGB WS2812
#include <esp32_snir.h>

#define ROUGE   RgbColor(8,0,0)
#define RED 	RgbColor(8,0,0)

#define BLEU    RgbColor(0,0,8)
#define BLUE    RgbColor(0,0,8)

#define VERT    RgbColor(0,8,0)
#define GREEN   RgbColor(0,8,0)

#define NOIR    RgbColor(0,0,0)


class Led : public NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> // Spécialisation de NeoPixelBus 
{

public:
    
    Led(word _numPixels = DATALEDS );
    virtual ~Led();
    
    void allumer(const RgbColor &couleur, word id = 0);
    void eteindre(const word id = 0);
    void cheniller(const RgbColor &couleur, word nb = 4);
    void chenillerInverse(const RgbColor &couleur, word nb = 4);
    void setDelay(const int nb);

private:
    word numPixels;
    int  nb_ms;
};




#endif /* LED_H */

