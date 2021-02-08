#pragma once
#ifndef CLIENT_MQTT_H
#define CLIENT_MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

// Update these with values suitable for your network.

#define TEMPS_CAFE_PETIT 85000
#define TEMPS_CAFE_GRAND 250000
#define TEMPS_ATTENTE 5000

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_pub_sub();
void loop_pub_sub();

#endif