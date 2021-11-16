#include <Arduino.h>
#include "SPIFFS.h"
#include <Preferences.h>

float maVariable;
Preferences preferences;

void setup() {
    Serial.begin(115200);
    

    // Démarre le système de fichier SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Affiche les tailles totale et utilisée
    unsigned int totalBytes = SPIFFS.totalBytes();
    unsigned int usedBytes = SPIFFS.usedBytes();

    Serial.println();
    Serial.println("===== Flash File System Info =====");

    Serial.print("Total space:      ");
    Serial.print(totalBytes);
    Serial.println(" octets");

    Serial.print("Total space used: ");
    Serial.print(usedBytes);
    Serial.println(" octets");

    Serial.println();

    // Ouvre le fichier de test en lecture seule
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
        // File not found | le fichier de test n'existe pas
        Serial.println("Failed to open index.html file");
        return;
    }

    // Envoie le contenu du fichier index.html sur le port série
    Serial.println();
    Serial.println("Read index.html file content :");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();
    
    // Exemple d'utilisation de Preferences 
        
    preferences.begin("mon-app", false);
    // Get the counter value, if the key does not exist, return a default value of 0
    // Note: Key name is limited to 15 chars.
    unsigned int counter = preferences.getUInt("counter", 0);
    counter++;
    Serial.printf("Current counter value: %u\n", counter);

    // Store the counter to the Preferences
    preferences.putUInt("counter", counter);

    // Close the Preferences
    preferences.end();
    

}

void loop() {
}

