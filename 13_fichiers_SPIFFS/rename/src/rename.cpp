/* 
 * File:   rename.cpp
 * Author: philippe SIMIER Lycée touchard Le Mans
 * 
 * programme test pour le listage des fichiers présents
 * et le renommage
 *  
 * Created on 30 juillet 2022, 19:12
 */

#include <Arduino.h>
#include <SPIFFS.h>

void listFiles();

void setup() {

    Serial.begin(115200);

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    File file = SPIFFS.open("/test.txt", FILE_WRITE);

    if (!file) {
        Serial.println("There was an error opening the file for writing");
        return;
    }

    if (file.print("some content")) {
        Serial.println("File was written");
    } else {
        Serial.println("File write failed");
    }

    file.close();

    Serial.println("\n\n---BEFORE RENAMING---");
    listFiles();

    SPIFFS.rename("/test.txt", "/renamed.txt");

    Serial.println("\n\n---AFTER RENAMING---");
    listFiles();

}

void loop() {
}

/**
 * @brief liste les fichiers présents dans SPIFS
 */
void listFiles() {

    File root = SPIFFS.open("/");

    File file = root.openNextFile();

    while (file) {

        Serial.print("FILE: ");
        Serial.println(file.name());

        file = root.openNextFile();
    }
}

