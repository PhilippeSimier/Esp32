/*
 * Essai d'affichage avec management de 4 pages avec défillement
 * 
 */
#include <Afficheur.h>          // Afficheur SSD1306

Afficheur *afficheur;

void setup() {
    //nvs_flash_erase(); // erase the NVS partition and...
    //nvs_flash_init(); // initialize the NVS partition.
    Serial.begin(115200);
    afficheur = new Afficheur;

}

void loop() {

    int remainingTimeBudget = afficheur->update();

    if (remainingTimeBudget > 0) {
        /*
         * Vous pouvez faire du travail ici. 
         * Ne faites rien si vous êtes en dessous de votre budget temps.
         */
        delay(remainingTimeBudget);
    }
}
    