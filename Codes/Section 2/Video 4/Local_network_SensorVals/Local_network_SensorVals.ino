#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

DHT dht;
const int moisture_pin = A1;
const int ldr_pin = 8;
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;
String s;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168,137, 177); 
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
  while (!Serial) {
    ; 
  }

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  delay(dht.getMinimumSamplingPeriod());

  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();
  
  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);

  ldr_value = digitalRead(ldr_pin);
  if(ldr_value)
  {
     s = "Its dark";
   }
   else
   {
     s = "There is light";
    }
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println("Refresh: 5"); 
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("Soil moisture percentage is ");
          client.print(soil_moisture_percentage);
          client.print("%");
          client.println("<br />");
          client.print("Temperature is ");
          client.print(temperature);
          client.println("<br />");
          client.print("Humidity is ");
          client.print(humidity);
          client.print("%");
          client.println("<br />");
          client.print(s);
          client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}


