#include "biblio.h"

void envoyerFichier(String fichier, Stream &flux) {

    if (SPIFFS.exists(fichier)) {

        File file = SPIFFS.open(fichier, "r");

        // Envoie le contenu du fichier sur le port série
        while (file.available()) {

            flux.write(file.read());

        }
        file.close();

    } else {
        flux.print("Oups le fichier ");
        flux.print(fichier);
        flux.println(" n'existe pas !!!");
    }
}

/**
 * Fonction pour créer la tâche Blink led builtin blue
 * 
 */
void createTaskBlink(void) {

    xTaskCreatePinnedToCore(tacheBlink, // task function
            "taskBlink", // taskname
            8192, // stack size
            NULL, // pointer for task2 parameters
            2, // priority
            NULL, // handle for task
            1 // run in core 1
            );
}




// Tâche pour faire clignoter la led bleu 

void tacheBlink(void * parameter) {

    // setup
    pinMode(LED, OUTPUT);

    // loop
    while (1) {
        digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
        delay(200); // wait for a second
        digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
        delay(1000);
    }
    vTaskDelete(NULL);
}

/**
 * Fonction pour créer la tâche scrutation Clavier
 */
void createTaskClavier(void) {

    xTaskCreatePinnedToCore(taskClavier, // task function
            "taskClavier", // taskname
            8192, // stack size
            NULL, // pointer for task2 parameters
            2, // priority
            NULL, // handle for task
            1 // run in core 1
            );
}

/**
 * @brief Fonction associée à la Tâche Scrutation Clavier 
 * @param pvParameters
 */
static void taskClavier(void *pvParameters) {

    extern TaskHandle_t loopTaskHandle;

    // Déclaration des caractères sur les touches
    char keys[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };

    //affectation des GPIO aux lignes L0, L1, L2, L3 du clavier
    //affectation des GPIO aux colonnes C0, C1, C2 du clavier
#if defined(CONNECTEUR_BAS)  // connecteur en bas

    byte rowPins[4]{32, 33, 25, 26};
    byte colPins[3]{4, 5, 15};

#else   // connecteur en haut

    byte rowPins[4]{26, 25, 33, 32};
    byte colPins[3]{15, 5, 4};

#endif

    Keypad clavier = Keypad((char *) keys, rowPins, colPins, 4, 3);
    Serial.println("Setup Clavier done");

    while (1) {

        char c = clavier.getKey();
        if (c) {
            // Renvoie à la tache principale une notification avec la valeur de la touche
            xTaskNotify(loopTaskHandle, c, eSetValueWithOverwrite);
        }
        delay(10);
    }

}

/*
 * Fonction pour tester les quatre leds couleurs
 */
void chenillard(void) {
    
    extern Led* led;
       
    for(word i=0 ; i< 4; i++ ){
        
        led->allumer(VERT, i); // led 0 verte
        delay(200);
        led->eteindre(i); // led 0 verte  
        
    }
    for(word i=0 ; i< 4; i++ ){
        
        led->allumer(BLEU, i); // led 0 verte
        delay(200);
        led->eteindre(i); // led 0 verte  
        
    }
    for(word i=0 ; i< 4; i++ ){
        
        led->allumer(ROUGE, i); // led 0 verte
        delay(200);
        led->eteindre(i); // led 0 verte  
        
    }
  
}

