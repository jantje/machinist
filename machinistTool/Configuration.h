/*
 * Configuration.h
 *
 * This file is intended to be madified to the
 * materials used in yor workshop
 *
 *  Created on: 27 mrt. 2018
 *      Author: jan
 */

#pragma once
//to adjust the brightness of the leds change the PWM value below 0->255
#define PWMVALUE 50
//to change the "go down voltage" change the value below
#define BATTERY_TO_LOW_CENTI_VOLTAGE 800
//calculate this value based on your battery and voltage divider
#define BATTERY_MULTIPLYER 1

#define MINIMUM_DIAMETER_IN_MM 1
#define MAXIMUM_DIAMETER_IN_MM 40

//as from blackbook 2nd edition speeds and feeds for HSS twisted drills
enum WorkPieceMaterials {
    stainlessSteel,
    toolsteel,
    castIron,
    malleablIron,
    mildSteel,
//    feecutting, I only have 7 buttons
    aluminium,
    woodPlastic,
    numberOfWorkPieceMaterials
};
enum cutterMaterials {
    hss,
    carbide,
    NumberOfCutterMaterials
};
enum operations {
    drilling,
    turning,
    milling,
    numberOfOperations
};
extern const char *workPieceMaterialNames[numberOfWorkPieceMaterials];
extern const  int twistedDrillCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] ;
extern const  int millingCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] ;
extern const  int turningCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] ;
/*
 * If you want you can set defaults for the material/operation
 * Setting it to numberof will make the leds blink
 */
//#define defaultWorkpieceMaterial numberOfWorkPieceMaterials
//#define defaultCutterMaterial NumberOfCutterMaterials
//#define defaultOperation numberOfOperations
#define defaultWorkpieceMaterial mildSteel
#define defaultCutterMaterial hss
#define defaultOperation drilling
