/*
 * #####################################
 * #          CODE Kfee                #
 * # Author : Mickael RAMILISON        #
 * # Author : Elyoth HARIAN            #
 * #####################################
 */

 /*
  * ######### LIBRAIRIES ###############
  * 
  * 
  * ######### Capteur_distance #########
  */

#include <VL53L0X.h>
#include <Wire.h>
#include <Stepper.h>

#define VL53_OFFSET 50

int setup_VL53L0X(VL53L0X sensor, VL53L0X sensor2, int SHUTDOWNPIN);
void loop_VL53L0X();
uint8_t get_qtt_cafe(VL53L0X sensor);
uint8_t get_qtt_sucre(VL53L0X sensor);


int setup_VL53L0X(VL53L0X sensor, VL53L0X sensor2, int SHUTDOWNPIN)
{
  
//  //Serial.begin(115200);
//  pinMode(SHUTDOWNPIN, OUTPUT);
//  
//  digitalWrite(SHUTDOWNPIN, LOW);
//
//  sensor.setAddress(0x40);
//  sensor.setTimeout(500);
//  if (!sensor.init())
//  {
//    Serial.println("Failed to detect and initialize sensor 1!");
//    return -1;
//  }
//
//  digitalWrite(SHUTDOWNPIN, HIGH);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    return -1;
  }
#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif

  return 0;
}

// void loop_VL53L0X()
// {
//   Serial.print(sensor.readRangeSingleMillimeters());
//   if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }


//   Serial.println();
// }

uint8_t get_qtt_cafe(VL53L0X sensor){
  Serial.print(sensor.readRangeSingleMillimeters());
  return sensor.readRangeSingleMillimeters();
}

uint8_t get_qtt_sucre(VL53L0X sensor){
  return sensor.readRangeSingleMillimeters();
}

/*
 * ########## Water_level_sensor #######
 */
 
#define NO_TOUCH       0xFE
#define THRESHOLD      100
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR   0x77

void getHigh12SectionValue(void);
void getLow8SectionValue(void);
void check();
uint8_t get_water_level();
void setup_water_level();


unsigned char low_data[8] = {0};
unsigned char high_data[12] = {0};
 

void getHigh12SectionValue(void)
{
  //Serial.print("In get High Section");
  memset(high_data, 0, sizeof(high_data));
  Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
  while (12 != Wire.available()){
    //Serial.print("Wire unavailable");
    }
  
  for (int i = 0; i < 12; i++) {
    high_data[i] = Wire.read();
  }
  delay(10);
}
 
void getLow8SectionValue(void)
{
  //Serial.print("In get low Section");
  memset(low_data, 0, sizeof(low_data));
  Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
  while (8 != Wire.available()){
    //Serial.print("Wire unavailable");
    }
 
  for (int i = 0; i < 8 ; i++) {
    low_data[i] = Wire.read(); // receive a byte as character
  }
  delay(10);
}

//EXAMPLE CODE 
void check()
{
  int sensorvalue_min = 250;
  int sensorvalue_max = 255;
  int low_count = 0;
  int high_count = 0;
  while (1)
  {
    uint32_t touch_val = 0;
    uint8_t trig_section = 0;
    low_count = 0;
    high_count = 0;
    getLow8SectionValue();
    getHigh12SectionValue();
 
    //Serial.println("low 8 sections value = ");
    for (int i = 0; i < 8; i++)
    {
      //Serial.print(low_data[i]);
      //Serial.print(".");
      if (low_data[i] >= sensorvalue_min && low_data[i] <= sensorvalue_max)
      {
        low_count++;
      }
      if (low_count == 8)
      {
        //Serial.print("      ");
        //Serial.print("PASS");
      }
    }
    //Serial.println("  ");
    //Serial.println("  ");
    //Serial.println("high 12 sections value = ");
    for (int i = 0; i < 12; i++)
    {
      //Serial.print(high_data[i]);
      //Serial.print(".");
 
      if (high_data[i] >= sensorvalue_min && high_data[i] <= sensorvalue_max)
      {
        high_count++;
      }
      if (high_count == 12)
      {
        //Serial.print("      ");
        //Serial.print("PASS");
      }
    }
 
    //Serial.println("  ");
    //Serial.println("  ");
 
    for (int i = 0 ; i < 8; i++) {
      if (low_data[i] > THRESHOLD) {
        touch_val |= 1 << i;
 
      }
    }
    for (int i = 0 ; i < 12; i++) {
      if (high_data[i] > THRESHOLD) {
        touch_val |= (uint32_t)1 << (8 + i);
      }
    }
 
    while (touch_val & 0x01)
    {
      trig_section++;
      touch_val >>= 1;
    }
    //Serial.print("water level = ");
    //Serial.print(trig_section * 5);
    //Serial.println("% ");
    //Serial.println(" ");
    //Serial.println("*********************************************************");
    delay(1000);
  }
}

