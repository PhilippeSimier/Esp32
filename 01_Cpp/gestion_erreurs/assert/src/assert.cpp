/* 
 * File:   assert.cpp
 * Author: philippe SIMIER Lycée Touchard Washington Le Mans
 * 
 * assert & static_assert in action en C++ 
 *
 * Created on 11 août 2022, 13:17
 */

#include <Arduino.h>
#include <cassert>

float calculateTime(float height, float gravity) {

    assert(gravity > 0.0);   // gravity doit être supérieure à 0.0 pour avoir la racine carré d'un nombre positif 

    float res { 0.0 };

    if (height > 0.0) {
        res = std::sqrt((2.0 * height) / gravity);
    }
    return res;
}

void setup() {
    
    static_assert( sizeof(int) == 4, "32 bits platform required" );  // Pour provoquer une erreur à la compilation
    
    Serial.begin(115200);
    while (!Serial)
        continue;

    float h = calculateTime(10.0, 9.80);
    Serial.println(h);
    delay(5000);
    h = calculateTime(10.0, -9.80);
    Serial.println(h);


}

void loop() {

}

