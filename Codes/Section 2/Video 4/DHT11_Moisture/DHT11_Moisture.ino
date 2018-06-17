#include <DHT.h>
DHT dht;
const int moisture_pin = A1;
int soil_moisture;
float soil_moisture_percentage; 
void setup()
{
  Serial.begin(9600);
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();
  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.print("  Temperature:");
  Serial.println(temperature);

  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);
  Serial.print("Moisture Percentage = ");
  Serial.print(soil_moisture_percentage);
   Serial.println("%");
  delay(1000);

}

