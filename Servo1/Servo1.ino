#include <Servo.h>

int motor_control = 8;
Servo servo;

void setup()
{
  servo.attach(motor_control);
}


void loop()
{
  int i;
  
  for(i=0; i<=180; i+=1)
  {
    servo.write(i);
    delay(10);
  }
  
  for(i=180; i>=0; i-=1)
  {
    servo.write(i);
    delay(10);
  }
}
