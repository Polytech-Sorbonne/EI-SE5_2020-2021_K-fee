#include <Arduino.h>
#include "client_MQTT.h"
#include "Water_level_sensor.h"
#include "Capteur_distance.h"


void setup() {
  // put your setup code here, to run once:

  //##### Test client MQTT #####
  //setup_pub_sub();
  //##### FIN Test client MQTT #####

  //##### Test Water Level #####
  Serial.begin(115200);
  Wire.begin();
  //##### FIN Test Water Level #####

  //##### Test Capteur distance #####
  setup_VL53L0X();
  //##### FIN Capteur distance #####

  
}

void loop() {
  // put your main code here, to run repeatedly:

  //##### Test client MQTT #####
  //loop_pub_sub();
  //##### FIN Test client MQTT #####

  //##### Test Water Level #####
  //check();
  //##### FIN Test Water Level #####

  //##### Test Capteur distance #####
  //loop_VL53L0X();
  //##### FIN Capteur distance #####

  uint8_t water_level = get_water_level();
  uint16_t capteur_distance = get_distance();
  uint16_t capteur_distance2 = get_distance2(); 
  Serial.printf("water level : %d  capteur distance : %d, capteur_distance2 : %d\n", water_level, capteur_distance, capteur_distance2);
}




