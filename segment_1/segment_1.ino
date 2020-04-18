int position_pin[] = {1,2,3,4}; //4자리 결정 핀
int segment_pin[] = {5,6,7,8,9,10,11,12}; //세그먼트 제어 핀
const int delayTime = 5;

byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

void setup() {
  //4자리 결정 핀 출력용으로 설정
  for(int i=0; i<4; i++) {
    pinMode(position_pin[i], OUTPUT);
  }

  //세그먼트 제어 핀 출력용으로 설정
  for(int i=0; i<8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
}

void loop() {
  show(1,0);
  delay(delayTime);
  show(2,0);
  delay(delayTime);
  show(3,0);
  delay(delayTime);
  show(4,0);
  delay(delayTime);
  //count();
  
}

void show(int position, int number) {
  for(int i=0; i<4; i++) {
    if(i+1==position) {
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  for(int i=0; i<8; i++) {
    byte segment = (data[number] & (0x01 << i)) >> i;
    if(segment == 1) {
      digitalWrite(segment_pin[7-i],HIGH);
    } else {
      digitalWrite(segment_pin[7-i],LOW);
    }
  }
}

void count() {
  for(int i=0; i<2; i++) {
    for(int j=0; j<10; j++) {
      for(int k=0; k<6; k++) {
        for(int l=0; l<10; l++) {
          if (i==1 && j==3){
            return;
          }
          show(1,i);
          delay(delayTime);
          show(2,j);
          delay(delayTime);
          show(3,k);
          delay(delayTime);
          show(4,l);
          delay(delayTime);
        }
      }
    }
  }
}
