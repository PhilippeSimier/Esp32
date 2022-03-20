/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * pio lib search "header:ESP32Time.h"
 * 
 * pio lib -g install 11703
 */

#include <Arduino.h>
#include <ESP32Time.h>

ESP32Time rtc;

void setup() {
    
    Serial.begin(115200);
    rtc.setTime(30, 24, 15, 20, 3, 2022); // 20th Mars 2022 15:24:30
    //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00

    /*---------set with NTP---------------*/
    //  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    //  struct tm timeinfo;
    //  if (getLocalTime(&timeinfo)){
    //    rtc.setTimeStruct(timeinfo); 
    //  }

}

void loop() {
    //  Serial.println(rtc.getTime());          //  (String) 15:24:38
    //  Serial.println(rtc.getDate());          //  (String) Sun, Jan 17 2021
    //  Serial.println(rtc.getDate(true));      //  (String) Sunday, January 17 2021
    //  Serial.println(rtc.getDateTime());      //  (String) Sun, Jan 17 2021 15:24:38
    //  Serial.println(rtc.getDateTime(true));  //  (String) Sunday, January 17 2021 15:24:38
    //  Serial.println(rtc.getTimeDate());      //  (String) 15:24:38 Sun, Jan 17 2021
    //  Serial.println(rtc.getTimeDate(true));  //  (String) 15:24:38 Sunday, January 17 2021
    //
    //  Serial.println(rtc.getMicros());        //  (long)    723546
    //  Serial.println(rtc.getMillis());        //  (long)    723
    //  Serial.println(rtc.getEpoch());         //  (long)    1609459200
    //  Serial.println(rtc.getSecond());        //  (int)     38    (0-59)
    //  Serial.println(rtc.getMinute());        //  (int)     24    (0-59)
    //  Serial.println(rtc.getHour());          //  (int)     3     (0-12)
    //  Serial.println(rtc.getHour(true));      //  (int)     15    (0-23)
    //  Serial.println(rtc.getAmPm());          //  (String)  pm
    //  Serial.println(rtc.getAmPm(true));      //  (String)  PM
    //  Serial.println(rtc.getDay());           //  (int)     17    (1-31)
    //  Serial.println(rtc.getDayofWeek());     //  (int)     0     (0-6)
    //  Serial.println(rtc.getDayofYear());     //  (int)     16    (0-365)
    //  Serial.println(rtc.getMonth());         //  (int)     0     (0-11)
    //  Serial.println(rtc.getYear());          //  (int)     2021

    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); // (String) returns time with specified format 
    // formating options  http://www.cplusplus.com/reference/ctime/strftime/

    //struct tm timeinfo = rtc.getTimeStruct();
    //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");   //  (tm struct) Sunday, January 17 2021 07:24:38

    delay(1000);
}

