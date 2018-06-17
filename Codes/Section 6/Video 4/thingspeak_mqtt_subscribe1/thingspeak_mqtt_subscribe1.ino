#include <SPI.h>
#include <Ethernet.h> 
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 


char mqttUserName[] = "Makerdemy"; 
char mqttPass[] = "FW3JRPEX7J90NC28";
 
const char* server = "mqtt.thingspeak.com";

EthernetClient client; 
PubSubClient mqttClient(client); 



void setup() { 
  Serial.begin(9600); 
   while(!Serial);
   if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Unable to configure Ethernet using DHCP"));
    for (;;);
  }
  Serial.println("Ethernet configured via DHCP");
  mqttClient.setServer(server, 1883); 
  mqttClient.setCallback(callback);

}

void loop() { 
  
  if (!mqttClient.connected()) 
  {
    reconnect();
  }
  mqttClient.loop(); 
  
}

void reconnect() 
{
  while (!mqttClient.connected()) 
   {
    Serial.print("Attempting MQTT connection...");
    char clientID[]="makerdemy123";
    if (mqttClient.connect(clientID,mqttUserName,mqttPass))
    {
      Serial.print("Connected...");
      if(mqttClient.subscribe("channels/488382/subscribe/fields/field1/WLQB2MHV0OPWWI2T"))
      {
      Serial.println("SUBSCRIBED");
      }
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
     }
  }
}
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("The topic is : ");
  Serial.println(topic);
  Serial.print("The value is : ");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  return;
}


