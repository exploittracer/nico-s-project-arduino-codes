#include <Servo.h>

Servo zorro;

void setup() {
  zorro.attach(9);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(500);
}
void loop() {
  zorro.write(0);
  Serial.println("Foward");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)  
  delay(500);

  zorro.write(180);
  Serial.println("Reverse");
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW  
  delay(500);
}

// #include <Servo.h>
// Servo servo;
// int angle = 10;
// void setup() {
//   servo.attach(9);
//   servo.write(angle);
//   Serial.begin(9600);
// }
// void loop() 
// { 
//  // scan from 0 to 180 degrees
//   for(angle = 10; angle < 180; angle++)  
//   {                                  
//     servo.write(angle);
//     Serial.println(angle);               
//     delay(15);                   
//   } 
//   // now scan back from 180 to 0 degrees
//   for(angle = 180; angle > 10; angle--)    
//   {                                
//     servo.write(angle); 
//     Serial.println(angle);          
//     delay(15);       
//   } 
// }