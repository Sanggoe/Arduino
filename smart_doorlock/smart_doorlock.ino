
// keypad 관련 선언
#include <Keypad.h>
const byte numRows = 4;
const byte numCols = 3;
char keymap[numRows][numCols] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[numRows] = {8, 7, 6, 5}; ////// PIN NUMBER //////
byte colPins[numCols] = {4, 3, 2}; ////// PIN NUMBER //////
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


// bluetooth 관련 선언
#include <SoftwareSerial.h>
int bluetooth_Tx = 9; ////// PIN NUMBER //////
int bluetooth_Rx = 10; ////// PIN NUMBER //////
SoftwareSerial bluetooth(bluetooth_Tx, bluetooth_Rx);


// Servo 모터 관련 선언
#include <Servo.h>
int motor_control = 11; ////// PIN NUMBER //////
Servo servo;


// led 관련 선언
int LED_red = A5;
int LED_green = A4;
int LED_white = A1;


// buzzer 음계 관련 선언
#define NOTE_C 2093
#define NOTE_D 2349
#define NOTE_E 2647
#define NOTE_F 2793
#define NOTE_G 3186
#define NOTE_A 3300
#define NOTE_B 3951
#define NOTE_C2 4186
#define NOTE_D2 4698
#define NOTE_E2 5274
#define NOTE_F2 5587
#define NOTE_G2 6271
#define NOTE_A2 7040
///////////////////
#define NOTE_B2 7902
#define NOTE_C3 8000
#define buzzerPin 12 ////// PIN NUMBER //////
int melody1[] = { // Door's Unlocked 도-미-솔
  NOTE_C, NOTE_E, NOTE_G
};
int melody2[] = { // Door's Locked 솔-솔-미
  NOTE_G, NOTE_G, NOTE_E
};
int tempo1[] = { // 세 박자 템포
  //5, 5, 5, 5, 5, 5, 5, 5
  6, 6, 7
};
int melody3[] = { // Door's Closed 미미-미미
  NOTE_E, NOTE_E, 0, NOTE_E, NOTE_E
};
int tempo2[] = { // 네 박자 쉼 템포
  12, 12, 5, 12, 12
};
int melody4[] = { // Password Wrong 솔미솔미솔미솔미
  NOTE_G, NOTE_E, NOTE_G, NOTE_E, NOTE_G, NOTE_E, NOTE_G, NOTE_E
};
int tempo3[] = { // 여덟 박자 템포
  15, 15, 15, 15, 15, 15, 15, 15
};
int melody5[] = { // Warning 경보
  4040, 3644, 3458
  //5644, 6040, 6458
};
int tempo4[] = { // 빠른 세박자 템포
  18, 18, 18
};
int melody6[] =  { // ready to input 라-파
  NOTE_A, NOTE_F
};
int tempo5[] = { // 2개
  12, 12
};
int melody7[] = { // someone appeared in front of the door
  NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_F, NOTE_G, NOTE_G,
  NOTE_E, NOTE_G, NOTE_F, NOTE_E, NOTE_F, NOTE_D, NOTE_E
};
int tempo6[] = { // 14개
  12, 12, 4, 12, 4, 12, 3, 6, 7, 4, 12, 7, 7, 3
};
int melody8[] = { // input butten 미
  NOTE_A
};
int tempo7[] = { // 1개
  12
};


// Ultrasonic Sensor 관련 선언
#define trigPin A2
#define echoPin A3


// password 입력 관련 선언
char password[] = {'1', '2', '3', '4'}; // password 설정
char input_status = 0; // keypad input 받는 상태 여부
char bluetooth_status = 0; // bluetooth input 받는 상태 여부
int input_count = 0; // password 누른 횟수
int input_right = 0; // password 일치 횟수
int password_count = 0; // password 틀린 횟수


// LCD 출력 관련 선언
char inputPassword[5];
char str[40];


// doorlock 관련 선언
char lock_status = 1;
char open_status_available = 0;
int close_count = 0;


// IR sensor 관련 선언
int motion = 13; ////// PIN NUMBER //////
int test = 2;


// interrupt 관련 선언
int button = A0;
volatile int interrupt = LOW;
volatile int state = LOW;
volatile unsigned long current_high;
volatile unsigned long current_low;


