#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "yourWifi"; 
const char* password = "yourPassword";
const char* mqtt_server = "test.mosquitto.org";// MQTT broker

WiFiclient espclient;
PubSubclient client (espclient);
unsigned long lastMsg = 0; 
char msg[50];
int value = 0;

void setup() {

Serial.begin(115200); 
setup_wifi();
client.setserver (mqtt_server, 1883);
client.setCallback(callback);
}
void setup wifi() {
delay(10);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(",");
}
Serial.println();
Serial.println("WiFi connected...");
Serial.println("IP Adress: ");
Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
  String string;
  Serial.print("Message arrived [");
  Serial.print("topic");
  Serial.print("]");
  for(int i = 0; i < length; i++){
    string += ((char)payload[i]);
  }
  
  if(topic = "/FOTA"){   //Created topic
    Serial.print(string);
    client.publish("/FOTA, Iam ESP");
    delay(15);
  }
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    if(client.connect("ESPClient")){
      Serial.println("connected...");
      client.subscribe("/FOTA");
    }else{
      Serial.print("Failed");
      Serial.print(client.state());
      Serial.println("Try again in 10 seconds...");
      delay(10000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  delay(100);
}
