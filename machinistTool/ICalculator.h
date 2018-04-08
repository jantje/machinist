/*
 * ICalculator.h
 *
 *  Created on: 18 mrt. 2018
 *      Author: jan
 */

#pragma once
#include "machinistTool.h"

class ICalculator {
    public:
        /*given the cutter material and the workspace material and the diameter of the twisted drill in mm
         calculate the RPM*/
        virtual int calculateRPM(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia)=0;

        /*given the cutter material and the workspace material and the diameter of the twisted drill in mm
         calculate the RPM*/
        virtual int calculatellFeedPer100Revolutions(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia)=0;

        /*
         * Given these info what is the proposed cut of depth
         */
        virtual int calculateCutOfDepth(cutterMaterials cutterMaterial, WorkPieceMaterials workPieceMaterial, int dia)=0;

};

