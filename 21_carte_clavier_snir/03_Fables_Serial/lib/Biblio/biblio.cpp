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

void createTaskBridge(void){
    xTaskCreatePinnedToCore(tacheBridge, // task function
            "taskBridge", // taskname
            8192,         // stack size
            NULL,         // pointer for task2 parameters
            2,            // priority
            NULL,         // handle for task
            1             // run in core 1
            );
}

/**
 * Fonction pour créer un pont entre les deux liaisons séries.
 * les caratères reçus sur Serial sont affichés sur l'écran OLED
 * @param parameter
 */
void tacheBridge(void * parameter) {


    extern HardwareSerial com;
    extern Afficheur* afficheur;
    
    char car;


    // loop
    while (1) {
        while (Serial.available() > 0) {
            car = Serial.read();            
            com.write(car);
            afficheur->afficher(car);
        }

        while (com.available() > 0) {
            car = com.read();
            Serial.write(car);
        }
        vTaskDelay(1);
    }
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

    extern TaskHandle_t loopTaskHandle; // Le handle de la loopTask (programme principal)

    // Déclaration des caractères sur les touches
    char keys[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '\n'}
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
 * Fonction pour tester le ruban des leds couleurs
 */
void chenillard(const word nb) {

    extern Led* led;
    extern Afficheur* afficheur;
    word i{0};

    afficheur->afficher("couleur verte");
    led->cheniller(VERT, nb);
    led->chenillerInverse(NOIR, nb);

    afficheur->afficher("couleur Bleue");
    led->cheniller(BLEU, nb);
    led->chenillerInverse(NOIR, nb);

    afficheur->afficher("couleur rouge");
    led->cheniller(ROUGE, nb);
    led->chenillerInverse(NOIR, nb);
    delay(200);
}

void createTaskLed1Led2(void) {
    xTaskCreatePinnedToCore(taskLed1Led2, // task function
            "taskLed1Led2", // taskname
            8192, // stack size
            NULL, // pointer for task2 parameters
            2, // priority
            NULL, // handle for task
            1 // run in core 1
            );

}

/**
 * @brief Tache pour tester les led D1 (GPIO13) et D2 (GPIO12)
 * @param pvParameters
 */
static void taskLed1Led2(void *pvParameters) {

    // setup
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(BP1, INPUT);
    pinMode(BP2, INPUT);
    pinMode(BP3, INPUT);


    // loop
    while (1) {

        bool bp1 = !digitalRead(BP1);
        bool bp2 = !digitalRead(BP2);
        bool bp3 = !digitalRead(BP3);


        digitalWrite(D1, bp1); // turn the LED 
        digitalWrite(D2, bp2 || bp3); // turn the LED
        delay(10);
    }
}

