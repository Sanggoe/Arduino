int led1 = 8; // Red
int led2 = 9; // Yellow
int led3 = 10; // Green
int buzzer = 11;
const int interruptPin = 2;
const int interruptPin2 = 3;
volatile int state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), blink2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(state == LOW) {
    Serial.println("--- 정상 수행 ---");
    Serial.println("--- Green On ---");
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(3000);
  }

  if(state == LOW) {
    Serial.println("--- Yello On ---");
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    delay(1000);
  }
  
  if(state == LOW) {
    Serial.println("--- Red On ---");
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(3000);
  }
}
 
void blink1() {
  state = HIGH;
  Serial.println("+++ 인터럽트 발생! ISR blink1()실행 +++");
  digitalWrite(buzzer, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
}

void blink2() {
  state = LOW;
  Serial.println("--- 해제 인터럽트 발생! ISR blink2()실행 ---");
}