void setup()
{
  // serial 모니터
  Serial.begin(9600);

  // bluetooth 수신
  bluetooth.begin(9600);

  // Servo 모터 출력
  servo.attach(motor_control);
  servo.write(180); // 잠금

  // Buzzer 출력
  pinMode(buzzerPin, OUTPUT);

  // LED 출력
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_white, OUTPUT);
  digitalWrite(LED_red, HIGH);
  digitalWrite(LED_green, LOW);

  // Ultrasonic 거리 측정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // IR sensor
  pinMode(motion, INPUT);

  // interrupt
  pinMode(button, INPUT);
  attachInterrupt(0, read_button, CHANGE);
}


void loop()
{
  // if door is locked
  if (lock_status) {
    char key_pressed = myKeypad.getKey();
    char phone_pressed = (char)bluetooth.read();

    // LCD output
    Serial.print("$CLEAR\r\n");

    // button interrupt
    if (interrupt) {
      interrupt = 0;
      setUnlocked();
    }

    /*    // IR sensor 측정
        int sensor = digitalRead(motion);
        if (sensor == HIGH) {

        }
    */

    if (key_pressed == '#' || phone_pressed == '#') {

      // LCD output
      Serial.print("$CLEAR\r\n");
      Serial.print("$GO 1 1\r\n");
      Serial.print("$PRINT INPUT PASSWORD : \r\n");
      Serial.print("$GO 2 1\r\n");
      Serial.print("$PRINT \r\n");

      input_status = 1;
      melody(6);
      while (input_status) {
        key_pressed = myKeypad.getKey();
        if (bluetooth.available()) {
          phone_pressed = (char)bluetooth.read();
          bluetooth_status = 1;
        }

        // when input something
        if (key_pressed != NO_KEY || bluetooth_status) {
          bluetooth_status = 0;
          // if input '#' or count 4, finish input
          if (key_pressed == '#' || phone_pressed == '#' || input_count == 4 ) {
            if (input_count == 4 && input_count == input_right) {
              setUnlocked();
              lock_status = 0;
              password_count = 0;
            } else {
              // LCD output
              Serial.print("$CLEAR\r\n");
              Serial.print("$GO 1 1\r\n");
              Serial.print("$PRINT WRONG PASSWORD\r\n");
              Serial.print("$GO 2 1\r\n");
              Serial.print("$PRINT TRY AGAIN\r\n");

              melody(4);
              delay(1000);
              password_count++;
            }

            // if password wrong more than 3 times
            if (password_count == 3) {
              for (int i = 0; i < 13; i++) {
                // LCD output
                if (i % 2) {
                  Serial.print("$CLEAR\r\n");
                  Serial.print("$GO 1 1\r\n");
                  Serial.print("$PRINT WARNNING!!\r\n");
                  Serial.print("$GO 2 1\r\n");
                  Serial.print("$PRINT YOU WRONG 3 TIMES\r\n");
                } else {
                  Serial.print("$CLEAR\r\n");
                }

                digitalWrite(LED_red, LOW);
                melody(5);
                digitalWrite(LED_red, HIGH);
                melody(5);
              }
              password_count = 0;
            }

            input_status = 0;
            input_count = 0;
            input_right = 0;
          } else if (key_pressed == password[input_count] || phone_pressed == password[input_count]) {
            // LCD output
            inputPassword[input_count] = key_pressed;
            inputPassword[input_count + 1] = '\0';
            sprintf(str, "$PRINT %s\r\n", inputPassword);
            Serial.print("$CLEAR\r\n");
            Serial.print("$GO 1 1\r\n");
            Serial.print("$PRINT INPUT PASSWORD : \r\n");
            Serial.print("$GO 2 1\r\n");
            Serial.print(str);
            Serial.print("$CURSOR 1 1\r \n");

            melody(8);
            input_count++;
            input_right++;

          } else {
            // LCD output
            inputPassword[input_count] = key_pressed;
            inputPassword[input_count + 1] = '\0';
            sprintf(str, "$PRINT %s\r\n", inputPassword);
            Serial.print("$CLEAR\r\n");
            Serial.print("$GO 1 1\r\n");
            Serial.print("$PRINT INPUT PASSWORD : \r\n");
            Serial.print("$GO 2 1\r\n");
            Serial.print(str);
            Serial.print("$CURSOR 1 1\r \n");

            melody(8);
            input_count++;
          }
        }
      }
    }
  }
  // if door is unlocked
  else {

    if (interrupt) {
      interrupt = 0;
      setLocked();
    }

    delay(500);
    float distance = getDistanceUltrasonicSensor();
    Serial.print("$CLEAR\r\n");

    if (open_status_available == 1) {
      if (close_count == 3) {
        // LCD output
        Serial.print("$CLEAR\r\n");
        Serial.print("$GO 1 1\r\n");
        Serial.print("$PRINT Closing...\r\n");
        melody(3); // close 알림 melody

        if (getDistanceUltrasonicSensor() < 4) {
          close_count = 0;
          lock_status = 1;
          open_status_available = 0;
          delay(1000);
          setLocked();
        } else { // if open again
          close_count = 0;
        }
      } else { // distance에 따라 count 증가 또는 초기화
        if (distance < 4) { // 2cm ~ 4cm 사이 close 값으로 하기
          close_count++;
        } else {
          close_count = 0;
        }
      }
    }

    else { // after unlocked, still not opened
      if (close_count > 8 || distance > 4) {
        open_status_available = 1;
        close_count = 0;
      } else {
        close_count++;
      }
    }
  }
}

