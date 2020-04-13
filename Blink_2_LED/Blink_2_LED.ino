int led1 = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT); // output from +5V
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);

  delay(100);

  digitalWrite(led1, LOW);

  delay(100);
}
