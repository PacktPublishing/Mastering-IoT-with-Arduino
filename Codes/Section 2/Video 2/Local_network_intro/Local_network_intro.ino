#include <SPI.h> 
#include <Ethernet.h>



byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 107); 
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  } 
  Ethernet.begin(mac, ip); 
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available(); value from "server.available()"
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
          client.print("Hello World!");
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

