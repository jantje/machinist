/*
 * MedianAnalog.cpp
 *
 *  Created on: 26 mrt. 2018
 *      Author: jan
 */

#include "MedianAnalog.h"

MedianAnalog::MedianAnalog(uint8_t Pin) {
        myPin = Pin;
        my_last_read=0;
}
void MedianAnalog::setup() {
    pinMode(myPin, INPUT); // This may not be needed
    uint16_t myActualReadValue = analogRead(myPin);
    for (int x = 0; x < 5; x++) {
        myValues.addValue(myActualReadValue);
    }
}
void MedianAnalog::loop() {
    //only reed every 100 ms
#ifdef LOOPMILLIS
   extern uint32_t LOOPMILLIS;
#else
#define LOOPMILLIS curMillis
    uint32_t LOOPMILLIS = millis();

#endif
    if (LOOPMILLIS - my_last_read > 10) {
        my_last_read=LOOPMILLIS;
        myValues.addValue( analogRead(myPin));

    }
}
