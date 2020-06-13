#include <SoftwareSerial.h>
#include <string.h>
int bluetooth_Tx = 9;
int bluetooth_Rx = 10;
SoftwareSerial bluetooth(bluetooth_Tx, bluetooth_Rx);

int count=0;
char str[40];
char password[5];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  bluetooth.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char cmd;
  
  if(bluetooth.available() ) {
    cmd = (char)bluetooth.read();
    Serial.print("Command = ");
    Serial.println(cmd);
    password[count] = cmd;
    password[count+1] = '\0';
    
    sprintf(str, "$PRINT %s\r\n", password);
    Serial.print("$CLEAR\r\n");
    Serial.print("$GO 1 1\r\n");
    Serial.print("$PRINT PASSWORD\r\n");
    Serial.print("$GO 2 1\r\n");
    Serial.print(str);
    Serial.print("$CURSOR 1 1\r \n");
    
    if (++count >= 4) {
      int isPassword = 1;
      for(int i=0; i<count; i++) {
        if(atoi(password[i]) != (i+1)) {
          isPassword = 0;
        }
        password[count]='\0';
      }
      
      Serial.print("$CLEAR\r\n");
      Serial.print("$GO 1 1\r\n");
      if(isPassword) {
        Serial.print("$PRINT Welcome!\r\n");
      } else {
        Serial.print("$PRINT PASSWORD Wrong!\r\n");
      }
      count = 0;
    }
  }
}
