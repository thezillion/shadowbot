/*
 * Author:Jacob 
 * 
 * 
*/

#include <Wire.h>
#include <L3G4200D.h>




L3G4200D gyroscope;

// Timers
unsigned long timer = 0;
float timeStep = 0.1;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

const int FluxPin1=A0;
const int FluxPin2=A1;
const int FluxPin3=A2;

int FluxVal1,FluxVal2,FluxVal3;


int LED = 13;
boolean Blink = false;

void setup() 
{
  Serial.begin(115200);
  pinMode(FluxPin1,INPUT);
  pinMode(FluxPin2,INPUT);
  pinMode(FluxPin3,INPUT);

  // Initialize L3G4200D
  // Set scale 2000 dps and 400HZ Output data rate (cut-off 50)
  while (!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50))
  {
    // Waiting for initialization

    if (Blink)
    {
      digitalWrite(LED, HIGH);
    } else
    {
      digitalWrite(LED, LOW);
    }

    Blink = !Blink;

    delay(500);
  }

  digitalWrite(LED, HIGH);

  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  gyroscope.calibrate(100);

  digitalWrite(LED, LOW);
}

void loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = gyroscope.readNormalize();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  FluxVal1=analogRead(FluxPin1);
  FluxVal2=analogRead(FluxPin2);
  FluxVal3=analogRead(FluxPin3);

 /* // Output raw
  Serial.print(norm.XAxis);
  Serial.print(":");
  Serial.print(norm.YAxis);
  Serial.print(":");
  Serial.print(norm.ZAxis);
  Serial.print(":");
  Serial.print(pitch);
  Serial.print(":");
  Serial.print(roll);
  Serial.print(":");
  Serial.println(yaw);
*/

 // Serial.println(millis());
  String DataComma ="" ;
 // DataComma.concat(",");
  DataComma.concat(pitch);
  DataComma.concat(",");
  DataComma.concat(yaw);
  DataComma.concat(",");
  DataComma.concat(FluxVal1);
  DataComma.concat(",");
  DataComma.concat(FluxVal2-30);
  DataComma.concat(",");
  DataComma.concat(FluxVal3-85);
 // DataComma.concat(",");

  Serial.println(DataComma);

  if((millis()%33)==0)
  {
    float pitch = 0;
    float roll = 0;
    float yaw = 0;
    
  }

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}
