/* 
 * File:   lambda.cpp
 * Author: philippe
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
    
    auto lambda = [](std::string const & message) -> void { std::cout << "Message reçu : " << message << std::endl; };
    
    lambda("Hello !");
    lambda("philippe");
    
    std::vector<std::string> const chaines { "Un mot", "Autre chose", "Du blabla", "Du texe", "Des lettres" };
    std::for_each(std::begin(chaines), std::end(chaines), lambda);
}

void loop() {

}
