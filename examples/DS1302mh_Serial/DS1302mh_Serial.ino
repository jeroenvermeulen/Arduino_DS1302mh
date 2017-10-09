/*
 * DS1302mh - library for the DS1302 RTC
 *
 * Inspired on:
 *    https://playground.arduino.cc/Main/DS1302
 *    https://github.com/msparks/arduino-ds1302
 *    https://github.com/iot-playground/Arduino/tree/master/external_libraries/DS1302RTC
 */

#include "DS1302mh.h"

#define DS1302_CE_PIN    6    // Arduino pin for the Chip Enable (Reset)
#define DS1302_IO_PIN    7    // Arduino pin for the Data I/O
#define DS1302_SCLK_PIN  8    // Arduino pin for the Serial Clock

DS1302mh rtc(DS1302_CE_PIN, DS1302_IO_PIN, DS1302_SCLK_PIN);

void setup()
{      
  Serial.begin(9600);
  Serial.println(F("DS1302 Real Time Clock"));

  // Set a time and date
  // Day of week (dow) counts 1...7, Monday is 2nd day of Week.

  //          sec min hrs, dow, day, month, year
  rtc.setTime(0,  35, 17,  2,   9,   10,    2017);
}


void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());  

  delay( 1000);
}

