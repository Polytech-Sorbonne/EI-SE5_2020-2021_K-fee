#pragma once 
#ifndef KFEE_H
#define KFEE_H

#include <Arduino.h>
#include <Water_level_sensor.h>
#include <Stepper.h>
#include <client_MQTT.h>
#include <Capteur_distance.h>

#define MC0 13
#define MC1 12
#define MC2 14
#define MC3 27
#define MS0 26 
#define MS1 25 
#define MS2 33 
#define MS3 32 

#define SCL 22
#define SDA 21

#define XSHUTi2c 35

#define PROX 34

#define RELAY 23

#define TEMPS_CAFE_PETIT 85000
#define TEMPS_CAFE_GRAND 250000
#define TEMPS_ATTENTE 5000

#define NUMBER_OF_STEP 400
#define DOSE NUMBER_OF_STEP*2    //NUMBER OF STEP FOR ONE DOSE
#define COFFEE_MOTOR_SPEED 30
#define SUGAR_MOTOR_SPEED 30

#define RESERVE_EMPTY 250

#define WATER_FULL 40


class Kfee {
    private : 

        Stepper coffeeMotor;
        Stepper sugarMotor;
        VL53L0X coffee_sensor;
        VL53L0X sugar_sensor;
        WiFiClient espClient;
        PubSubClient client;


    public :

        Kfee();
        int setup_i2c_sensors();
        void setup_prox_sensor();
        void setup_motors();
        void putCoffee(int nb);
        void putSugar(int nb);
        void putWater(int taille);
        int getWaterLevelPercent();
        int getCoffeeQuantity();
        int getSugarQuantity();
        int run();
        void monitoring();
        void acknowledgement();
        int presenceTasse();
        void test_water_level();
        void test_capteur_prox();
        void test_capteur_distance();
        void test_MQTT();
        void test_motors();
        void test_water_emptying(int taille);
       
        
};

#endif