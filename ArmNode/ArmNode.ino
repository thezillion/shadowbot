/*
 * Author:Jacob
 * Topic:Serial Communicatin Node MCU
 * 
 */
#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(D7,D8);

void setup(){

    Serial.begin(9600);
    NodeMCU.begin(115200);
    pinMode(D7,INPUT);
    pinMode(D8,OUTPUT);
}

void loop(){

    NodeMCU.print("hai");

}


