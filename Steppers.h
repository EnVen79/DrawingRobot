#define xEndPin 9
#define yEndPin 10

#define stepPinX 2
#define dirPinX 5
#define stepPinY 3
#define dirPinY 6
#define ENABLE_PIN 8

AccelStepper stepperX(1, stepPinX, dirPinX);
AccelStepper stepperY(1, stepPinY, dirPinY);

const float xMin = 0;
const float xMax = 7000;
const float yMin = 0;
const float yMax = -7000;

void moveToHome() 
{
  while (true) 
  {
    if (digitalRead(xEndPin) == LOW) 
     {
       stepperX.stop();
       stepperX.setCurrentPosition(0);
     } 
    else 
     {
       stepperX.runSpeed();
     }

    if (digitalRead(yEndPin) == LOW) 
     {
       stepperY.stop();
       stepperY.setCurrentPosition(0);
     } 
    else 
     {
       stepperY.runSpeed();
     }

    if (digitalRead(yEndPin) == LOW && digitalRead(xEndPin) == LOW) 
     {
       Serial.println("Начальная позиция установлена: X=0, Y=0");
       break;
     }
  }
}

void moveToPosition(float x, float y) 
{
    if (y > 0) 
    {
     y = -y;
    }

    x = constrain(x, xMin, xMax);
    y = constrain(y, yMin, yMax);

    float dx = abs(x - stepperX.currentPosition());
    float dy = abs(y - stepperY.currentPosition());
    float maxDistance = max(dx, dy);

    stepperX.setMaxSpeed(1000 * (dx / maxDistance));
    stepperY.setMaxSpeed(1000 * (dy / maxDistance));

    stepperX.moveTo(x);
    stepperY.moveTo(y);

    if (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) 
    {
        stepperX.run();
        stepperY.run();
    }
    else 
    {
      stepperX.stop();
      stepperY.stop();
    }
}