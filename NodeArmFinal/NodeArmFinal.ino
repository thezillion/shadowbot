/*
*Author : Jacob Sabu
*Topic : Node Arm Final Code
*Date:07/07/2018
*/


#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h>

#define USE_SERIAL Serial

SoftwareSerial NodeMCU(D7,D8);

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
  webSocket.emit("client-nodeMCU-event");
  webSocket.on("data-from-server",event2);
}
void event2(const char * payload, size_t length){
  USE_SERIAL.println(payload);
  NodeMCU.print(payload);
  delay(50);
  
}

void setup() {
    USE_SERIAL.begin(9600);
    NodeMCU.begin(115200);

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("Lenovo Z2 Plus", "blastoise");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.on("init", event);
    webSocket.begin("192.168.43.22",5000);
}

void loop() {
    webSocket.loop();
}
