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

// // Temps Debug
#define TEMPS_CAFE_PETIT 8500
#define TEMPS_CAFE_GRAND 25
#define TEMPS_ATTENTE 50

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void dose_cafe(char dose);
void dose_sucre(char dose);
void taille_cafe(char dose);
void monitoring();
void reconnect();
void setup_pub_sub();
void loop_pub_sub();

#endif