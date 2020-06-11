#include <SoftwareSerial.h>

int bluetooth_Tx = 2;
int bluetooth_Rx = 3;
int LED1 = 9;
int LED2 = 10;
int LED3 = 11;
bool toggle1 = false;
bool toggle2 = false;
bool toggle3 = false;
SoftwareSerial bluetooth(bluetooth_Tx, bluetooth_Rx);

void setup()
{
  Serial.begin(9600);  
  delay(100);
  bluetooth.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  char cmd;
    
  if(bluetooth.available() ) {
    cmd = (char)bluetooth.read();
    Serial.print("Command = ");
    Serial.println(cmd);

    if( cmd == '1' ) {
      if(toggle1 == true) {
        toggle1 = false;
        Serial.println("LED1 ON");
        digitalWrite(LED1, HIGH);
      } else {
        toggle1 = true;
        Serial.println("LED1 OFF");
        digitalWrite(LED1, LOW);
      }
    }

    else if( cmd == '2' ) {
      if(toggle2 = !toggle2) {
        Serial.println("LED2 ON");
        digitalWrite(LED2, HIGH);
      } else {
        Serial.println("LED2 OFF");
        digitalWrite(LED2, LOW);
      }
    }

    else if( cmd == '3' ) {
      if(toggle3 = !toggle3) {
        Serial.println("LED3 ON");
        digitalWrite(LED3, HIGH);
      } else {
        Serial.println("LED3 OFF");
        digitalWrite(LED3, LOW);
      }
    }

    else if( cmd == '4' ) {
      toggle1 = true;
      toggle2 = true;
      toggle3 = true;

      Serial.println("All LEDS ON");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
    }

    else if( cmd == '5' ) {
      toggle1 = false;
      toggle2 = false;
      toggle3 = false;

      Serial.println("All LEDS OFF");
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
    
  }
}
