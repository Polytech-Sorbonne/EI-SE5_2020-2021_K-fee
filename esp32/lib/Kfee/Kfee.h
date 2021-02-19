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


    public :

        //Constructeur
        Kfee();

        void init();
        //Setup les capteurs WaterLevel, ainsi que les capteurs de distances
        int setup_i2c_sensors();
        //Setup la pin du sensor de proximité
        void setup_prox_sensor();
        //Setup la pin du relay
        void setup_relay();
        //Setup la vitesse des moteurs
        void setup_motors();
        //Setup le mqtt client
        void setup_pub_sub();
        //Setup wifi
        void setup_wifi();
        //Fonction permettant de mettre nb doses de café dans la tasse
        void putCoffee(int nb);
        //Fonction permettant de mettre nb dose de sucre dans la tasse
        void putSugar(int nb);
        //Remplissage de la tasse selon la taille 1 -> petit, 2 -> grand
        void putWater(int taille);
        //Sensor du niveau d'eau restant
        int getWaterLevelPercent();
        //Quantité du reservoir du café en pourcentage
        int getCoffeeQuantity();
        //Quantité du reservoir de sucre en pourcentage
        int getSugarQuantity();
        //Application
        void callback(char* topic, uint8_t* payload, unsigned int length);
        
        void reconnect();
        //Envoi les données des sensors au serveur web
        void monitoring();
        //Fonction d'acquittement
        void acknowledgement();
        //Renvoi True ou False si il y a une tasse
        int presenceTasse();
        //Run client loop
        void run();
        
        //FONCTIONS DE TESTS

        //test le capteur de niveau d'eau
        void test_water_level();
        //test le capteur de proximité
        void test_capteur_prox();
        //test les capteurs de distance
        void test_capteur_distance();
        //test la communication mqtt avec le server 
        void test_MQTT();
        //test la rotation des moteurs
        void test_motors();
        //Effectue une vidange par la chauffe :
        //taille correspond a la taille du receptacle.
        //Effectue nb remplissage pour vider la cafetiere
        void test_water_emptying(int taille);
       
        
};

#endif