uint8_t get_water_level(){
    int sensorvalue_min = 250;
    int sensorvalue_max = 255;
    int low_count = 0;
    int high_count = 0;
    uint32_t touch_val = 0;
    uint8_t trig_section = 0;
    low_count = 0;
    high_count = 0;
    getLow8SectionValue();
    getHigh12SectionValue();
 
    // Serial.println("low 8 sections value = ");
    for (int i = 0; i < 8; i++)
    {
      //Serial.print(low_data[i]);
      //Serial.print(".");
      if (low_data[i] >= sensorvalue_min && low_data[i] <= sensorvalue_max)
      {
        low_count++;
      }
      if (low_count == 8)
      {
        //Serial.print("      ");
        //Serial.print("PASS");
      }
    }
    //Serial.println("  ");
    //Serial.println("  ");
    //Serial.println("high 12 sections value = ");
    for (int i = 0; i < 12; i++)
    {
      //Serial.print(high_data[i]);
      //Serial.print(".");
 
      if (high_data[i] >= sensorvalue_min && high_data[i] <= sensorvalue_max)
      {
        high_count++;
      }
      if (high_count == 12)
      {
        //Serial.print("      ");
        //Serial.print("PASS");
      }
    }
 
    //Serial.println("  ");
    //Serial.println("  ");
 
    for (int i = 0 ; i < 8; i++) {
      if (low_data[i] > THRESHOLD) {
        touch_val |= 1 << i;
 
      }
    }
    for (int i = 0 ; i < 12; i++) {
      if (high_data[i] > THRESHOLD) {
        touch_val |= (uint32_t)1 << (8 + i);
      }
    }
 
    while (touch_val & 0x01)
    {
      trig_section++;
      touch_val >>= 1;
    }
    //Serial.print("water level = ");
    //Serial.print(trig_section * 5);
    //Serial.println("% ");
    //Serial.println(" ");
    //Serial.println("*********************************************************");
    delay(1000);
    return trig_section * 5;
}

void setup_water_level(){
  //Serial.begin(115200);
  Wire.begin();
}

/*
 * ######### KFEE ############
 */



#define MC0 13
#define MC1 12
#define MC2 14
#define MC3 27
#define MS0 26 
#define MS1 25 
#define MS2 33 
#define MS3 32 

#define SCL 22
#define SDA 21

#define XSHUTi2c 35

#define PROX 34

#define RELAY 23

#define TEMPS_CAFE_PETIT 85000
#define TEMPS_CAFE_GRAND 250000
#define TEMPS_ATTENTE 5000

#define NUMBER_OF_STEP 400
#define DOSECOFFEE NUMBER_OF_STEP*2    //NUMBER OF STEP FOR ONE DOSE
#define DOSESUGAR NUMBER_OF_STEP
#define COFFEE_MOTOR_SPEED 30
#define SUGAR_MOTOR_SPEED 30

#define RESERVE_EMPTY 250

#define WATER_FULL 40


class Kfee {
    private : 

        Stepper coffeeMotor;
        Stepper sugarMotor;
        VL53L0X coffee_sensor;
        VL53L0X sugar_sensor;


    public :

        //Constructeur
        Kfee();

        void init();
        //Setup les capteurs WaterLevel, ainsi que les capteurs de distances
        int setup_i2c_sensors();
        //Setup la pin du sensor de proximité
        void setup_prox_sensor();
        //Setup la pin du relay
        void setup_relay();
        //Setup la vitesse des moteurs
        void setup_motors();
        //Setup le mqtt client
        void setup_pub_sub();
        //Setup wifi
        void setup_wifi();
        //Fonction permettant de mettre nb doses de café dans la tasse
        void putCoffee(int nb);
        //Fonction permettant de mettre nb dose de sucre dans la tasse
        void putSugar(int nb);
        //Remplissage de la tasse selon la taille 1 -> petit, 2 -> grand
        void putWater(int taille);
        //Sensor du niveau d'eau restant
        int getWaterLevelPercent();
        //Quantité du reservoir du café en pourcentage
        int getCoffeeQuantity();
        //Quantité du reservoir de sucre en pourcentage
        int getSugarQuantity();
        //Application
        void callback(char* topic, uint8_t* payload, unsigned int length);
        
        void reconnect();
        //Envoi les données des sensors au serveur web
        void monitoring();
        //Fonction d'acquittement
        void acknowledgement();
        //Renvoi True ou False si il y a une tasse
        int presenceTasse();
        //Run client loop
        void run();
        
