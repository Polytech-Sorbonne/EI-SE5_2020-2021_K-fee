#include <Arduino.h>
#include "client_MQTT.h"
#include "Water_level_sensor.h"

void setup() {
  // put your setup code here, to run once:

  //##### Test client MQTT #####
  //setup_pub_sub();
  //##### FIN Test client MQTT #####

  //##### Test Water Level #####
  Serial.begin(115200);
  Wire.begin();
  //##### FIN Test Water Level #####

}

void loop() {
  // put your main code here, to run repeatedly:

  //##### Test client MQTT #####
  //loop_pub_sub();
  //##### FIN Test client MQTT #####

  //##### Test Water Level #####
  check();
  //##### FIN Test Water Level #####
}