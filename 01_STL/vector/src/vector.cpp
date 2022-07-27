/* 
 * File:   vector.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Programme pour tester l'utilisation du conteneur std::vector
 * Created on 27 juillet 2022, 08:25
 */

#include <Arduino.h>
#include <vector>

std::vector<String> monVecteur = {"Bonjour","comment","allez","vous"};

void setup() 
{
  pinMode(02, OUTPUT);
  Serial.begin(115200);
  
  monVecteur.push_back("?");
  
  for (int i=0; i < monVecteur.size() ; i++){
      Serial.print(monVecteur.at(i));
      Serial.print(" | ");
  }
  Serial.print("\n\r");
  
  Serial.println("Setup done");
  
}

void loop() 
{
                      
}
