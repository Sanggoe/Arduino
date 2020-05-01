#define trigPin 12 
#define echoPin 13 

void setup()  
{ 
    Serial.begin (9600); 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
} 

double microsecondsToInches(double microseconds)
{
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch 

    return microseconds / 74 / 2;
}

double microsecondsToCentimeters(double microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    
    return microseconds / 29 / 2;
}

void loop() 
{ 
    double duration, inches, cm;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(10); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    duration = pulseIn(echoPin, HIGH); 

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    Serial.print(inches);
    Serial.print("inch, ");
    Serial.print(cm);
    Serial.println(" cm"); 

    delay(100); 
}
