#include <biblio.h>

// Loads the configuration from a file
void loadConfiguration(const char *filename, User &user) {
   
    // Open file for reading
    File file = SPIFFS.open(filename);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use https://arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error){
        Serial.println(F("Failed to read file, using default configuration"));
        Serial.println(error.f_str());
    }
    // Copy values from the JsonDocument to the Config
    user.age = doc["age"] | 27;
    strlcpy(user.nom, // <- destination
            doc["nom"] | "Dupond", // <- source
            sizeof (user.nom)); // <- destination's capacity
    strlcpy(user.prenom, // <- destination
            doc["prenom"] | "Jean", // <- source
            sizeof (user.prenom)); // <- destination's capacity
    // Close the file (Curiously, File's destructor doesn't close the file)
    file.close();
}

// Saves the configuration to a file

void saveConfiguration(const char *filename, const User &user) {
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
    doc["nom"] = user.nom;
    doc["prenom"] = user.prenom;
    doc["age"] = user.age;
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


