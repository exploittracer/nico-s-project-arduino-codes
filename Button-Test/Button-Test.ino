/*
  Button Test

  Outputs to serial monitor the status of start button and 
  stop button

  The circuit:
  - 2 buttons connected to GND
  - start button attached to pin 7
  - stop button attached to pin 8

  References:
  https://docs.arduino.cc/built-in-examples/digital/Button/
  https://newbiely.com/tutorials/arduino-nano/arduino-nano-button
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int startButtonPin = 7;  // the number of the start button pin
const int stopButtonPin = 8;  // the number of the stop button pin

// variables will change:
int startButtonState = 0;  // variable for reading the pushbutton status
int stopButtonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the built in LED as an output:
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the button pins as an pull up input:
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  // set serial communication baud rate at 9600
  Serial.begin(9600);
}

void loop() {
  // read the state of the buttons value:
  startButtonState = digitalRead(startButtonPin);
  stopButtonState = digitalRead(stopButtonPin);

  // check if the pushbuttons are pressed. Different output 
  // displayed based on the combination of button pressed.

  if ((startButtonState == HIGH) && (stopButtonState == HIGH)){
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Both High");

  } else if ((startButtonState == HIGH) && (stopButtonState == LOW)){
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Stop button Low");

  } else if ((startButtonState == LOW) && (stopButtonState == HIGH)){
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Start button Low");

  } else if ((startButtonState == LOW) && (stopButtonState == LOW)){
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Both Low");
  }
  delay(100);
}
