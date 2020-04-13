int led1 = 8;
int led2 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT); // output from +5V
  pinMode(led2, OUTPUT); // output from +5V
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW); // power on

  delay(100);

  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH); // power off

  delay(100);
}
