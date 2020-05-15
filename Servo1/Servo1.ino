#include <Servo.h>

int motor_control = A3;
Servo servo;

void setup()
{
  servo.attach(motor_control);
}


void loop()
{
  servo.write(0);

  delay(3000);

  //servo.write(160);

  delay(3000);
  /*  int i;

  for (i = 0; i <= 180; i += 1)
  {
    servo.write(i);
    delay(10);
  }

  for (i = 180; i >= 0; i -= 1)
  {
    servo.write(i);
    delay(10);
  }
  */
}
