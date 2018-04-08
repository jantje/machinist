/*
 * MillCalculator.h
 *
 *  Created on: 31 mrt. 2018
 *      Author: jan
 */

#ifndef MILLCALCULATOR_H_
#define MILLCALCULATOR_H_

#include "ICalculator.h"

class MillCalculator: public ICalculator {
    public:
        int calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

};

#endif /* MILLCALCULATOR_H_ */
