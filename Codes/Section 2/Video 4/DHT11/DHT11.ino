#include <DHT.h>
DHT dht;

void setup()
{
  Serial.begin(9600);
  dht.setup(2);
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
}


