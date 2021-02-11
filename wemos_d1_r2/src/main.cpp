#include <Arduino.h>
#include <Kfee.h>

Kfee k;

void setup() { 
  k.setup_i2c_sensors();
  Serial.begin(115200);
}

void loop() {
  k.test_water_emptying(1);
}




