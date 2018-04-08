/*
 * Configuration.cpp
 *
 * This file is intended to be modified to the names and cutting speeds used
 * in your workshop
 *
 *  Created on: 27 mrt. 2018
 *      Author: jan
 */

#include "Configuration.h"

const char *workPieceMaterialNames[numberOfWorkPieceMaterials] = {
    "rvs ",
    "toolstaal ",
    "gietijzer ",
    "brons",
    "zacht staal",
    "aluminium ",
    "hout/plast." };
/*
 * The cutting speed in meters per minute
 * numbers taken from
 * https://littlemachineshop.com/mobile/speeds_feeds.php
 * and black book
 * Basically you see a huge variety of numbers so you should provide your own
 * or start from these and adapt as is fit fir your situation
 * I assume these numbers are without cooling
 */
const int twistedDrillCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] = {
    {
        12,
        11,
        26,
        46,
        29,
        76,
        91 },
    {
        18,
        30,
        61,
        61,
        36,
        84,
        91 } };

const int millingCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] = {
    {
        15,
        15,
        27,
        43,
        27,
        61,
        91 },//No data found
    {
        46,
        46,
        66,
        53,
        107,
        274,
        91 } };//No data found
const int turningCuttingSpeed[NumberOfCutterMaterials][numberOfWorkPieceMaterials] = {
    {
        34,
        30,
        53,
        61,
        46,
        168,
        91 },//No data found
    {
        82,
        114,
        122,
        305,
        244,
        305,
        91 } };//No data found