// button interrupt
void read_button() {

  if (digitalRead(button) == HIGH) {
    current_high = millis();
    state = HIGH;
  }

  if (digitalRead(button) == LOW && state == HIGH) {
    current_low = millis();

    if ((current_low - current_high) > 0 && (current_low - current_high) < 3000) {
      if (lock_status) {
        lock_status = 0;
      } else {
        lock_status = 1;
      }
      Serial.println("인터럽트!! 열려라 참깨!!");
      interrupt = 1;
      state = LOW;
    }
  }
}

// change locked
void setLocked() {
  ;
  // LCD output
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print("$PRINT DOOR IS LOCKED\r\n");
  Serial.print("$GO 2 1\r\n");
  Serial.print("$PRINT SECURE THE HOUSE\r\n");

  servo.write(180); // locked
  digitalWrite(LED_red, HIGH);
  digitalWrite(LED_green, LOW);
  melody(2);
  delay(1000);
}


// change unlocked
void setUnlocked() {
  // LCD output
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print("$PRINT DOOR IS UNLOCKED\r\n");
  Serial.print("$GO 2 1\r\n");
  Serial.print("$PRINT WELLCOME HOME\r\n");

  servo.write(90); // unlocked
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_green, HIGH);
  melody(1);
  delay(1000);
}


// get distance from Ultrasonic sensor
float getDistanceUltrasonicSensor() {
  // Ultrasonic 측정
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration / 29.0 / 2.0;
  Serial.print(distance);
  Serial.println("cm");

  return distance;
}

// select melody
void melody(int s) {
  int size = 0;
  int situation = s;
  switch (situation) {
    case 1:
      size = sizeof(melody1) / sizeof(int);
      Serial.println("melody1, 'Unlocked melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo1[thisNote];
        buzz(buzzerPin, melody1[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 2:
      size = sizeof(melody2) / sizeof(int);
      Serial.println("melody2, 'Locked melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo1[thisNote];
        buzz(buzzerPin, melody2[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 3:
      size = sizeof(melody3) / sizeof(int);
      Serial.println("melody3, 'Closed melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo2[thisNote];
        buzz(buzzerPin, melody3[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 4:
      size = sizeof(melody4) / sizeof(int);
      Serial.println("melody4, 'Password wrong melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo3[thisNote];
        buzz(buzzerPin, melody4[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 5:
      size = sizeof(melody5) / sizeof(int);
      Serial.println("melody5, 'Password wrong melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo4[thisNote];
        buzz(buzzerPin, melody5[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 6:
      size = sizeof(melody6) / sizeof(int);
      Serial.println("melody6, 'ready to input melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo5[thisNote];
        buzz(buzzerPin, melody6[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 7:
      size = sizeof(melody7) / sizeof(int);
      Serial.println("melody7, 'someone appeared in front of the door melody'");
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / tempo6[thisNote];
        buzz(buzzerPin, melody7[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        buzz(buzzerPin, 0, noteDuration);
      }
      break;
    case 8:
      int noteDuration = 1000 / tempo7[0];
      Serial.println("melody8, 'input button melody'");

      buzz(buzzerPin, melody8[0], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(buzzerPin, 0, noteDuration);

      break;
  }
}


// play melody by buzzer
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);
}
