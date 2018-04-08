#pragma once

#include "Arduino.h"
#include "Arduino.h"
#include "DebounceButton.h"
#include "LiquidCrystal.h"
#include "BlinkLed.h"
#include "MedianAnalog.h"
#include "VoltMeter.h"
#include "Configuration.h"

void updateDisplay() ;
void updateLeds() ;
int calculateTwistedDrillRPM(cutterMaterials cutterMaterial,WorkPieceMaterials workPieceMaterial,int dia);
int calculateTwistedDrillFeedPer100Revolutions(cutterMaterials cutterMaterial,WorkPieceMaterials workPieceMaterial,int dia);
