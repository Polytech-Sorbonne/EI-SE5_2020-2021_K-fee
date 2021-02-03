#ifndef TEST_PUB_SUB_H
#define TEST_PUB_SUB_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

// Update these with values suitable for your network.

const char* ssid = "S20+";
const char* password = "12345678abc";
const char* mqtt_server = "192.168.46.198";

const char* mqtt_username = "mickael"; // MQTT username
const char* mqtt_password = "mickael"; // MQTT password

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_pub_sub();
void loop_pub_sub();

#endif