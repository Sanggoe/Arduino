int button = A0;
// stores if the switch was high before at all
volatile int state = LOW;
volatile int basic = LOW;

//stores the time each button went high or low
volatile unsigned long current_high;
volatile unsigned long current_low;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  attachInterrupt(0, read_button, CHANGE);
}


void loop() {
  
}

void read_button() {

  if (digitalRead(button) == HIGH) {
    current_high = millis();
    state = HIGH;
  }

  if (digitalRead(button) == LOW && state == HIGH) {
    current_low = millis();

    if ((current_low - current_high) > 0 && (current_low - current_high) < 3000) {
      Serial.println("3초 이하!");
      state = LOW;
      basic = (basic + 1) % 2;
    }
  }
}
