#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
DHT dht;

const int moisture_pin = A1;
const int ldr_pin = 8;
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;

byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.1.3"; 
EthernetClient client;

void setup() {
  Serial.begin(9600); 
   if (Ethernet.begin(mac) == 0) {
    Serial.println("Unable to configure Ethernet using DHCP");
    for (;;);
  }
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
}

void loop() 
{ 
  
  delay(dht.getMinimumSamplingPeriod());  

  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);

  ldr_value = digitalRead(ldr_pin);
  
  Serial.println("connecting...");
   
  if (client.connect(server, 80)) {
    Serial.println("--> Connected");
    client.print("GET /write_data.php?"); 
    client.print("temperature="); 
    client.print(temperature);
    client.print("&humidity="); 
    client.print(humidity);  
    client.print("&soilmoisture="); 
    client.print(soil_moisture_percentage);   
    client.print("&ldrvalue=");
    client.print(ldr_value);
    client.println(" HTTP/1.1"); 
    client.println("Host: 192.168.1.3"); 
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println("Connection: close"); 
    client.println(); 
    client.println(); 
  }
  else {
    
    Serial.println("--> connection failed\n");
  }
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
    client.flush();
    client.stop();
  
    delay(10000);
  
}
