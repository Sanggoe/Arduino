#define motor1EnablePin 9
#define motor1_1        2
#define motor1_2        4

void setup()
{
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  analogWrite(motor1EnablePin, 0);
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);  
}

void loop()
{
  analogWrite(motor1EnablePin, 1023);
  delay(3000);
  analogWrite(motor1EnablePin, 0);
  delay(1000);
}
