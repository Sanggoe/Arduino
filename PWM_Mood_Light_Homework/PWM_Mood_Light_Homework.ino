// declare led pin numbers
int LED[] = {5,6,9,10,11};
int led_index = 0;

// mapping values of brightness
int brightness = 0;
int fadeAmount = 5;

//declare button (16 = A2)
const int button = A2;

// stores if the switch was high before at all
volatile int state = LOW;
volatile int basic = LOW;

//storing the button state for short press mode
volatile int state_short = LOW;

//storing the button state for long press mode
volatile int state_long = LOW;

//storing the button state for so long press mode
volatile int state_so_long = LOW;

//stores the time each button went high or low
volatile unsigned long current_high;
volatile unsigned long current_low;

// control potentiometer pin
int sensorPin = A0;
int sensorValue = 0;

void setup() {
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);

  pinMode(button, INPUT);
  attachInterrupt(0, read_button, CHANGE);
  Serial.begin(9600);
}

void loop() {
  Serial.println(state_so_long);
  if(state_so_long == HIGH) {
    if (basic == 0) {
      Serial.println("기본 기능, 자동 밝기 변경");

      analogWrite(LED[led_index], brightness);
      brightness = brightness + fadeAmount;
      if(brightness == 255) {
        fadeAmount = -fadeAmount;
      } else if (brightness == 0) {
        fadeAmount = -fadeAmount;
        digitalWrite(LED[led_index], LOW);
        led_index = (led_index+1)%5;
        Serial.println("기본 기능, LED 색 순차변경");
      }
      Serial.println(brightness);
      delay(30);
    }

    if (basic == 1) {
      Serial.println("선택 기능, 단일 색 자동 밝기 변경");

      analogWrite(LED[led_index], brightness);
      brightness = brightness + fadeAmount;
      
      if(brightness == 255) {
        fadeAmount = -fadeAmount;
      } else if (brightness == 0) {
        fadeAmount = -fadeAmount;
        digitalWrite(LED[led_index], LOW);
        Serial.println("선택 기능, LED 색 고정");
    }
      Serial.println(brightness);
      delay(30);
    }

    if (basic == 2) {
      Serial.println("선택 기능2, 밝기 수동 지정");
      sensorValue = analogRead(sensorPin);
      analogWrite(LED[led_index], sensorValue/4);
  
      delay(10);
    }

    if (state_long == HIGH) {
      Serial.println("길게 누름, 색 변경");
      digitalWrite(LED[led_index], LOW);
        led_index = (led_index+1)%5;

        state_long = LOW;
      }
   } else {
    Serial.println(state_so_long);
    Serial.println("전원 OFF 상태");

    for(int i=0; i<5; i++) {
      digitalWrite(LED[led_index], LOW);  
    }
   }
}

void read_button() {

  if (digitalRead(button) == HIGH) {
    current_high = millis();
    state = HIGH;
  }

  if (digitalRead(button) == LOW && state == HIGH) {
    current_low = millis();

    if ((current_low - current_high) > 0 && (current_low - current_high) < 1000) {
      state = LOW;
      basic = (basic+1)%3;
    }
    else if ((current_low - current_high) >= 1000 && (current_low - current_high) < 4000) {
      state = LOW;
      state_long = HIGH;
    }
    else if ((current_low - current_high) >= 4000 && (current_low - current_high) < 10000) {
      state = LOW;
      state_so_long = !state_so_long;
    }
    
  }
}
