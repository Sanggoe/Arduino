#include <Servo.h>
int motor_control = 4;
Servo servo; 

#define trigPin 5 
#define echoPin 6
int num = 0;

void setup() {
  Serial.begin (9600);
  servo.attach(motor_control);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}


void loop() {
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration / 29.0 / 2.0;

  Serial.print(distance);
  Serial.println("cm");
  delay(200);

  if (distance < 3) {
    servo.write(180); // LOCK
    delay(1000);
  } else {
    servo.write(90); // UNlOCK
    delay(1000);
  }
}
