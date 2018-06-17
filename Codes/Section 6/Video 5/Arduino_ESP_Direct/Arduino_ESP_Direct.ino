
#include <SoftwareSerial.h>// Header that gives us the ability to enable other digital pins (other than 0 and 1) for serial communication

SoftwareSerial mySerial(10,11);// This line creates an instance of software serial header with pins 10 and 11 as receiver and transmitter pins respectively
 
 
void setup() 
{ 
    Serial.begin(9600);//sets the data rate of the default serial communication with computer to 9600     
  mySerial.begin(9600);//sets the data rate of the serial communication between arduino and ESP8266 to 9600  
}
 
void loop() 
{
 // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   
  {  
    Serial.write( mySerial.read() );  
  }

    // listen for user input and send it to the ESP8266

    if ( Serial.available() )       
  {  
    mySerial.write( Serial.read() );  
  }
}

/*

AT commands

AT - This will check if the module is connected properly and its functioning, the module will reply with an acknowledgment(OK)

AT+GMR - This will mention the firmware version installed on the ESP8266

AT+CWLAP - This will detect the Access points and their signal strengths available in the area

AT+CWJAP=”SSID”,”PASSWORD” This connects the ESP8266 to the specified SSID

If you face error in the above step then use 

AT+CWMODE=1 This sets the Wifi mode. It should be always set to Mode 1 if the module is going to be used as a node

*/


