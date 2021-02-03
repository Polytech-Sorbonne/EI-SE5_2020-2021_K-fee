#include <Arduino.h>
#include <Water_level_sensor.h>
#include <Stepper.h>
#include <VL53L0X.h>


#define MC0 5 //D1
#define MC1 4 //D2
#define MC2 0 //D3
#define MC3 2 //D4
#define MS0 14 //D5
#define MS1 12 //D6
#define MS2 13 //D7
#define MS3 15 //D8

#define SCL 5
#define SDA 4

#define NUMBER_OF_STEP 200

bool debug_flag = false; //enable it to view debug print on serial

class Kfee {
    private : 

        Stepper coffeeMotor;
        Stepper sugarMotor;
        VL53L0X coffee_sensor;
        VL53L0X sugar_sensor;

    public :

        Kfee();
        int putCoffee(int nb);
        int putSugar(int nb);
        int getWaterLevelPercent();
        int getCoffeeQuantity();
        int getSugarQuantity();
        void setDebugFlag(bool boolean);
        int run();
        int sendValuesToServer();
        
};