//declare led connected pins
uint8_t LED[] = {5,6,9,10,11};
uint8_t i_led = 0;

//mapping values of brightness
uint8_t brightness[] = {0, 5, 20, 35, 50, 65, 80, 95, 110, 125,
                       140, 155, 170, 185 ,200, 215, 230, 255}; // 17
uint8_t i_brt = 0;

//declare button (16 = A2)
const int button = A2;

//stores if the switch was high before at all
volatile int state = LOW;

//storing the button state for short press mode
volatile int state_short = LOW;

//storing the button state for long press mode
volatile int state_long = LOW;

//storing the button state for so long press mode
volatile int state_so_long = LOW;

//stores the time each button went high or low
volatile unsigned long current_high;
volatile unsigned long current_low;


void setup()
{
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);
//  pinMode(13, OUTPUT);

  pinMode(button, INPUT);
  attachInterrupt(0, read_button, CHANGE);
  Serial.begin(9600);

  //digitalWrite(13,HIGH);
  Serial.begin(9600);
}

void loop()
{
//  Serial.println();
//  Serial.println(state);
//  Serial.println(state_short);
//  Serial.println(state_long);
  if(state_short == HIGH)
  {
    //do something when button 0 was pressed short ...
    Serial.println("짧게 눌러 밝기 조절");
    Serial.println(state_short);
    i_brt = (i_brt+1) % 18;
    state_short = LOW;
    
    //end
  }    
  if(state_long == HIGH)
  {
    //do something when button 3 was pressed long ...
    Serial.println("길게 눌러 LED 변경");
    Serial.println(state_long);
    digitalWrite(LED[i_led],LOW);
    i_led = (i_led+1) % 5;    
    i_brt = 0;
    state_long = LOW;
    
    //end
  }
  if(state_so_long == HIGH)
  {
    //do something when button 3 was pressed so long ...
    Serial.println("매우 길게 눌러 전원 On off");
    Serial.println(state_long);
    for(int i=0; i<5; i++) {
      digitalWrite(LED[i], HIGH);
      delay(500);
    }
    
    for(int i=0; i<5; i++) {
      digitalWrite(LED[i], LOW);
      delay(500);
    }
    state_so_long = LOW;

    //end
  }
  analogWrite(LED[i_led],brightness[i_brt]);
}


//is called when the Interrupt Pin is pressed or released (CHANGE Mode)
void read_button()
{
  //cycles through the buttons to find out which one was pressed or released
  //if this is true the button was just pressed down
  if(digitalRead(button) == HIGH)
  {
    //note the time the button was pressed
    current_high = millis();
    state = HIGH;
    Serial.println("button이 input으로 눌림, state도 바뀜");
    Serial.println(button);
    Serial.println(state);
  }

  //if no button is high one had to be released. The millis function will increase while a button is hold down the loop function will be cycled (no change, so no interrupt is active) 
   if(digitalRead(button) == LOW && state == HIGH)
  {
    Serial.println("button이 input으로 눌림, state도 동작중");
    Serial.println(button);
    Serial.println(state);
    current_low = millis();
    Serial.println(current_high);
    Serial.println(current_low);
    if((current_low - current_high) > 0 && (current_low - current_high) < 1000)
    {
      state_short = HIGH;
      state = LOW;
      
    }
    else if((current_low - current_high) >= 1000 && (current_low - current_high) < 5000)
    {
      state_long = HIGH;
      state = LOW;
    }
    else if((current_low - current_high) >= 5000 && (current_low - current_high) < 15000)
    {
      state_so_long = HIGH;
      state = LOW;
    }
    
  }
  
}
