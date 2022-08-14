/* 
 * File:   any.cpp
 * Author: philippe
 *
 * Created on 14 août 2022, 10:03
 */

#include <Arduino.h>
#include <iostream>
#include <string>
#include <any>

void setup() {

    Serial.begin(115200);
    while (!Serial)
        continue;

    int i = 42;
    void* pvi = &i;
    double d1 = *static_cast<double*> (pvi);

    try {
        
        std::any ai = i;
        double d2 = std::any_cast<double&>(ai);
        
    } catch (std::bad_any_cast &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::any a{1};
    std::cout << "a -> " << std::any_cast<int>(a) << '\n';


    a = 3.1415f;
    std::cout << "a -> " << std::any_cast<float>(a) << '\n';

    a.reset();
    if (!a.has_value()) {
        std::cout << "a -> " << "n'a pas de valeur\n";
    }
    
    a = std::string(R"(<a href="file">\spiffs\</a>)");
    std::cout << "a -> " << std::any_cast<std::string>(a) << '\n';

    a = {}; // On peut utiliser la méthode has_value() pour déterminer s'il y a une valeur.
    if (!a.has_value()) {
        std::cout << "a -> " << "n'a pas de valeur\n";
    }    
}

void loop() {

}