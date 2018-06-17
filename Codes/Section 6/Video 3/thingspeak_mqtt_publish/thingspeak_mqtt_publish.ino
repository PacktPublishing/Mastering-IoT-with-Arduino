#include <SPI.h>
#include <Ethernet.h> 
#include <PubSubClient.h>
#include <DHT.h>

DHT dht;
const int moisture_pin = A1;
const int ldr_pin = 8; 
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;

 
const char* server = "mqtt.thingspeak.com"; 
unsigned long lastConnectionTime = 0; 
const unsigned long postingInterval = 15L * 1000L;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

char mqttUserName[] = "Maker"; 
char mqttPass[] = "SBAFM465MGD2B78X";

EthernetClient client; 
PubSubClient mqttClient(client);           


void setup() { 
  Serial.begin(9600); 
  while(!Serial);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Unable to configure Ethernet using DHCP"));
    while(true);
  }
  
  Serial.println("Ethernet configured via DHCP");
  mqttClient.setServer(server, 1883); 
  dht.setup(2);
  
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
}

void loop() { 
  
  if (!mqttClient.connected()) 
  {
    reconnect();
  }
  mqttClient.loop(); 
  if (millis() - lastConnectionTime > postingInterval) 
  {
    mqttpublish();
  }
}

void reconnect() 
{
  while (!mqttClient.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    char clientID[]="maker123"; 
    if (mqttClient.connect(clientID,mqttUserName,mqttPass))
    {
      Serial.print("Connected...");
    } else 
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttpublish() {
  
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);
  ldr_value = digitalRead(ldr_pin);
  
  String data = String("field1=" + String(temperature, DEC) + "&field2=" + String(humidity,DEC) + "&field3=" + String(soil_moisture_percentage, DEC) + "&field4=" + String(ldr_value,DEC) );
  int length = data.length();
  char msgBuffer[length]; 
  
  data.toCharArray(msgBuffer,length+1); 
  Serial.println("field1=25&field2=32&field3=3.0000000000&field4=1");
  mqttClient.publish( "channels/490937/publish/ON3HANNUKPTYOP8R", msgBuffer ); 
  
  lastConnectionTime = millis();
}


