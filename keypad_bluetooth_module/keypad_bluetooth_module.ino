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
byte rowPins[numRows] = {8, 7, 6, 5};
byte colPins[numCols] = {4, 3, 2};
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

// bluetooth 관련 선언
#include <SoftwareSerial.h>
int bluetooth_Tx = 9;
int bluetooth_Rx = 10;
SoftwareSerial bluetooth(bluetooth_Tx, bluetooth_Rx);


void setup()
{
  // serial 모니터
  Serial.begin(9600);

  // bluetooth 수신
  bluetooth.begin(9600);
}

// password 입력 관련 선언
char password[] = {'1', '2', '3', '4'}; // password 설정
char input_status = 0; // keypad input 받는 상태 여부
char bluetooth_status = 0; // bluetooth input 받는 상태 여부
int input_count = 0; // password 누른 횟수
int input_right = 0; // password 일치 횟수

void loop()
{
  char key_pressed = myKeypad.getKey();
  char phone_pressed = (char)bluetooth.read();

  if (key_pressed == '#' || phone_pressed == '#') {
    Serial.print("# Input Password : ");
    input_status = 1;
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
          if (input_count != 0 && input_count == input_right) {
            Serial.println("\nPassword Collect!");
            // 잠금 해제
          } else {
            Serial.println("\nPassword Wrong!");
          }
          input_status = 0;
          input_count = 0;
          input_right = 0;
        } else if (key_pressed == password[input_count] || phone_pressed == password[input_count]) {
          input_count++;
          input_right++;
          Serial.print("key_pressed : ");
          Serial.print(key_pressed);
          Serial.print("  phone_pressed : ");
          Serial.println(phone_pressed);
        } else {
          input_count++;
          Serial.print("key_pressed : ");
          Serial.print(key_pressed);
          Serial.print("  phone_pressed : ");
          Serial.println(phone_pressed);
        }
      }
    }
  }
}
