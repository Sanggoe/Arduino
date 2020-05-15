// 온습도 센서
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal.h>
double temp;

// CDS 조도센서
int lightPin = A0;
int bright;
int brightLayter;

// 가변 저항 및 LED
int registerPin = A1;
int ledPin = 3;
int regitValue;

// 무드등 LED
int ledMoodPin = A2;

// 서보 모터
#include <Servo.h>
int motor_control = A3;
Servo servo;

// DC 모터
#define motor1EnablePin 5
#define motor1_1        4
#define motor1_2        7

// Step 모터
#include <Stepper.h>
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
bool whichSide = true;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledMoodPin, OUTPUT);
  servo.attach(motor_control);

  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  analogWrite(motor1EnablePin, 0);
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  myStepper.setSpeed(100);
}

void loop() {
  temp = dht.readTemperature();
  bright = analogRead(lightPin);
  brightLayter = bright/100;
  regitValue = analogRead(registerPin);

  switch(brightLayter) {
    case 0:
      digitalWrite(ledMoodPin, HIGH);
      servo.write(160);
      break;
    case 1:
      digitalWrite(ledMoodPin, HIGH);
      servo.write(160);
      break;
    case 2:
      digitalWrite(ledMoodPin, HIGH);
      servo.write(120);
      break;
    case 3:
      digitalWrite(ledMoodPin, LOW);
      servo.write(80);
      break;
    case 4:
      digitalWrite(ledMoodPin, LOW);
      servo.write(40);
      break;
    default:
      digitalWrite(ledMoodPin, LOW);
      servo.write(0);
      break;
  }
  
  Serial.print("Temp(C): ");
  Serial.print(temp);
  Serial.print("\t\tCDS(bright): ");
  Serial.print(brightLayter);
  Serial.print("\t\tRegister: ");
  Serial.println(regitValue);
  analogWrite(ledPin, regitValue/4);

  if (temp >= 27) {
    analogWrite(motor1EnablePin, 1023);
    if (whichSide) {
      whichSide = false;
      for (int i = 0; i < 30; i++) {
        myStepper.step(1);
        delay(60);
      }
    } else {
      whichSide = true;
      for (int i = 0; i < 30; i++) {
        myStepper.step(-1);
        delay(60);
      }
    }
  } else {
    analogWrite(motor1EnablePin, 0);
    delay(1800);
  }
}
