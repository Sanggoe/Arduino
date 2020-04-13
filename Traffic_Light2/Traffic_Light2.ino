int led1 = 8; // Red
int led2 = 9; // Yellow
int led3 = 10; // Green
int led4 = 11; // Red2
int led5 = 12; // Green2

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT); // output from +5V
  pinMode(led2, OUTPUT); // output from +5V
  pinMode(led3, OUTPUT); // output from +5V
  pinMode(led4, OUTPUT); // output from +5V
  pinMode(led5, OUTPUT); // output from +5V
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, LOW);// power off
  digitalWrite(led2, LOW); // power off
  digitalWrite(led3, HIGH); // power on, Green
  digitalWrite(led4, HIGH); // power on, Red2
  digitalWrite(led5, LOW); // power off
  
  delay(3000);

  digitalWrite(led1, LOW);// power off
  digitalWrite(led2, HIGH); // power on, Yello
  digitalWrite(led3, LOW); // power off
  
  delay(1000);
  
  digitalWrite(led1, HIGH);// power on, Red
  digitalWrite(led2, LOW); // power off
  digitalWrite(led3, LOW); // power off
  digitalWrite(led4, LOW); // power off
  digitalWrite(led5, HIGH); // power on, Green2
  
  delay(1000);

  for(int i=0; i<5; i++){
    digitalWrite(led5, HIGH); // power on, Green2
    delay(200);
    digitalWrite(led5, LOW); // power on, Green2
    delay(200);
  }
    
}
