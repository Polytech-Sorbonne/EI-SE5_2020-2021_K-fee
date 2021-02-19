#include <Arduino.h>
#include <client_MQTT.h>

void setup() { 
  k.init();
  setup_pub_sub();
}

void loop() {
  
  loop_pub_sub();
  
}




