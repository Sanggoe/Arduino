#include <DHT.h>
#define DHTPIN 3  // 온·습도 데이터 핀 설정
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal.h>

#include <Stepper.h>
#define motor1EnablePin 7
#define motor1_1        2
#define motor1_2        4
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

double temp;
bool whichSide = true;

int sensorPin = A1;
int lightPin = A0; // define a pin for Photo resistor
int ledPin = 6; // define a pin for LED

void setup()
{
  Serial.begin(9600);
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  analogWrite(motor1EnablePin, 0);
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  myStepper.setSpeed(100);
}

void loop()
{
  delay(2000);
  temp = dht.readTemperature();
  Serial.print("Temperature (C): ");
  Serial.println(temp);
  int i;

  if (temp > 23.0) {
    analogWrite(motor1EnablePin, 1023);

    if (whichSide) {
      whichSide = false;
      for (i = 0; i < 30; i++) {
        myStepper.step(1);
        delay(60);
      }
    } else {
      whichSide = true;
      for (i = 0; i < 30; i++) {
        myStepper.step(-1);
        delay(60);
      }
    }
    delay(1000);
  }

  else {
    analogWrite(motor1EnablePin, 0);
  }
}
