#include <SoftwareSerial.h> 
SoftwareSerial mySerial(10, 11);
#include <DHT.h> 

DHT dht;
const int moisture_pin = A1;
const int ldr_pin = 8; 
int soil_moisture;
float soil_moisture_percentage;
int ldr_value;

String WriteApiKey = "72HHKGV77BFSIOD3";
void setup() 
{                 
  
  Serial.begin(9600);
  Serial.println("Serial connection has started...");
  mySerial.begin(9600);
  mySerial.println("AT+RST");
  
  dht.setup(2);
  pinMode(moisture_pin,INPUT);
  pinMode(ldr_pin,INPUT);
}

void loop() 
{
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  soil_moisture = analogRead(moisture_pin);
  soil_moisture_percentage = map(soil_moisture,1023,350,0,100);
  ldr_value = digitalRead(ldr_pin);


  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";
  mySerial.println(cmd);

  if(mySerial.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }

  String getStr = "GET /update?api_key=";
  getStr += WriteApiKey;
  getStr +="&field1=";
  getStr += String(temperature);
  getStr +="&field2=";
  getStr += String(humidity);
  getStr +="&field3=";
  getStr += String(soil_moisture_percentage);
  getStr +="&field4=";
  getStr += String(ldr_value);
  getStr += "\r\n\r\n";
  
  Serial.println(getStr);

  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  mySerial.println(cmd);
  Serial.println(cmd);
  if(mySerial.find(">"))
  {
    mySerial.print(getStr);
  }
  else
  {
    mySerial.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
  delay(16000);  
}
