Servo penServo;
#define penServoPin 12
#define penUpPos 45
#define penDownPos 94

void penDown() 
{
    penServo.write(penDownPos);
    delay(300);
}

void penUp() 
{
    penServo.write(penUpPos);
    delay(300);
}