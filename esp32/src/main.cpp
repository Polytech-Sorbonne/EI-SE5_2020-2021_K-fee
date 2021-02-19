#include <Arduino.h>
#include <client_MQTT.h>

#include <WiFi.h>

WiFiClient client;

void setup() { 
  k.init();
  setup_pub_sub();
}

void loop() {
  
  loop_pub_sub();
  
}




