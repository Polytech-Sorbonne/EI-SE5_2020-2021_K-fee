#pragma once
#ifndef CLIENT_MQTT_H
#define CLIENT_MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

// Update these with values suitable for your network.

// Temps reel 
// #define TEMPS_CAFE_PETIT 85000
// #define TEMPS_CAFE_GRAND 250000
// #define TEMPS_ATTENTE 5000
Kfee k;

//Connect la carte au wifi qui le connect au broker mqtt de la raspberry pi
void setup_wifi();

//Fonction de callback qui sera appeler a chaque fois que quelqu'un publish sur un topic auquels on a subscribe
void callback(char* topic, byte* payload, unsigned int length);

//Connecte la carte au brocker et subscribe au topic home/kfee
void reconnect();

//Initialise le serial et appel la fonction setup_wifi() et connect au brocker
void setup_pub_sub();

//Lance la boucle infini 
void loop_pub_sub();

#endif