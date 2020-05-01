#include <DHT.h>
#define DHTPIN 2 // 디지털 1번핀 사용
#define DHTTYPE DHT11 // DHT 11 모델 사용
DHT dht(DHTPIN, DHTTYPE);

#define trigPin A4
#define echoPin A5 


char str[40];

byte digitPin[4]={A0,A1,A2,A3}; // digit
byte segPin[8]={5,6,7,8,9,10,11,12}; // a~g,dp
const int delayTime = 10;

byte data[] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE4,0xFE,0xE6};

int num = 0;
int n1000 = 0;
int n100 = 0;
int n10 = 0;
int n1 = 0;
int cnt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for(int i=0;i<8;i++){
    pinMode(segPin[i], OUTPUT);
  }
  for(int j=0; j<4; j++){
    pinMode(digitPin[j], OUTPUT);
    digitalWrite(digitPin[j], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();//습도 읽기
  float t = dht.readTemperature();// 온도 읽기
  int tmp = (int)t;

  sprintf(str, "$PRINT Tmp: %d'C\r\n", tmp);
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print(str);
  Serial.print("$CURSOR 1 1\r \n");
  
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = ((float)(340 * duration) / 10000) / 2;
  num = 100*distance;    //(int)(duration * 100);
  num /= 2.54;
  n1000 = num/1000;
  n100 = num%1000/100;
  n10 = num%100/10;
  n1 = num%10;

  show(4, n1);
  delay(delayTime);
  show(3, n10);
  delay(delayTime);
  show(2, n100);
  delay(delayTime);
  show(1, n1000);
  delay(delayTime);
}

void show(int position, int number) { // 숫자 출력 사용자 정의 함수
  // 4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == position) {
      digitalWrite(digitPin[i], LOW);
    } else {
      digitalWrite(digitPin[i], HIGH);
    }
  }

  // 8개 세그먼트 제어, 원하는 숫자 출력
  for(int i = 0; i < 8; i++) {
    byte segment = (data[number] & (0x01 << i)) >> i;
    if(segment == 1) {
      digitalWrite(segPin[7-i], HIGH);
      if(position == 2)
        digitalWrite(segPin[7], HIGH);
    } else {
      digitalWrite(segPin[7-i], LOW);
    }
  }
}
