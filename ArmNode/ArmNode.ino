/*
 * Author:Jacob
 * Topic:Serial Communicatin Node MCU
 * Date:07/07/2018
 */
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "Lenovo Z2 Plus";
const char* password = "blastoise";

char path[] = "/";
char host[] = "192.168.43.22";


WebSocketClient webSocketClient;
WiFiClient client;

SoftwareSerial NodeMCU(D7,D8);

void setup(){

    Serial.begin(9600);
    NodeMCU.begin(115200);
    pinMode(D7,INPUT);
    pinMode(D8,OUTPUT);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);

  if (client.connect(host, 5000)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
    digitalWrite(13,HIGH);
    delay(1000);
  } else {
    Serial.println("Handshake failed.");
  }
  delay(1000);
}

void loop(){
    String data="";

    if (client.connected()) {

      //webSocketClient.sendData("it works ");

      webSocketClient.getData(data);
      if (data.length() > 0) {
        Serial.print("Received data: ");
        Serial.println(data);
        NodeMCU.print(data);
        delay(50);
      }

    } else {
          Serial.println("Client disconnected.");
      }
  //delay(100);
}


