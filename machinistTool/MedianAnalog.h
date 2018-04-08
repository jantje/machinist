/*
 * MedianAnalog.h
 *
 *  Created on: 26 mrt. 2018
 *      Author: jan
 */

#pragma once
#include "Arduino.h"
#include "FastRunningMedian.h"

class MedianAnalog {
    private:
        uint8_t myPin;
        FastRunningMedian<uint16_t, 5, false> myValues;
        uint32_t my_last_read;
    public:
        MedianAnalog(uint8_t Pin);


        void setup();
        void loop();
        uint16_t getValue() {
            return myValues.getMedian();
        }
};

