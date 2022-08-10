/* 
 * File:   string_view.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * String_view in action
 * 
 * Ne pas oublier de passer le compilateur gcc en version 17
 * dans platformio ajouter les 2 lignes suivantes
 *      build_unflags = -std=gnu++11
 *      build_flags = -std=gnu++17
 * 
 * Created on 9 août 2022, 17:33
 */

#include <Arduino.h>
#include <iostream>
#include <string_view>

void printSV(std::string_view str);

void setup() {
    Serial.begin(115200);
    while (!Serial)
        continue;

    std::string_view sv { "balloon" };
    std::string s { "Hello, world" };
    char  sc[]  { "stratosphérique" };
    const char *a1 { "hello" };
    

    printSV(sv); // ok: pass std::string_view
    printSV(s);  // ok: pass std::string
    printSV(sc); //ok pass un C-style string literal
    printSV("un litteral");
    printSV(a1);
    
}

void loop() {

}

void printSV(std::string_view str) {
    std::cout << str << std::endl;
}

