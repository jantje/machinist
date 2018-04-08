/*
 * TurnCalculator.h
 *
 *  Created on: 31 mrt. 2018
 *      Author: jan
 */

#ifndef TURNCALCULATOR_H_
#define TURNCALCULATOR_H_

#include "ICalculator.h"


class TurnCalculator: public ICalculator  {
    public:
        int calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

        int calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia);

};

#endif /* TURNCALCULATOR_H_ */
