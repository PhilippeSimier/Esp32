/* 
 * File:   assert.cpp
 * Author: philippe SIMIER
 * 
 * assert in action
 *
 * Created on 11 août 2022, 13:17
 */

#include <Arduino.h>
#include <assert.h>

float calculateTime(float height, double gravity) {

    assert(gravity > 0.0);   // gravity doit être supérieure à 0.0 

    float res{ 0.0};

    if (height <= 0.0) {
        res = 0.0;
    } else {
        res = std::sqrt((2.0 * height) / gravity);
    }
    return res;
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        continue;

    float h = calculateTime(10.0, 9.80);
    Serial.println(h);
    delay(10000);
    h = calculateTime(10.0, -9.80);
    Serial.println(h);


}

void loop() {

}

