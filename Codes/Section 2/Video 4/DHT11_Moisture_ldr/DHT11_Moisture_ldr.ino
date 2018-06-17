#include <DHT.h>
DHT dht;
const int moisture_pin = A1;
const int ldr_pin = 8;
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;
void setup()
{
  Serial.begin(9600);
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
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
  
  ldr_value = digitalRead(ldr_pin);
  if(ldr_value)
  {
    Serial.println("It's dark");
    }
   else
   {
    Serial.println("There is enough light");
    }
  delay(1000);
}


