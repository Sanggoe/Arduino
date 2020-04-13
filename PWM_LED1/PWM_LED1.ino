int led = 9; // the pin that the LED is attached to
int led2 = 10;
int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by

void setup() {
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  analogWrite(led, brightness);
  analogWrite(led2, brightness);
  brightness = brightness + fadeAmount;
  if(brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }

  delay(30);
}
