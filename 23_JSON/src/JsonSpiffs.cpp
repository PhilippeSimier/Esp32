/* 
 * File:   JsonSpiffs.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 6 août 2022, 21:17
 */

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>  

struct Config {
    char hostname[64];
    int port;
};

const char *filename = "/config.txt"; 
Config config; // <- global configuration object


void loadConfiguration(const char *filename, Config &config);
void saveConfiguration(const char *filename, const Config &config);
void printFile(const char *filename);
void listFiles();

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
    loadConfiguration(filename, config);
    
    Serial.printf("hostname : %s\r\n", config.hostname);
    Serial.printf("port : %d\r\n", config.port);

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


// Loads the configuration from a file

void loadConfiguration(const char *filename, Config &config) {
   
    // Open file for reading
    File file = SPIFFS.open(filename);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use https://arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
        Serial.println(F("Failed to read file, using default configuration"));

    // Copy values from the JsonDocument to the Config
    config.port = doc["port"] | 2731;
    strlcpy(config.hostname, // <- destination
            doc["hostname"] | "example.com", // <- source
            sizeof (config.hostname)); // <- destination's capacity

    // Close the file (Curiously, File's destructor doesn't close the file)
    file.close();
}

// Saves the configuration to a file

void saveConfiguration(const char *filename, const Config &config) {
    // Delete existing file, otherwise the configuration is appended to the file
    SPIFFS.remove(filename);

    // Open file for writing
    File file = SPIFFS.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println(F("Failed to create file"));
        return;
    }

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use https://arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<256> doc;

    // Set the values in the document
    doc["hostname"] = config.hostname;
    doc["port"] = config.port;

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0) {
        Serial.println(F("Failed to write to file"));
    }

    // Close the file
    file.close();
}

// Prints the content of a file to the Serial

void printFile(const char *filename) {
    // Open file for reading
    File file = SPIFFS.open(filename);
    if (!file) {
        Serial.println(F("Failed to read file"));
        return;
    }

    // Extract each characters by one by one
    while (file.available()) {
        Serial.print((char) file.read());
    }
    Serial.println();

    // Close the file
    file.close();
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


