/* 
 * File:   JsonSpiffs.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 6 août 2022, 21:17
 */

#include <Arduino.h>
#include <biblio.h>



const char *filename = "/config.txt"; 
User user; // <- global configuration object


void setup() {
    
    // Initialize serial port
    Serial.begin(115200);
    while (!Serial) continue;

    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Should load default config if run for the first time
    Serial.println(F("Loading configuration..."));
    loadConfiguration(filename, user);
    
    Serial.printf("nom    : %s\r\n", user.nom);
    Serial.printf("prenom : %s\r\n", user.prenom);
    Serial.printf("age    : %d\r\n", user.age);

    /** Create configuration file
    Serial.println(F("Saving configuration..."));
    saveConfiguration(filename, config);
    **/
    
    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(filename);
    Serial.println("List of files");
    listFiles();
    
}

void loop() {
    // not used in this example
}




