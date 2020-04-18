int segValue[10][7] = {
   {1,1,1,1,1,1,0}, //0
   {0,1,1,0,0,0,0}, //1
   {1,1,0,1,1,0,1}, //2
   {1,1,1,1,0,0,1}, //3
   {0,1,1,0,0,1,1}, //4
   {1,0,1,1,0,1,1}, //5
   {1,0,1,1,1,1,1}, //6
   {1,1,1,0,0,0,0}, //7
   {1,1,1,1,1,1,1}, //8
   {1,1,1,1,0,1,1}  //9  
};
byte segPin[8]={5,6,7,8,9,10,11,12}; // a~g,dp
byte digitPin[4]={1,2,3,4}; // digit

extern volatile unsigned long timer0_millis; // 타이머 변수
unsigned long timeVal; // 이전 시간
unsigned long readTime; // 현재 타이머 시간
int hour, min, sec;
boolean state=false;

int d1 = 0; // 1의 자리
int d2 = 0; // 10의 자리
int d3 = 0; // 100의 자리
int d4 = 0; // 1000의 자리

void setup() {
  for(int i=0;i<8;i++){
    pinMode(segPin[i], OUTPUT);
  }
  for(int j=0; j<4; j++){
    pinMode(digitPin[j], OUTPUT);
    digitalWrite(digitPin[j], HIGH);
  }
}

void loop() {

  //if(millis() - timeVal >= 1000) { // 1초 단위 출력
    readTime = millis()/1;

    d1 = readTime%10; // 1의 자리
    d2 = (readTime/10)%10; // 10의 자리
    d3 = (readTime/100)%10; // 100의 자리
    d4 = (readTime/1000)%10; // 1000의 자리

    segOutput(3, d1,0); // 1의 자리
    if(readTime >= 10) segOutput(2,d2,0); // 10의 자리
    if(readTime >= 100) segOutput(1,d3,0); // 100의 자리
    if(readTime >= 1000) segOutput(0,d4,0); // 1000의 자리

}

// LED 초기화
void segClear() {
  for(int i=0; i<8; i++) {
    digitalWrite(segPin[i], LOW);
  }
 
}


// LED 출력
void segOutput(int d, int Number, int dp) {
  segClear();
  digitalWrite(digitPin[d], LOW);
  for(int i=0; i<7; i++) {
    digitalWrite(segPin[i], segValue[Number][i]);    
  }
  digitalWrite(segPin[7], dp);
  delayMicroseconds(1000);
  digitalWrite(digitPin[d], HIGH);
}
