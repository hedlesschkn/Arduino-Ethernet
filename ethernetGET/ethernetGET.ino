/*
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * RGB pins 3,5,6
 Underlying Ethernet Code:
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <WString.h>


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x5F, 0xC4 };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(213,186,33,19);  // numeric IP for pushingbox (no DNS)
char server[] = "api.pushingbox.com";    // name address for pushingBox (using DNS)
String devid = "v9A1CFE5F18FECCE";

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(129,64,18,246);
//129.64.5.11

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;



void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("EthernetGET");

  float humidityData = 99.9;
  float celData = 99.9;
  float fehrData = 99.9;
  float hicData = 999.9;
  float hifData = 999.9;

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    //http://api.pushingbox.com/pushingbox?devid=v9A1CFE5F18FECCE&humidityData=33&celData=44&fehrData=111&hicData=22&hifData=77
    //client.print("GET /pushingbox?devid=v9A1CFE5F18FECCE&humidityData=99&celData=99&fehrData=99&hicData=999&hifData=999");
//    client.print("GET /pushingbox?devid=" + devid
//       + "&humidityData=" + (String) humidityData
//       + "&celData="      + (String) celData
//       + "&fehrData="     + (String) fehrData
//       + "&hicData="      + (String) hicData
//       + "&hifData="      + (String) hifData
//         );
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{


String readString = String(1200);
readString = "";

  char tBuffer[1200];
  int tCount = 0;
  
  
  if (client.available()) {
 
    char c = client.read();
   Serial.print(c);
   
  /*if (tCount < 1199){        //    First attempt to create char array to store incoming client data unsuccessful
    tBuffer[tCount] = c;
    tCount++;
    tBuffer[tCount] = 0;
  }
  */
  //Client.read data appended to readString to create string that can be used for strcmp
 readString += c;
 Serial.println(readString);
 //readString displays same thing as c 
  }
  

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
Serial.print(readString);
 
    // do nothing forevermore:
    while(true);
  }
 
}
