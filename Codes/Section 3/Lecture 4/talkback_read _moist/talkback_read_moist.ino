#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>

#define RBUFFSIZE 200

const size_t bufferSize = JSON_OBJECT_SIZE(5);

long id=0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const char server[] = "api.thingspeak.com"; 
EthernetClient client;

char responseBuffer[RBUFFSIZE];
int  rbindex = 0;  

boolean startCapture;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println(F("Unable to configure Ethernet using DHCP"));
    while(true);
  }
  delay(500);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop()
{
  if (client.connect(server, 80))
  {
    Serial.println(F("Connected!"));
  } 
  else
  {
    Serial.println(F("Connection failed!"));
  }
  
  apiExecute();
  
  while(true)
  {
  if (client.available())
  {
    char c = client.read();
    if(c == '{') {
      startCapture=true;
    }
    
    if(startCapture && rbindex < RBUFFSIZE) {
      responseBuffer[rbindex] = c;
      rbindex++;
    }
  }
  
  if (!client.connected()) {   
    Serial.print(F("Received bytes "));
    Serial.print(strlen(responseBuffer));
    Serial.println(F(" Disconnecting."));
    client.flush();
    client.stop();
    Serial.println(responseBuffer);
  
    StaticJsonBuffer<bufferSize> jsonBuffer;
    
    JsonObject& root = jsonBuffer.parseObject(responseBuffer);

    String command = root["command_string"];
     id = root["id"];
    Serial.println(command);
    Serial.println(id);
    if(command == "LIGHT_ON")
    {
      Serial.println(F("Command received"));
      digitalWrite(7,HIGH);
      delay(4000);
      digitalWrite(7,LOW);
    }
    else if(command == "Moist")
    {
      Serial.println(F("Command received"));
      digitalWrite(6,HIGH);
      delay(4000);
      digitalWrite(6,LOW);
    }
    else
    {
      Serial.println(F("no valid option recieved"));
    }
    delay(10000);
    return;
  }
  }
}

void apiExecute()
{
    Serial.println("inside api get");
    const String html_cmd1 = "GET https://api.thingspeak.com/talkbacks/24667/commands/execute.json?api_key=6XH5H6QK26ZVU3BM";
    const String html_cmd2 = "Host: api.thingspeak.com";
    const String html_cmd3 = "Connection: close";

    client.println(html_cmd1);
    client.println(html_cmd2);
    client.println(html_cmd3);
    client.println();
    
    responseBuffer[0] = '\0';
    rbindex = 0;
    startCapture = false;     
}

