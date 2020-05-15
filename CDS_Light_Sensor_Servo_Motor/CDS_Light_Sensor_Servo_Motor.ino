int mood_led = A3;
int brightness = 0;
int fadeAmount = 5;

#include <Servo.h>
int motor_control = A2;
Servo servo;

int sensorPin = A1;
int lightPin = A0; // define a pin for Photo resistor
int ledPin = 6; // define a pin for LED

void setup()
{
  Serial.begin(9600); //Begin serial communcation
  pinMode( ledPin, OUTPUT );
  pinMode( mood_led, OUTPUT );
  servo.attach(motor_control);
}
int i;
int sensorValue;
int bright;
void loop()
{
  sensorValue = analogRead(sensorPin);
  bright = analogRead(lightPin);
  Serial.print(bright);
  Serial.print("  ");
  Serial.println(sensorValue);
  analogWrite(ledPin, sensorValue / 4);

  if (bright <= 200) {
    servo.write(180);
    analogWrite(mood_led, 255);
  } else if (bright <= 400) {
    servo.write(135);
    analogWrite(mood_led, 255);
  } else if (bright <= 600) {
    servo.write(90);
    analogWrite(mood_led, 255);
  } else if (bright <= 800) {
    servo.write(45);
    analogWrite(mood_led, 0);
  } else {
    servo.write(0);
    analogWrite(mood_led, 0);
  }
  delay(500);


}
