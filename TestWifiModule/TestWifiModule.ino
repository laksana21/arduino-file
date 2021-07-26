#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D0,D1); // RX, TX nodemcu
WiFiServer server(80); //Initialize the server on Port 80
String recSerial;

void setup()
{
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("GKM 16-S1IF", "kebogiro"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server

  //Looking under the hood
  mySerial.begin(115200);
  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);
}

void loop()
{
  WiFiClient client = server.available();
  if (!client) {
  return;
  }
  //Looking under the hood
  recSerial = Serial.read();
  //Serial.println("Somebody has connected :)");
  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readString();
  //Looking under the hood
  //Serial.println(request);
  //Serial.read();

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><br>";
  s += "Test Pesan";
  s += "<br><br>";
  s += recSerial;
  s += "</html>\n";
  
  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  delay(1);
  //Serial.println("Client disonnected"); //Looking under the hood
}
