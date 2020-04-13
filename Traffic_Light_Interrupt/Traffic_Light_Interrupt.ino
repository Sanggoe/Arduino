int led1 = 8; // Red
int led2 = 9; // Yellow
int led3 = 10; // Green
int buzzer = 11;
const int interruptPin = 2;
volatile int state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
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
     
    Serial.println("--- Yello On ---");
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    delay(1000);

    Serial.println("--- Red On ---");
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(3000);
  }
}
 
void blink() {
  state = !state;
  Serial.println("+++ 인터럽트 발생! ISR blink()실행 +++");
    digitalWrite(buzzer, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
}
