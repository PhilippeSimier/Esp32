/* 
 * File:   nullptr.cpp
 * Author: philippe
 * 
 *  nullptr programme de démonstration
 *  Why C++ programmers don't use NULL?
 * 
 * Created on 10 août 2022, 16:03
 */

#include <Arduino.h>
#include <cstddef>

// Déclaration d'une fonction template printValue
template <typename T> void printValue(T value);
// Spécialisation pour le type int
template <> void printValue<int>(int value);
// Spécialisation pour le type void *
template <> void printValue<void *>(void *value);
// Spécialisation pour le type nullptr_t
template <> void printValue<nullptr_t>(nullptr_t value);


void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;
  
  const char *color { NULL };
  String colorStr1 { color };
  String colorStr2 { NULL };
  String colorStr3 {};

  if (colorStr1 == colorStr2) {
    Serial.println("colorStr1 == colorStr2");
  } else {
    Serial.println("colorStr1 != colorStr2");
  }

  Serial.print("colorStr1 = ");
  Serial.println(colorStr1);
  Serial.print("colorStr2 = ");
  Serial.println(colorStr2);
  Serial.print("colorStr3 = ");
  Serial.println(colorStr3);
  
  
  
  int nb { 42 };
  
  
  printValue(nb);  // Affiche Integer: 42
  printValue( static_cast<void*>( &nb ) );  // Affiche Pointer : (l'adresse de la variable nb)
  printValue(NULL);   // Affiche Integer: 0
  printValue(nullptr); // Affiche Pointer nullptr : 0
  
  
}


void loop() {}




//spécialisation pour entier
template <>
void printValue<int>(int value) {
  Serial.print("Integer: ");
  Serial.println(value, DEC);
}

//spécialisation pour pointeur généric void *
template <>
void printValue<void *>(void *value) {
  Serial.print("Pointer: 0x");
  Serial.println((intptr_t)value, HEX);
}

//spécialisation pour nullptr_t
template <>
void printValue<nullptr_t>(nullptr_t value) {
   Serial.print("nullptr_t : 0x"); 
   Serial.println((intptr_t)value, HEX);
}

