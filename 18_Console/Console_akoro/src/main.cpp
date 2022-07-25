/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Washington le Mans
 * 
 * Bibliothèque : Console 
 * https://registry.platformio.org/libraries/akoro/Console
 * installation : pio pkg install --library "akoro/Console@^1.2.1"
 * 
 *
 * Created on 20 novembre 2021, 17:42
 */

#include <Arduino.h>
#include <console.h>
#include <driver/adc.h>

#define LED 2


Console laConsole;

void _echo_(ArgList& L, Stream& S);
void _adc_(ArgList& L, Stream& S);
void _led_(ArgList& L, Stream& S);
void _infos_(ArgList& L, Stream& S);
void _unknown(String& L, Stream& S);

void setup() {

    pinMode(LED, OUTPUT);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    Serial.begin(115200);

    while (!Serial)
        yield();  // yield() Passe le contrôle à d'autres tâches

    Serial.println(F("--- test console start"));

    // Console setup
    laConsole.onCmd("echo", _echo_);
    laConsole.onCmd("led", _led_);
    laConsole.onCmd("adc", _adc_);
    laConsole.onCmd("infos", _infos_);
    laConsole.onUnknown(_unknown);

    laConsole.start();

}

void loop() {
    laConsole.run();

}

// command parsing
/******************************************************************/

// Affiche tous les arguments de la ligne de commande

void _echo_(ArgList& L, Stream& S) {

    String p;
    while (!(p = L.getNextArg()).isEmpty())
        S.printf("%s ", p.c_str());
    S.printf("\n\r");
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

void _led_(ArgList& L, Stream& S) {

    String p;

    if (!(p = L.getNextArg()).isEmpty()) {
        if (p.equalsIgnoreCase("ON")) { //
            digitalWrite(LED, HIGH);
            S.printf("LED is now ON\r\n");
        } else if (p.equalsIgnoreCase("OFF")) {
            digitalWrite(LED, LOW);
            S.printf("LED is now OFF\r\n");
        } else {
            S.printf("Unknown argument!\r\n");
        }
    } else {
        S.printf("Usage led ON or OFF\r\n");
    }
}


// Commande inconnue

void _unknown(String& L, Stream & S) {
    S.print("? ");
    S.println(L);
}

void _infos_(ArgList& L, Stream& S) {
    esp_chip_info_t out_info;
    esp_chip_info(&out_info);
    
    S.print("CPU freq : ");
    S.println(String(ESP.getCpuFreqMHz()) + " MHz");
    
    S.print("CPU cores : ");
    S.println(String(out_info.cores));
    
    S.print("Flash size : ");
    S.println(String(ESP.getFlashChipSize() / 1000000) + " MB");
    
    S.print("Free RAM : ");
    S.println(String((long) ESP.getFreeHeap()) + " bytes");
    
    S.print("Min. free seen : "); 
    S.println(String((long)esp_get_minimum_free_heap_size()) + " bytes");
    
    S.print("tsk IDLE_PRIORITY : ");
    S.println(String((long) tskIDLE_PRIORITY));
    
    S.print("config MAX_PRIORITIES : ");
    S.println(String((long) configMAX_PRIORITIES));
    
    S.print("config TICK_RATE_HZ : ");
    S.println(String(configTICK_RATE_HZ) + " Hz");
    
    S.println();
}
