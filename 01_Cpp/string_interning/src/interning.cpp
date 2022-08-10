/* 
 * File:   interning.cpp
 * Author: philippe
 *
 * Created on 8 août 2022, 10:29
 * 
 * String interning in action
 * Mais où donc l'editeur de lien range t'il les variables ?
 * Réponses :
 *  Les variables const sont rangées dans la mémoire flash                plage 0x3f40_0000  0x3f7f_ffff
 *  les variables en lecture écriture sont rangées  dans la mémoire SRAM  plage 0x3ff8_0000  0x3fff_ffff
 */

#include <Arduino.h>

const int maxarray { 255 };
char store_char[maxarray];

// Number of copies: 1 in Flash, 1 in RAM
const char *a1 { "hello" };
const char *a2 { "hello" };

// Number of copies: 1 in Flash, 3 in RAM
// pour char[], le programme fait une copie du littéral lorsqu'il crée les variables :
const char b1[] { "hello" };
const char b2[] { "hello" };

char g1[] { "hello" };
char g2[] { "hello" };

// Number of copies: 2 in Flash, 2 in RAM
static const char c1[] PROGMEM = "This is a string stored in flash";
static const char c2[] PROGMEM = "This is a string stored in flash";

// Number of copies: 1 in Flash, 3 in RAM
// pour String, le constructeur fait une copie de la chaîne :
const String d1 { "hello" };
const String d2 { "hello" };

// Number of copies: 1 in Flash, 3 in RAM
// pour std::string, le constructeur fait aussi une copie de la chaîne :
const std::string e1 { "hello" };
const std::string e2 { "hello" };

// Number of copies: 1 in Flash, 1 in RAM
const __FlashStringHelper* f1 = F("hello");
const __FlashStringHelper* f2 = F("hello");

void showAddresses(const char *title, const void *s1, const void *s2) {
    Serial.println(title);
    Serial.print(" s1 = ");
    Serial.printf("0x%x\r\n", (intptr_t) s1);
    Serial.print(" s2 = ");
    Serial.printf("0x%x\r\n", (intptr_t) s2);
    Serial.println("---------------------");
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        continue;

    showAddresses("const char*", a1, a2);
    showAddresses("const char[]", b1, b2);
    showAddresses("char[]", g1, g2);
    showAddresses("static const char[] PROGMEM", c1, c2);
    showAddresses("F()", F("hello"), F("hello"));
    showAddresses("const String", d1.c_str(), d2.c_str());
    showAddresses("const std::string", e1.c_str(), e2.c_str());
    showAddresses("const __FlashStringHelper*", f1, f2);
    
    showAddresses("store_char[255]", store_char, nullptr);
    
}

void loop() {

}

