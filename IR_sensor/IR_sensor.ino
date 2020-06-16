/*
  제목  : 인체감지센서 사용하기
  내용  : 인체감지센서를 오렌지보드에 연결하여 사람의 움직임이 인식되면 내장LED를 켜고, 아니면 내장 LED를 꺼지도록 만들어봅시다.
*/

int motion = 13;
// 사용할 LED를 13번 핀으로 설정합니다.
int light = A1;

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
  // 인체감지센서의 핀을 INPUT으로 설정합니다.
  pinMode(motion, INPUT);
  // LED의 핀을 OUTPUT으로 설정합니다.
  pinMode(light, OUTPUT);
  // 시리얼 통신 속도 설정
  Serial.begin(9600);
}

// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.
void loop() {
  // 적외선 인체감지 센서에서 값을 읽는다
  int sensor = digitalRead(motion);
  // 센서값을 시리얼 모니터에 출력
  Serial.println(sensor);Serial.println("으\n");

  // 센서값이 HIGH(1)일 경우 13번 LED를 한번 깜빡인다
  if (sensor == HIGH) {
    // 내장된 LED가 연결된 핀의 로직레벨을 HIGH (5V)로 설정하여, LED가 켜지도록 합니다.
    digitalWrite(light, HIGH);
    // 0.5초 동안 대기합니다.
    delay(500);
  } else {
    // 내장된 LED가 연결된 핀의 로직레벨을 LOW (0V)로 설정하여, LED가 꺼지도록 합니다.
    digitalWrite(light, LOW);
    // 0.5초 동안 대기합니다.
    delay(500);
  }
}
