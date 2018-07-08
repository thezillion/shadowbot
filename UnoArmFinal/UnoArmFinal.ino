/*
 * Author:Jacob
 * Topic:Serial Communicatin Uno
 * Date:07/07/2018
 */

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Servo.h>
#include <stdlib.h>
#include <string.h>

String DataString;
DynamicJsonBuffer jBuffer;

Servo myservo,servo2;
Servo myservof1; 
Servo myservof2;// create servo object to control a servo
Servo myservof3;

SoftwareSerial Uno(2,3);
String Data ="";
String Sdata;

void setup() {
    Serial.begin(9600);
    Uno.begin(115200);
    pinMode(2,INPUT);
    pinMode(3,OUTPUT);
    myservo.attach(9);
    servo2.attach(10);
    myservof1.attach(5);  // attaches the servo on pin 9 to the servo object
    myservof2.attach(6);
    myservof3.attach(11);
    

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
    //Sdata.replace("\"",'"');
    //StaticJsonBuffer<300> JSONBuffer; //Memory pool
    //JsonObject& parsed = JSONBuffer.parseObject(Sdata);
    //Serial.println(Sdata);
    //float pitch=parsed["pitch"];
    //float yaw=parsed["yaw"];
    //int flux1=parsed["flux1"];
    //int flux2=parsed["flux2"];
    //int flux3=parsed["flux3"];

    float pitch;
    float yaw;
    int flux1;
    int flux2;
    int flux3;

    char *bubble = Sdata.c_str();

    char* pt;
    pt = strtok(bubble, ",");
    int i = 0;
    while (pt != NULL) {
      if (i == 0) pitch = atof(pt);
      if (i == 1) yaw = atof(pt);
      if (i == 2) flux1 = atoi(pt);
      if (i == 3) flux2 = atoi(pt);
      if (i == 4) flux3 = atoi(pt);
      pt = strtok(NULL, ",");
      i++;
    }

    if((pitch!=0) && (flux1!=0) && (flux2!=0) && (flux3!=0))
    {
    pitch=constrain(pitch,10,95);
    pitch=map(pitch,10,95,30,115);
    yaw=constrain(yaw,-100,100);
    yaw=map(yaw,-100,100,0,180);
    flux1=constrain(flux1,100,200);
    flux1=map(flux1,100,200,90,180);
    flux2=constrain(flux2,100,200);
    flux2=map(flux2,100,200,90,180);
    flux3=constrain(flux3,100,200);
    flux3=map(flux3,100,200,90,180);
    Serial.print(pitch);
    Serial.print(":");
    Serial.print(yaw);
    Serial.print(":");
    Serial.print(flux1);
    Serial.print(":");
    Serial.print(flux2);
    Serial.print(":");
    Serial.println(flux3);
    servo2.write(yaw);
    myservo.write(pitch);
    myservof1.write(flux1);  // attaches the servo on pin 9 to the servo object
    myservof2.write(flux2);
    myservof3.write(flux3);
    }
    

}
