/* 
 * File:   cli_at.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 4 août 2022, 10:19
 */

#include <Arduino.h>
#include <CommandeAt.h>
#define LED 2

CommandeAt cat;

void _led_(ArgList& L, Stream& S);
void _ledIn_(ArgList& L, Stream& S);

void setup() {
    
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    while (!Serial);
    
    cat.onCmd("AT+LED", _led_);
    cat.onCmd("AT+LED?", _ledIn_);
    
    Serial.println("\r\nOK");
    
}

void loop() {
    
    cat.run();

} 

void _led_(ArgList& L, Stream& S) {

    String p;

    if (!(p = L.getNextArg()).isEmpty()) {
        if (p.equalsIgnoreCase("ON")) { //
            digitalWrite(LED, HIGH);
            S.println("OK\r\n");
        } else if (p.equalsIgnoreCase("OFF")) {
            digitalWrite(LED, LOW);
            S.println("OK\r\n");
        } else {
            S.println("Error Unknown argument\r\n");
        }
    } else {
        S.println("Error\r\n");
    }
}

void _ledIn_(ArgList& L, Stream& S){
    
    bool etat = digitalRead(LED);
    S.print("LED is ");
    if (etat)
        S.println("ON");
    else
        S.println("OFF");
}