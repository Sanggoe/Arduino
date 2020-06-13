// buzzer 음계 관련 선언
#define NOTE_C 2093
#define NOTE_D 2349
#define NOTE_E 2647
#define NOTE_F 2793
#define NOTE_G 3186
#define NOTE_A 3520
#define NOTE_B 3951
#define NOTE_C2 4186
#define NOTE_D2 4698
#define NOTE_E2 5274
#define NOTE_F2 5587
#define NOTE_G2 6271
#define NOTE_A2 7040

#define NOTE_B2 7902
#define NOTE_C3 8000
#define buzzerPin 3
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
  5644, 6040, 6458, 5644, 6040, 6458, 5644, 6040, 6458, 5644, 6040, 6458
};
int tempo4[] = { // 열두 박자 템포
  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18
};

// Servo 모터 관련 선언
#include <Servo.h>
int motor_control = 4;
Servo servo; 

// Ultrasonic Sensor 관련 선언
#define trigPin 5 
#define echoPin 6
int num = 0;



void setup() {
  // Serial 모니터
  Serial.begin(9600);

  // Buzzer 출력
  pinMode(buzzerPin, OUTPUT);

  // Servo 모터 출력
  servo.attach(motor_control);

  // Ultrasonic 거리 측정
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {
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

  
  if (distance < 3) {
    melody(3); // close
    delay(1000);
    servo.write(180); // lock
    melody(1); // lock
    delay(1000);
  } else if (distance < 20) {
    servo.write(90); // unlock
    melody(2); // unlock
    delay(1000);
  } else {
    melody(4);
    delay(1000);
    melody(5);
    melody(5);
    melody(5);
    melody(5);
    delay(1000);
  }
}
int situation = 0;

// select melody
void melody(int s) {
  int size = 0;
  situation = s;
  switch(situation) {
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
