#include <Wire.h>
#include <Arduino.h>

#pragma once
#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
//#define SERIAL Serial
#endif
 

#define NO_TOUCH       0xFE
#define THRESHOLD      100
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR   0x77

void getHigh12SectionValue(void);
void getLow8SectionValue(void);
void check();
uint8_t get_water_level();
void setup_water_level();

#endif
