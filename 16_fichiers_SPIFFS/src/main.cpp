#include <Arduino.h>
#include "SPIFFS.h"
#include <Effortless_SPIFFS.h>

float maVariable;
eSPIFFS fileSystem;

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
    
    // Exemple d'utilisation eSPIFFS avec une variable de type float

    // Ouverture du fichier /Float.txt et transfert du contenu dans maVariable
    if (fileSystem.openFromFile("/Float.txt", maVariable)) {
        Serial.print("\nSuccessfully read file and parsed data: ");
        Serial.println(maVariable, 6);
    }

    // Set myVariable avec un contenu aléatoire
    maVariable = (float) random(1, 1000) / (float) random(1000, 65563);
    Serial.print("myVariable is now: ");
    Serial.println(maVariable, 6);

    // Ecriture de maVariable dans /Float.txt
    if (fileSystem.saveToFile("/Float.txt", maVariable)) {
        Serial.println("Successfully wrote data to file");
    }
    
       // Ouvre le fichier de Float.txt en lecture seule
    file = SPIFFS.open("/Float.txt", "r");
    if (!file) {
        // File not found | le fichier de test n'existe pas
        Serial.println("Failed to open Float.txt file");
        return;
    }

    // Envoie le contenu du fichier index.html sur le port série
    Serial.println();
    Serial.println("\nRead Float.txt file content :");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();

}

void loop() {
}

