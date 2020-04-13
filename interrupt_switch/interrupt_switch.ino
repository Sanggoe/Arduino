// LED pin numbers
int LED[] = {5,6,9,10,11};
int i_led = 0;

// bright control values
int brightness[] = {0, 64, 128, 192, 255};
int i_brt = 0;

// declare button pin
const int button = 16; // = A2

// stores if the switch was high before at all
volatile int state = LOW;

// storing the button state for short press mode
volatile int state_short = LOW;

// storing the button state for long press mode
volatile int state_long = LOW;

// stores the time each button went high or low
volatile unsigned long current_high;
volatile unsigned long current_low;

void setup() {
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(button, INPUT);
  attachInterrupt(0, read_button, CHANGE);

  digitalWrite(13, HIGH);
  Serial.begin(9600);
}

void loop() {
  if (state_short == HIGH) {
    // do something when button 0 was pressed short
    Serial.println("짧게 눌러 밝기 조절");
    i_brt = (i_brt+1)%5;
    state_short = LOW;

    // end
  }
  if (state_long == HIGH) {
    // do something when button 3 was pressed long
    Serial.println("길게 눌러 LED 변경"); 
    digitalWrite(LED[i_led], LOW);
    i_led = (i_led+1) % 5;
    i_brt = 0;
    state_long = LOW;

    // end
  }

  analogWrite(LED[i_led], brightness[i_brt]);
}


// is called when the Interrupt Pin is pressed or released (CHANGE Mode)
void read_button() {
  //cycles through the buttons to find out which one was pressed or released

  // if this is true the button was just pressed down
  if (digitalRead(button) == HIGH) {
    //note the time the button was pressed
    current_high = millis();
    state = HIGH;
    Serial.println("button이 눌려서 state high로 변경");
    return 0;
  }

  /*
   if no button is high one had to be released. The millis function will
   increase while a button is hold down the loop function will be cycled
    (no change, so no interrupt is active)*/

   if (digitalRead(button) == HIGH && state == HIGH) {
    current_low = millis();
    Serial.println("button도 눌리고, state도 high 상태여서 ");
    if ((current_low - current_high) > 1 && (current_low - current_high) < 300) {
      state_short = HIGH;
      state = LOW;
      Serial.println("millis 계산 결과, 짧게 눌림에 high");
    }
    else if ((current_low - current_high) >= 300 && (current_low - current_high) < 4000) {
      state_long = HIGH;
      state = LOW;
      Serial.println("millis 계산 결과, 길게 눌림에 high");
    }
    
   }

}
