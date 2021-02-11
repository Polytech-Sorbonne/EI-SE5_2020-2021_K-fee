
#include "client_MQTT.h"
#include "Water_level_sensor.h"
#include "Capteur_distance.h"

char ssid[] = "S20+";
char password[] = "12345678abc";
const char* mqtt_server = "192.168.118.226";

const char* mqtt_username = "mickael"; // MQTT username
const char* mqtt_password = "mickael"; // MQTT password

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("\nMessage arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char dose[length];

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    dose[i] = (char)payload[i];
  }
  Serial.println();
  Serial.println();

  if(dose[0] == '1'){
    Serial.print("Preparation cafe \n");

    Serial.print("Dose de cafe : ");
    dose_cafe(dose[1]);
    
    Serial.print("\nDose de sucre : ");
    dose_sucre(dose[2]);
   
    Serial.print("\nTaille Cafe : ");
    taille_cafe(dose[3]);
  }
  else{
    Serial.print("preparation inconnu\n");
  }
}

void monitoring(){
  Serial.print("Debut monitoring\n");
  char monitoring[60];

  int qtt_cafe = (int)get_qtt_cafe();
  int qtt_sucre = (int)get_qtt_sucre();
  int water_level = (int)get_water_level();

  sprintf(monitoring,"Reservoirs : cafe : %d%%\n",qtt_cafe);
  Serial.print(monitoring);
  client.publish("Monitoring", monitoring);

  sprintf(monitoring,"Reservoirs : sucre : %d%%\n",qtt_sucre);
  Serial.print(monitoring);
  client.publish("Monitoring", monitoring);

  sprintf(monitoring,"Reservoirs : eau : %d%%\n",water_level);
  Serial.print(monitoring);
  client.publish("Monitoring", monitoring);
}

void dose_cafe(char dose){
if(dose == '1'){
    Serial.print("1 rotation dose cafe");
  }
else if(dose == '2'){
    Serial.print("2 rotation dose cafe");
  }
else if(dose == '3'){
    Serial.print("3 rotation dose cafe");
  }
else if(dose == '4'){
    Serial.print("4 rotation dose cafe");
  }
else{
    Serial.print("Dose cafe inconnu\n");
}

}

void dose_sucre(char dose){
if(dose == '1'){
    Serial.print("1 rotation dose sucre");
  }
else if(dose == '2'){
    Serial.print("2 rotation dose sucre");
  }
else if(dose == '3'){
    Serial.print("3 rotation dose sucre");
  }
else if(dose == '4'){
    Serial.print("4 rotation dose sucre");
  }
else{
    Serial.print("Dose sucre inconnu\n");
  }
}

void taille_cafe(char dose){
if(dose == '1'){
  Serial.print("Petit Cafe\n");
  Serial.print("Eau chaude en cours  \n");
  delay(TEMPS_ATTENTE);
  digitalWrite(16, HIGH);
  delay(TEMPS_CAFE_PETIT);
  digitalWrite(16, LOW);
  Serial.print("Fin eau chaude\n");
}

else if(dose == '2'){
  Serial.print("Grand Cafe\n");
  Serial.print("Eau chaude en cours  \n");
  delay(TEMPS_ATTENTE);
  digitalWrite(16, HIGH);
  delay(TEMPS_CAFE_GRAND);
  digitalWrite(16, LOW);
  Serial.print("Fin eau chaude\n");
}
else{
  Serial.print("Taille tasse inconnu\n");
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

void setup_pub_sub() {
Serial.begin(115200);
setup_wifi();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
randomSeed(analogRead(0));
}

void loop_pub_sub() {

  if (!client.connected()) {
    reconnect();
  }
  monitoring();
  client.loop();
}