#include <AccelStepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "Steppers.h"
#include "Servo.h"
#include "Bluetooth.h"

float coords[maxLines][maxPoints][2];

void setup() 
{
  pinMode(xEndPin, INPUT_PULLUP);
  pinMode(yEndPin, INPUT_PULLUP);
  pinMode(ENABLE_PIN, OUTPUT);

  Bluetooth.begin(9600);

  Serial.begin(9600);

  stepperX.setMaxSpeed(12800);
  stepperX.setAcceleration(-2000);
  stepperX.setSpeed(-1000);

  stepperY.setMaxSpeed(12800);
  stepperY.setAcceleration(2000);
  stepperY.setSpeed(1000);

  penServo.attach(penServoPin);
  penServo.write(penUpPos);

  digitalWrite(ENABLE_PIN, LOW);

  penUp();
  moveToHome(); 
  penDown();

}

void drawLines(float coords[][maxPoints][2], int numLines, int numPoints) 
{
    for (int line = 0; line < numLines; line++) 
    {
        float startX = coords[line][0][0];
        float startY = coords[line][0][1];
        
        penUp();
        moveToPosition(startX, startY);
        penDown();
        
        for (int point = 1; point < numPoints; point++) 
        {
            float x = coords[line][point][0];
            float y = coords[line][point][1];
            if (x == 0 && y == 0) break;
            moveToPosition(x, y);
        }
        penUp();
    }
}

void loop() 
{
  if (Bluetooth.available()) 
  {
    String data = Bluetooth.readStringUntil('\n');
    GetCoord(data);
  }
  delay(10);
}