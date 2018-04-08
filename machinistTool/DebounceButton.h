/*
 * DebounceButton.h
 *
 *  Created on: 16 mrt. 2018
 *      Author: jan
 */

#pragma once
#include "Arduino.h"
#include "FastRunningMedian.h"

class DebounceButton {
private:
	FastRunningMedian<uint8_t, 5, false> myButton;
	uint8_t myPin;
	uint32_t last_bumperread;
public:
	DebounceButton(uint8_t pin);
	void setup();
	void loop();
	bool isPushed(){return myButton.getMedian();};

};

