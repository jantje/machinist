/*
 * TurnCalculator.cpp
 *
 *  Created on: 31 mrt. 2018
 *      Author: jan
 */

#include "TurnCalculator.h"

#include "Configuration.h"

int TurnCalculator::calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    float cuttingSpeed =turningCuttingSpeed[cutterMaterial][workPieceMaterial] * 1000.0;
    float diaInmm = dia;
    float pi = 3.1415;
    float ret=cuttingSpeed / (diaInmm * pi);
    return (int) ret;
}

int TurnCalculator::calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    return -1;
}

int TurnCalculator::calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    return -1;
}
