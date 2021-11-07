/* 
 * File:   MsdCard.h
 * Author: philippe SIMIER Touchard Washington Le Mans
 *
 * Created on 1 novembre 2021, 15:57
 */

#ifndef MSDCARD_H
#define MSDCARD_H

#include <SPI.h>
#include <SD.h>
#include <FS.h>

class MsdCard {
public:
    MsdCard(uint8_t sckPin = 18,
            uint8_t misoPin = 19,
            uint8_t mosiPin = 23,
            uint8_t csPin = 5);

    MsdCard(const MsdCard& orig);
    virtual ~MsdCard();

    bool begin();
    
    bool ls(const char * path);
    void fwrite(const char * path,  const char * message);
    void fputs(const char * path, const char * message);
    void fread(const char * path);
    bool mv(const char * path1, const char * path2);
    bool mkdir (const char * path);
    bool rmdir (const char * path);

private:
    int chipSelect;
    void _ls(File dir, int numTabs);
};

#endif /* MSDCARD_H */

