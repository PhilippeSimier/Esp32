/* 
 * File:   optional.cpp
 * Author: philippe SIMIER Lycée touchard Le Mans
 *
 * Created on 12 août 2022, 15:11
 */

#include <Arduino.h>
#include <Article.h>

void afficher(Article &a);

void setup() {

    Serial.begin(115200);
    while (!Serial)
        continue;

    Article article1 {"Module ESP32-CAM", 14.90};
    Article article2 {"Espressif"};
    Article article3 {"Documentation", 0.0 };
    
    afficher(article1);
    afficher(article2);
    afficher(article3);
    
    article2.setPrix(5.3);
    afficher(article2);
}

void loop() {

}

void afficher(Article &a){
    
    std::cout << "Article " << a.getLibelle() << std::endl;
    auto prix = a.getPrix();
    if (prix) {
        std::cout << "  Prix : " << *prix << " €" << std::endl;
    } else {
        std::cout << "  Pas de prix pour cet article" << std::endl;
    }
    
}

