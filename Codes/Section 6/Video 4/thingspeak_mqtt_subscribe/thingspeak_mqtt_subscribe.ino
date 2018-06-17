#include <SPI.h>
#include <Ethernet.h> 
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 


char mqttUserName[] = "Makerdemy"; 
char mqttPass[] = "FW3JRPEX7J90NC28";
 
const char* server = "mqtt.thingspeak.com";

const char* f1 = "field1";
const char* f2 = "field2";
const char* f3 = "field3";
const char* f4 = "field4";

const long channelID = 488382;


char readAPIKey[] = "WLQB2MHV0OPWWI2T";

EthernetClient client; 
PubSubClient mqttClient(client); 



void setup() { 
  Serial.begin(9600); 
  
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
      if(mqttsubscribe(channelID,3,readAPIKey)==1)
      {
      Serial.println("SUBSCRIBED");
      }
      else 
      {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      }
      if(mqttsubscribe(channelID,1,readAPIKey)==1)
      {
        Serial.println("SUBSCRIBED2");
      }
      else 
     {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      }
      if(mqttsubscribe(channelID,2,readAPIKey)==1)
      {
        Serial.println("SUBSCRIBED3");
      }
      else 
     {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      }
      if(mqttsubscribe(channelID,4,readAPIKey)==1)
      {
        Serial.println("SUBSCRIBED4");
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
}

int mqttsubscribe(long channelID, int field, char* readAPIKey) 
{
  String topic = "channels/"+String(channelID)+"/subscribe/fields/field"+String(field)+"/"+String(readAPIKey);
  Serial.println("Subscribed to "+topic);
  Serial.println("State="+String(mqttClient.state()));
  char charBuf[topic.length()+1];
  topic.toCharArray(charBuf,topic.length()+1);
  return mqttClient.subscribe(charBuf);
}
void callback(char* topic, byte* payload, unsigned int length)
{
  if(strstr(topic,f1))
  {
  Serial.print("The temperature is : ");
  strfun(payload,length);  
  }
  else if(strstr(topic,f2))
  {
  Serial.print("The humidity is : ");
  strfun(payload,length);  
  }
  else if(strstr(topic,f3))
  {
  Serial.print("The moisture percentage is : ");
  strfun(payload,length);  
  }
  else 
  {
  Serial.print("The light presence is : ");
  strfun(payload,length);  
  }
}


void strfun(byte* payload,unsigned int length)
{
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  return;
}
