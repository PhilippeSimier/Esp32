/* 
 * File:   exceptions.cpp
 * Author: philippe
 * 
 * exceptions in action
 * Created on 11 août 2022, 18:18
 */

#include <Arduino.h>
#include <iostream>
#include <Throwing.h>

using std::runtime_error;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        continue;

    try {
        /* This will succeed */
        Throwing obj1(42);
        Throwing obj2(obj1);

        /* This will throw an exception */
        Throwing obj3(0);

        std::cout << "This will not be printed" << std::endl;
        
    } 
    catch (const runtime_error &e) {
        
        std::cout << "Exception caught: " << e.what() << std::endl;
        
    }
}

void loop() {

}



