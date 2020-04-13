const int ledPin = 8;
const int interruptPin = 2;
volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(state);
  if (state == HIGH) {
    Serial.println("state = HIGH 입니다. 0.1초");
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  } else {
    Serial.println("state = LOW 입니다. 1초");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}

void blink() {
 state = !state;
}
