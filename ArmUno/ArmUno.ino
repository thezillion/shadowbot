/*
 * Author:Jacob
 * Topic:Serial Communicatin Uno
 * Date:07/07/2018
 */

#include <SoftwareSerial.h>

SoftwareSerial Uno(2,3);
String Data ="";
String Sdata;

void setup() {
    Serial.begin(9600);
    Uno.begin(115200);
    pinMode(2,INPUT);
    pinMode(3,OUTPUT);
    

}

void loop() {
  
    while(Uno.available())
    {
      char DataC = Uno.read();
      Data.concat(DataC);
      
    }
    if(Data !="")
      Sdata=Data;
    Data="";
    Serial.println(Sdata);

}
