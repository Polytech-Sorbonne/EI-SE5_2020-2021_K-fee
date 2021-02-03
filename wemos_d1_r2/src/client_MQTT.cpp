
#include "client_MQTT.h"


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char dose[length];
  char monitoring[60];

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    dose[i] = (char)payload[i];
  }
  Serial.println();
  
  Serial.println();

  if(dose[0] == '1'){
    Serial.print("Preparation cafe \n");
    Serial.print("Dose de cafe : ");
    Serial.print(dose[1]);
    Serial.print("\nDose de sucre : ");
    Serial.print(dose[2]);
    Serial.print("\n");
  }

  else if(dose[0] == '2'){
    Serial.print("Preparation the \n");
    Serial.print("Dose de the : ");
    Serial.print(dose[1]);
    Serial.print("\nDose de sucre : ");
    Serial.print(dose[2]);
    Serial.print("\n");
  }

  else if(dose[0] == '3'){
    Serial.print("Preparation chocolat \n");
    Serial.print("Dose de chocolat : ");
    Serial.print(dose[1]);
    Serial.print("\nDose de sucre : ");
    Serial.print(dose[2]);
    Serial.print("\n");
  }

  else{
    Serial.print("preparation inconnu\n");
  }

  float rand_cafe_qtt = random(100);
  float rand_the_qtt = random(100);
  float rand_chocolat_qtt = random(100);
  float rand_sucre_qtt = random(100);

  sprintf(monitoring,"Reservoirs : cafe : %.0f%% ",rand_cafe_qtt);
  client.publish("Monitoring", monitoring);

  sprintf(monitoring,"Reservoirs : the : %.0f%% ",rand_the_qtt);
  client.publish("Monitoring", monitoring);

  sprintf(monitoring,"Reservoirs : chocolat : %.0f%% ",rand_chocolat_qtt);
  client.publish("Monitoring", monitoring);

  sprintf(monitoring,"Reservoirs : sucre : %.0f%% ",rand_sucre_qtt);
  client.publish("Monitoring", monitoring);
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
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
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
  client.loop();
}