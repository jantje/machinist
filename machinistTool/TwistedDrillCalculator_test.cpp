/*
 * TwistedDrillCalculator_test.cpp
 *
 *  Created on: 18 mrt. 2018
 *      Author: jan
 */
#ifdef UNITTEST
#include "gtest.h"
#include "TwistedDrillCalculator.h"
#define RES * 0.07
TEST(twistedDrill, rpm) {
    TwistedDrillCalculator calc;
//    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,1.5),6112,60);
//    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,2.5),4073,40);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,3),3056,3056 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,4),2445, 2445  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,5),2037, 2037 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,6),1637, 1637 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,7),1358, 1358 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,8),1222, 1222 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,9),1120, 1120 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,10),1019,1019 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,16),611,  611 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,20),473,  473 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,25),382,  382 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,28),340,  340 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,35),278,  278 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,41),235,  235 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,44),218,  218 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,50),191,  191 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, mildSteel,76),127,  127 RES);


    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,3), 3180, 3180 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,4), 2390, 2390 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,5), 1910, 1910 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,6), 1590, 1590 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,8), 1190, 1190 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,10),950,  950 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, mildSteel,12),800,  800 RES);


    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,3), 1833, 1833 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,4), 1467, 1467 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,5), 1222, 1222 RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,6), 982 , 982  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,7), 815 , 815  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,8), 733 , 733  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,9), 672 , 672  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,10),611 , 611  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,16),367 , 367  RES);
 //   EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,20),224 , 224  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,25),229 , 229  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,28),204 , 204  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,35),167 , 167  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,41),141 , 141  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,44),131 , 131  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,50),115 , 115  RES);
    EXPECT_NEAR( calc.calculateRPM(hss, toolsteel,76),76  , 76    RES);


    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,3), 1590, 1590 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,4), 1190, 1190 RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,5), 950 , 950  RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,6), 800 , 800  RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,8), 600 , 600  RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,10),480 , 480  RES);
    EXPECT_NEAR( calc.calculateRPM(carbide, toolsteel,12),400 , 400  RES);

}

#endif
