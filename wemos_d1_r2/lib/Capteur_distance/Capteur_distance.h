#pragma once
#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include <VL53L0X.h>
#include <Wire.h>

#define VL53_OFFSET 50

int setup_VL53L0X(VL53L0X sensor, VL53L0X sensor2, int SHUTDOWNPIN);
void loop_VL53L0X();
uint8_t get_qtt_cafe(VL53L0X sensor);
uint8_t get_qtt_sucre(VL53L0X sensor);

#endif