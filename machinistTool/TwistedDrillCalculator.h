/*
 * TwistedDrillCalculator.h
 *
 *  Created on: 18 mrt. 2018
 *      Author: jan
 */

#pragma once
#include "ICalculator.h"
#include "Configuration.h"

class TwistedDrillCalculator: public ICalculator {
    public:
        int calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);
        ~TwistedDrillCalculator();
};

