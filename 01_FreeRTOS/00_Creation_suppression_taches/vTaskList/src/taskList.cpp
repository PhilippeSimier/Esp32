/* 
 * File:   taskList.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 3 août 2022, 12:53
 */

#include <Arduino.h>


char ptrTaskList[500];

void setup() {

    Serial.begin(115200);
    Serial.println(F("In Setup function"));
}

void loop() {
    
    Serial.println(F("Loop function"));
    delay(10000);
    vTaskList(ptrTaskList);
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));
}


