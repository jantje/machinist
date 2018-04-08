/*
 * MillCalculator.cpp
 *
 *  Created on: 31 mrt. 2018
 *      Author: jan
 */

#include "MillCalculator.h"
#include "Configuration.h"

int MillCalculator::calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    float cuttingSpeed =millingCuttingSpeed[cutterMaterial][workPieceMaterial] * 1000.0;
    float diaInmm = dia;
    float pi = 3.1415;
    float ret=cuttingSpeed / (diaInmm * pi);
    return (int) ret;
}

int MillCalculator::calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    return -1;
}

int MillCalculator::calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia) {
    return -1;
}
