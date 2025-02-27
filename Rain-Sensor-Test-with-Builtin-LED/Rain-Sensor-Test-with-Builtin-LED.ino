/*
 
 All the resources for this project:
 https://randomnerdtutorials.com/
 
*/

int rainPin = A0;
// int greenLED = 6;
// int redLED = 7;
// you can adjust the threshold value
int thresholdValue = 500;

void setup(){
  pinMode(rainPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(greenLED, OUTPUT);
  // pinMode(redLED, OUTPUT);
  // digitalWrite(greenLED, LOW);
  // digitalWrite(redLED, LOW);
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println(" - It's wet");
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    // digitalWrite(greenLED, LOW);
    // digitalWrite(redLED, HIGH);
  }
  else {
    Serial.println(" - It's dry");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

    // digitalWrite(greenLED, HIGH);
    // digitalWrite(redLED, LOW);
  }
  delay(500);
}
