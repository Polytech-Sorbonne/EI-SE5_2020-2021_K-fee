#include <Kfee.h>

Kfee::Kfee():coffeeMotor(NUMBER_OF_STEP, MC0, MC1, MC2, MC3), sugarMotor(NUMBER_OF_STEP, MS0, MS1, MS2, MS3), client(espClient){
    
}

int Kfee::setup_i2c_sensors(){
    Wire.begin();
    if(!setup_VL53L0X(coffee_sensor, sugar_sensor, XSHUTi2c)){
        return -1;
    }
    return 0;    
}

void Kfee::init(){
    setup_i2c_sensors();
    setup_prox_sensor();
    setup_relay();
    setup_motors();
}

void Kfee::setup_prox_sensor(){
    pinMode(PROX, INPUT);
}

void Kfee::setup_motors(){
    coffeeMotor.setSpeed(COFFEE_MOTOR_SPEED);
    sugarMotor.setSpeed(SUGAR_MOTOR_SPEED);
}
void Kfee::setup_relay(){
    pinMode(RELAY, OUTPUT);
}

void Kfee::putCoffee(int nb){
    coffeeMotor.step(nb * DOSE);
}

void Kfee::putSugar(int nb){
    sugarMotor.step(nb * DOSE);
}

int Kfee::getWaterLevelPercent(){
    return (int)(get_water_level() * 100 / WATER_FULL);
}

int Kfee::getCoffeeQuantity(){
    return (int)(100 - (get_qtt_cafe(coffee_sensor) * RESERVE_EMPTY / 100));
}

int Kfee::getSugarQuantity(){
    return (int)(100 - (get_qtt_cafe(sugar_sensor) * RESERVE_EMPTY / 100));
}

int Kfee::presenceTasse(){
    return !digitalRead(PROX);
}

void Kfee::test_water_level(){
    Serial.begin(115200);
    while(1){
        delay(500);
        Serial.printf("Niveau d'eau : %d%%\n", getWaterLevelPercent());
    }
}

void Kfee::test_capteur_prox(){
    Serial.begin(115200);
    while(1){
        delay(500);
        if(presenceTasse()){
            Serial.println("OBJET DETECTE !");
        }
        else {
            Serial.println("RIEN A L'HORIZON !");
        }
    }
}

void Kfee::putWater(int taille){
    delay(TEMPS_ATTENTE);
    Serial.println("Relay On");
    digitalWrite(RELAY, HIGH);
    switch(taille){
        case 1 : 
        Serial.print("Here!");
            delay(TEMPS_CAFE_PETIT);
            break;
        case 2 :
            delay(TEMPS_CAFE_GRAND);
            break;
        default :
            digitalWrite(RELAY, LOW);
            break;
    }
    digitalWrite(RELAY, LOW);
    Serial.println("Relay Off");
}


void Kfee::test_water_emptying(int taille){
    Serial.println("Start !");
    Serial.printf("First Water Level : %d%%\n", getWaterLevelPercent());
    while(getWaterLevelPercent() > 12){
        delay(TEMPS_ATTENTE * 3);
        putWater(taille);
        Serial.printf("Niveau d'eau : %d%%\n", getWaterLevelPercent());
    }
    return;
}
