#pragma once
#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include <VL53L0X.h>
#include <Wire.h>


void setup_VL53L0X();
void loop_VL53L0X();
uint8_t get_distance();
uint8_t get_distance2();

#endif