/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>
#include <stdlib.h>


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xAE, 0xAE, 0xDE, 0xAF, 0xDE, 0xAD };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,1,1);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 0, 1);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
char temp[7];
int tempTemp;
int uid;
void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Ethernet.begin(mac, ip, myDns);
  uid = rand() % 20000;
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
  String test1 = "?param1=someDataToPost&hej=1";
  // if you get a connection, report back via serial:
  
}

void loop() {
  Serial.readBytes(temp,8);
  tempTemp = rand() % 30;
  // if there are incoming bytes available
  // from the server, read them and print them:
  String url;
  url += F("POST: /h5emb/index.php?temp=");
  url += String((char *)temp);
  url += F("&uid=");
  url += String(uid,6);
  url += F(" HTTP/1.1");
  
  
  Serial.print(url);
  if (client.connect(server, 80)) {
      Serial.print("connected to ");
      Serial.println(client.remoteIP());
      // Make a HTTP request:
      
      //if(){
        client.println(url);
        client.println("Host: 192.168.1.1");
        client.println("Connection: close");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println();
        delay(1000);
      //}
  } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
  }

  beginMicros = micros();
  
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
}