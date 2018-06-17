
#include <ThingSpeak.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

DHT dht;
const int moisture_pin = A1;
const int ldr_pin = 8;
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;

unsigned long myChannelNumber = 473770;
const char * myWriteAPIKey = "B7CWBGOCWES3KPMD";

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
  
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Unable to configure Ethernet using DHCP");
    while(true);
  }
  Serial.println("Ethernet configured via DHCP");
  ThingSpeak.begin(client);
  
}

void loop() {
  
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);
  ldr_value = digitalRead(ldr_pin);
  ThingSpeak.setField(1,temperature);
  ThingSpeak.setField(2,humidity);
  ThingSpeak.setField(3,soil_moisture_percentage);
  ThingSpeak.setField(4,ldr_value);

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  

  Serial.println("data sent");
  delay(16000); 
}  
