/*
 * DebounceButton.cpp
 *
 *  Created on: 16 mrt. 2018
 *      Author: jan
 */

#include "DebounceButton.h"

DebounceButton::DebounceButton(uint8_t pin) {
    myPin = pin;
    last_bumperread=0;
}

void DebounceButton::setup() {
    pinMode(myPin, INPUT_PULLUP);
}

void DebounceButton::loop() {
#ifdef LOOPMILLIS
   extern uint32_t LOOPMILLIS;
#else
#define LOOPMILLIS curMillis
    uint32_t LOOPMILLIS = millis();

#endif
    if (LOOPMILLIS - last_bumperread > 30) {
        last_bumperread = LOOPMILLIS;
        myButton.addValue(digitalRead(myPin) == LOW);

    }
}
