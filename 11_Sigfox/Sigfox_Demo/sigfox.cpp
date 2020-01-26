#include "sigfox.h"

//Message buffer
uint8_t msg[12];

Sigfox::Sigfox (uint8_t rxPin=26 , uint8_t txPin=27, bool debugEn=true) {
	serialSig = new HardwareSerial(2);
  rx = rxPin;
  tx = txPin;
  debug = debugEn;
}

// Lecture des datas reçu sur la liaison série HardwareSerial 
String Sigfox::obtenirData(void){
  String data = "";
  char output;

  while (!serialSig->available()){
    delay(100);
  }

  while(serialSig->available()){
    output = serialSig->read();
    if ((output != 0x0A) && (output != 0x0D)){       //0x0A Line feed | 0x0D Carriage return
      data += output;
      }
    delay(10);
  } 
  return data;  
}

// Initialise la liaison avec le composant Sigfox
void Sigfox::begin(){

	serialSig->begin(9600, SERIAL_8N1, rx, tx);

	if (debug) {
		Serial.begin(9600);
		delay(100);
    tester();
    delay(100);
		obtenirID();
		delay(100);
		obtenirPAC();
	}
}

//Méthode pour obtenir l'identifiant Sigfox
String Sigfox::obtenirID(){
	serialSig->print("AT$I=10\r");
	String id = obtenirData();

	if(debug){
		Serial.print("ID: ");
		Serial.println(id);
	}

	return id;
}


//Méthode pour obtenir le PAC number
String Sigfox::obtenirPAC(){
	serialSig->print("AT$I=11\r");
	String pac = obtenirData();

	if(debug){
		Serial.print("PAC: ");
		Serial.println(pac);
	}

	return pac;
}

//Méthode pour obtenir la température du module
uint16_t Sigfox::obtenirTemp(void){
	serialSig->print("AT$T?\r");
	uint16_t tempVal = obtenirData().toInt();

	if(debug){
		Serial.print("Module temperature : ");
		Serial.println(tempVal);
	}

	return tempVal;
}

/** Méthode pour tester le composant 
 *  la commande AT renvoie OK
 */

 String Sigfox::tester(){
  serialSig->print("AT\r");
  String status = obtenirData();

  if(debug){
    Serial.print("Status : ");
    Serial.println(status);
  }

  return status;
}

/**
 * Méthode pour envoyer des data
 * data un tableau de 12 octets au maximum
 * size le nombre d'octet à envoyer
 * retourne vrai si le message a été envoyé avec success
 */
bool Sigfox::envoyer(const void* data, uint8_t size){   
  String status = "";
  char output;

  uint8_t* bytes = (uint8_t*)data;

  serialSig->print("AT$SF=");
  if(debug) { Serial.print("Byte : "); }
  for(uint8_t i= 0; i<size; ++i){
    serialSig->print(bytes[i] < 16 ? "0" : "");
    serialSig->print(bytes[i], HEX);
    
    if(debug){
      Serial.print(bytes[i] < 16 ? "0" : "");     
      Serial.print(bytes[i], HEX);
    }
  }
  if(debug) { Serial.println(" "); }
  serialSig->print("\r");

  String res = obtenirData();

  if(res.indexOf("OK") >= 0) {
    Serial.println("Message envoyé avec succès");
    return true;
  }
  
  if(debug){
    Serial.print("Status : ");
    Serial.println(res);
  }
  return false;
}
