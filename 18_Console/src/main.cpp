/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Washington le Mans
 * 
 * Bibliothèque : Console 
 * installation : pio lib -g install "akoro/Console@^1.2.1"
 * 
 * Avec netbeans ajouter dans Tools -> Options -> C/C++ ->  code assistance
 * le chemin vers la library
 * /home/philippe/.platformio/lib/Console/src
 *
 * Created on 20 novembre 2021, 17:42
 */

#include <Arduino.h>
#include <console.h>
#include <driver/adc.h>

#define LED 2

void tacheUne(void * parameter) {
    while (1) {
        digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
        delay(200); // wait for a second
        digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
        delay(1000);
    }
    vTaskDelete(NULL);
}

// command parsing
/******************************************************************/

// Affiche tous les arguments de la ligne de commande

void _test_(ArgList& L, Stream& S) {
    String p;
    int i = 0;
    while (!(p = L.getNextArg()).isEmpty())
        S.printf("arg%d = \"%s\"\n", i++, p.c_str());
}

// Affiche les entrées analogiques et les capteurs

void _adc_(ArgList& L, Stream& S) {
    for (int i = 0; i < 8; i++) {
        uint16_t val = adc1_get_raw(ADC1_CHANNEL_6);
        S.printf("%2d: V = %d\t", i, val);
        val = hall_sensor_read();
        S.printf("H = %d\t", val);
        float t = temperatureRead();
        S.printf("t = %0.1f°C\r\n", t);
    }
}

// Allume ou éteind la led 

void _led_(ArgList& L, Stream&) {
    String p = L.getNextArg();
    if (p == "1")
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW);
}

// Commande inconnue

void _unknown(String& L, Stream& S) {
    S.print("? ");
    S.println(L);
}


Console con;

void setup() {

    pinMode(LED, OUTPUT);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    Serial.begin(115200);

    while (!Serial)
        yield();

    Serial.println(F("--- test console start"));

    Serial.printf("F=%dMHz Heap=%d %02X\r\n",
            ESP.getCpuFreqMHz(),
            ESP.getHeapSize(),
            ESP.getChipRevision());

    Serial.printf("FCS=%d FCS=%dHz FCM=%d\r\n",
            ESP.getFlashChipSize(),
            ESP.getFlashChipSpeed(),
            ESP.getFlashChipMode()); // 0=QIO, 1=QOUT, 2=DIO, 3=DOUT

    // Console setup
    con.onCmd("test", _test_);
    con.onCmd("led", _led_);
    con.onCmd("adc", _adc_);
    con.onUnknown(_unknown);

    /**
    con.onUnknown([](String& L, Stream & S) {
        S.print("? "); S.println(L);
    });
     */

    con.start();
    xTaskCreate(
            tacheUne, /* Task function. */
            "TacheUne", /* String with name of task. */
            10000, /* Stack size in words. */
            NULL, /* Parameter passed as input of the task */
            1, /* Priority of the task. */
            NULL); /* Task handle. */
}

void loop() {
    con.run();

}

