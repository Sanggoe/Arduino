int led1 = 8; // Red
int led2 = 9; // Yellow
int led3 = 10; // Green
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT); // output from +5V
  pinMode(led2, OUTPUT); // output from +5V
  pinMode(led3, OUTPUT); // output from +5V
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, LOW);// power off
  digitalWrite(led2, LOW); // power off
  digitalWrite(led3, HIGH); // power on, Green
  
  delay(3000);

  digitalWrite(led1, LOW);// power off
  digitalWrite(led2, HIGH); // power on, Yello
  digitalWrite(led3, LOW); // power off
  
  delay(1000);
  
  digitalWrite(led1, HIGH);// power on, Red
  digitalWrite(led2, LOW); // power off
  digitalWrite(led3, LOW); // power off
  
  delay(3000);}
  
