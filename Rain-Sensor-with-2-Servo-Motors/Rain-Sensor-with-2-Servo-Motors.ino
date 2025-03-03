#include <Servo.h>

int rainPin = A0;
int thresholdValue = 500;
Servo servo9, servo10;

void setup() {
  servo9.attach(9);
  servo10.attach(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  reset_motors();
}
void loop() {
  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);

  if(sensorValue < thresholdValue){
    Serial.println(" - It's raining! Find a shelter for safety!");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    activate_rain_coat();
    activate_wiper();
  }
  else {
    Serial.println(" - No rain. It is safe to travel!");
    reset_motors();
  }
}

void reset_motors() {
  servo9.write(0);
  servo10.write(0);
  delay(500);
}

void activate_rain_coat() {
  servo9.write(180);
}

void activate_wiper() {
  servo10.write(0);
  Serial.println("Foward");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)  
  delay(500);

  servo10.write(180);
  Serial.println("Reverse");
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW  
  delay(500);

}