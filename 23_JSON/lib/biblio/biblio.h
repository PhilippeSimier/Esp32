/* 
 * File:   biblio.h
 * Author: philippe
 *
 * Created on 7 août 2022, 11:35
 */

#ifndef BIBLIO_H
#define BIBLIO_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

struct User {
    char nom[64];
    char prenom[64];
    int age;
};

void loadConfiguration(const char *filename, User &user);
void saveConfiguration(const char *filename, const User &user);
void printFile(const char *filename);
void listFiles();

#endif /* BIBLIO_H */

