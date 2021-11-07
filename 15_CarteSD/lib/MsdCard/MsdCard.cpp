/* 
 * File:   MsdCard.cpp
 * Author: philippe  SIMIER Touchard Washington Le Mans
 * 
 * Created on 1 novembre 2021, 15:57
 */

#include "MsdCard.h"

/**
 * Le constructeur
 * @param sckPin
 * @param misoPin
 * @param mosiPin
 * @param ssPin
 */
MsdCard::MsdCard(uint8_t sckPin, uint8_t misoPin, uint8_t mosiPin, uint8_t csPin) {

    SPI.begin(sckPin, misoPin, mosiPin, csPin);
    chipSelect = csPin;
    delay(10);
}

MsdCard::MsdCard(const MsdCard& orig) {
}

MsdCard::~MsdCard() {
}

bool MsdCard::begin() {

    bool retour;
    // L'instance SDFileSystem de la classe SDFS est créé dans le fichier inclus SD.h
    if (SDFileSystem.begin(chipSelect)) {

        Serial.println("Wiring is correct and a card is present.");
        Serial.println();

        Serial.print("Card type: ");
        switch (SDFileSystem.cardType()) {
            case CARD_NONE:
                Serial.println("NONE");
                break;
            case CARD_MMC:
                Serial.println("MMC");
                break;
            case CARD_SD:
                Serial.println("SD");
                break;
            case CARD_SDHC:
                Serial.println("SDHC");
                break;
            default:
                Serial.println("Unknown");
        }


        uint64_t cardSize = SDFileSystem.cardSize() / (1024 * 1024);
        Serial.printf("SD Card Size: %llu Mb\r\n", cardSize);

        uint64_t totalBytes = SDFileSystem.totalBytes() / (1024 * 1024);
        Serial.printf("Total bytes : %llu Mb\r\n", totalBytes);

        uint64_t usedBytes = SDFileSystem.usedBytes() / 1024;
        Serial.printf("Used bytes  : %llu Kb\r\n\n", usedBytes);

        retour = true;


    } else {
        Serial.println("Initialization failed.");
        retour = false;
    }

    return retour;
}

bool MsdCard::ls(const char * path) {
    Serial.println("List  information  about  the files");
    File racine = SDFileSystem.open(path);
    if (!racine) {
        Serial.println("Failed to open directory");
        return false;
    }else{
        MsdCard::_ls(racine, 0); //Liste les fichiers et repertoires présents à la racine
        return true;
    }
}

void MsdCard::_ls(File dir, int numTabs) {
    while (true) {

        File entry = dir.openNextFile();
        if (!entry) {
            break; // no more files
        }

        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            _ls(entry, numTabs + 1);
        } else {
            // files have sizes, directories do not
            // Affichage des propriétés du fichier
            Serial.print("\t");
            Serial.print(entry.size(), DEC);
            time_t lw = entry.getLastWrite();
            struct tm * tmstruct = localtime(&lw);
            Serial.printf("\t %d-%02d-%02d %02d:%02d:%02d\r\n",
                    (tmstruct->tm_year) + 1900,
                    (tmstruct->tm_mon) + 1,
                    tmstruct->tm_mday,
                    tmstruct->tm_hour,
                    tmstruct->tm_min,
                    tmstruct->tm_sec
                    );
        }
        entry.close();
    }
}

void MsdCard::fwrite(const char* path, const char* message) {
    
    File file = SDFileSystem.open(path, FILE_WRITE);
    
    if (file.print(message)) {
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void MsdCard::fputs(const char* path, const char* message){
    
    File file = SDFileSystem.open(path, FILE_APPEND);
    
    if (!file) {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message)) {
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
 }

/**
 * @brief Create the DIRECTORY, if they don't already exist.
 * @param path le chemin du répertoire à créer
 */
bool MsdCard::mkdir (const char * path){
    Serial.printf("make directory: %s\r\n", path);
    if (SDFileSystem.mkdir(path)) {
        Serial.println("Dir created");
        return true;
    } else {
        Serial.println("mkdir failed");
        return false;
    }  
}

/**
 * @brief remove empty directories
 * @param path
 * @return true if success
 */
bool MsdCard::rmdir (const char * path){
    Serial.printf("Removing Dir: %s\r\n", path);
    if (SDFileSystem.rmdir(path)) {
        Serial.println("Dir removed");
        return true;
    } else {
        Serial.println("rmdir failed");
        return false;
    }
}

/**
 * @brief Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.
 * @param path1 SOURCE
 * @param path2 DEST
 * @return 
 */
bool MsdCard::mv(const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (SDFileSystem.rename(path1, path2)) {
        Serial.println("File renamed");
        return true;
    } else {
        Serial.println("Rename failed");
        return false;
    }
}

void MsdCard::fread(const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = SDFileSystem.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

