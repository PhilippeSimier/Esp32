/* 
 * File:   lambda.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Les fonctions lambda en action
 *
 * Created on 14 août 2022, 16:27
 */

#include <Arduino.h>
#include <iostream>
#include <vector>


void setup() {
   
    Serial.begin(115200);
    while (!Serial)
        continue;
    
    auto lambda { [](auto const & parametre) -> void { std::cout << "Paramètre reçu : " << parametre << std::endl; }};
    
    std::string s1 = "Hello ! philippe";
    lambda(s1);
   
    
    std::vector<std::string> const chaines { "Un mot", "Autre chose", "Du blabla", "Du texe", "Des lettres" };
    std::for_each(std::begin(chaines), std::end(chaines), lambda);
    
    std::vector<int> const nombres { 3, 1, 25, 7, 51 };
    std::for_each(std::begin(nombres), std::end(nombres), lambda);
}

void loop() {

}