        //FONCTIONS DE TESTS

        //test le capteur de niveau d'eau
        void test_water_level();
        //test le capteur de proximité
        void test_capteur_prox();
        //test les capteurs de distance
        void test_capteur_distance();
        //test la communication mqtt avec le server 
        void test_MQTT();
        //test la rotation des moteurs
        void test_motors();
        //Effectue une vidange par la chauffe :
        //taille correspond a la taille du receptacle.
        //Effectue nb remplissage pour vider la cafetiere
        void test_water_emptying(int taille);
       
        
};


Kfee::Kfee():coffeeMotor(NUMBER_OF_STEP, MC0, MC1, MC2, MC3), sugarMotor(NUMBER_OF_STEP, MS0, MS1, MS2, MS3){
    
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
    Serial.print(nb);
    coffeeMotor.step(nb * DOSECOFFEE);
    Serial.print("Fin putCoffee");
}

void Kfee::putSugar(int nb){
    sugarMotor.step(nb * DOSESUGAR);
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
    while(1){
        delay(500);
        Serial.print("Niveau d'eau : ");
        Serial.println(getWaterLevelPercent());
    }
}

void Kfee::test_capteur_prox(){
    //Serial.begin(115200);
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

/*
 * ############# Client MQTT #################
 */

#include <WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.

// Temps reel 
// #define TEMPS_CAFE_PETIT 85000
// #define TEMPS_CAFE_GRAND 250000
// #define TEMPS_ATTENTE 5000
Kfee k;

//Connect la carte au wifi qui le connect au broker mqtt de la raspberry pi
void setup_wifi();

//Fonction de callback qui sera appeler a chaque fois que quelqu'un publish sur un topic auquels on a subscribe
void callback(char* topic, byte* payload, unsigned int length);

//Connecte la carte au brocker et subscribe au topic home/kfee
void reconnect();

//Initialise le serial et appel la fonction setup_wifi() et connect au brocker
void setup_pub_sub();

//Lance la boucle infini 
void loop_pub_sub();

void monitoring();

char ssid[] = "S20+";
char password[] = "12345678abc";
const char* mqtt_server = "192.168.20.226";

const char* mqtt_username = "mickael"; // MQTT username
const char* mqtt_password = "mickael"; // MQTT password

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi(){
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid,password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    delay(500);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    delay(500);
    Serial.println(WiFi.localIP());
    delay(500);
}

void setup_pub_sub() {
//Serial.begin(115200);
setup_wifi();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
randomSeed(analogRead(0));
}

void monitoring(){
  Serial.print("Debut monitoring\n");
  char monitoring[60];
  //int qtt_cafe = k.getCoffeeQuantity();
  //int qtt_sucre = k.getSugarQuantity();
  //int water_level = k.getWaterLevelPercent();
  // 1 c'est pour le café
  //sprintf(monitoring,"1%d",qtt_cafe);
  //Serial.println(monitoring);
  //client.publish("Monitoring", monitoring);
  // 3 c'est pour le sucre
//  sprintf(monitoring,"3%d",qtt_sucre);
//  Serial.println(monitoring);
//  client.publish("Monitoring", monitoring);
  // 2 c'est pour l'eau
  //sprintf(monitoring,"2%d",water_level);
  //Serial.println(monitoring);
  //client.publish("Monitoring", monitoring);
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
  Serial.print("\nMessage arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char monitoring_var[60];
  char dose[length];

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    dose[i] = (char)payload[i];
  }
  Serial.println();
  Serial.println();

  if(dose[0] == '1'){
    if(k.presenceTasse()){
      client.publish("Monitoring" ,"01");
      Serial.print("Preparation cafe \n");
  
      Serial.print("Dose de cafe : ");
      k.putCoffee(dose[1] - 48);
      
      Serial.print("\nDose de sucre : ");
      k.putSugar(dose[2] - 48);
     
      Serial.print("\nTaille Cafe : ");
      k.putWater(dose[3] - 48);

      //monitoring();
    }
    else {
      Serial.print("Il n'y a pas de tasse ! ");
    }
  }
  else if (dose[0] = '2'){
    //monitoring();
    sprintf(monitoring_var,"0%d", k.presenceTasse());
    Serial.println(monitoring_var);
    client.publish("Monitoring", monitoring_var);
  }
  else{
    Serial.print("preparation inconnu\n");
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Monitoring", "Connecte au serveur MQTT");
      // ... and resubscribe
      client.publish("Monitoring", "subscribe to home/kfee");
      client.subscribe("home/kfee");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() { 
  Serial.begin(115200);
  k.init();
  setup_pub_sub();
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
