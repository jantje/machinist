/*
 * TwistedDrillCalculator.cpp
 *
 *  Created on: 18 mrt. 2018
 *      Author: jan
 */

#include "TwistedDrillCalculator.h"






int TwistedDrillCalculator::calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    float cuttingSpeed = twistedDrillCuttingSpeed[cutterMaterial][workPieceMaterial] * 1000.0;
    float diaInmm = dia;
    float pi = 3.1415;
    float ret=cuttingSpeed / (diaInmm * pi);
    return (int) ret;
}

int TwistedDrillCalculator::calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    switch (cutterMaterial) {
        case hss:
            if (dia < 3) return 2;
            if (dia < 6) return 5;
            if (dia < 13) return 10;
            if (dia < 25) return 20;
            return 40;
        case carbide:
            if (dia < 3) return 2;
            if (dia < 6) return 5;
            if (dia < 13) return 10;
            if (dia < 25) return 20;
            return 40;
        default:
            break;

    }
    //this should not happen
    return -1;
}

/*
 * This method does not make sense for a twisted drill
 */
int TwistedDrillCalculator::calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    return -1;
}

TwistedDrillCalculator::~TwistedDrillCalculator() {
}
