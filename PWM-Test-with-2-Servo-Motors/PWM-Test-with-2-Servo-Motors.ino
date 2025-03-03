#include <Servo.h>

Servo servo9, servo10;

void setup() {
  servo9.attach(9);
  servo10.attach(10);
  reset_motors();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(500);
}
void loop() {
  servo9.write(0);
  Serial.println("Foward");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)  
  delay(500);

  servo9.write(180);
  Serial.println("Reverse");
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW  
  delay(500);
}

void reset_motors() {
  servo9.write(0);
  servo10.write(0);
}