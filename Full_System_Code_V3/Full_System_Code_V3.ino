#include <Servo.h>

// State Machine
// enum machineStates {IDLE, SENSOR_ACTIVE, SENSOR_INACTIVE, BUTTON_ACTIVE, BUTTON_INACTIVE};
enum machineStates {IDLE, RAINCOAT_RELEASE, WIPER_ACTIVE, WIPER_INACTIVE, RAINCOAT_RESET};
machineStates state;
// String machineStatesArray[5] = {"IDLE", "SENSOR-ACTIVE", "SENSOR-INACTIVE", "BUTTON-ACTIVE", "BUTTON-INACTIVE"};

// Rain Sensor configurations
const int rainPin = A0; // the number of analog pin for Rain Sensor
// const int thresholdValue = 500; // the threshold value to detect rain
const int thresholdValue = 200; // the threshold value to detect rain

// Push buttons configurations
const int startButtonPin = 7;  // the number of the start button pin
const int stopButtonPin = 8;  // the number of the stop button pin
int startButtonState = 0;  // variable for reading the start hbutton status
int stopButtonState = 0;  // variable for reading the stop button status
int stopButtonCounter = 0;
bool isButtonActivated = false;

// Servo motor object
Servo rainCoatServo, wiperServo; // servo motors for raincoat and wiper

void setup() {
  rainCoatServo.attach(9); // attach raincoat servo to PWM pin 9
  wiperServo.attach(10); // attach wiper servo to PWM pin 10
  pinMode(LED_BUILTIN, OUTPUT); // initialize the built in LED as an output:

  // initialize the button pins as an pull up input:
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(stopButtonPin), stop_button_interrupt, FALLING);

  Serial.begin(9600);
  reset_motors();
}

void loop() {
  // read the state of the buttons value:
  startButtonState = digitalRead(startButtonPin);
  stopButtonState = digitalRead(stopButtonPin);

  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);
  Serial.print(": ");
  Serial.print(startButtonState);
  Serial.print(": ");
  Serial.print(stopButtonState);
  Serial.print(": ");
  Serial.print(isButtonActivated);
  Serial.print(": ");
  Serial.print(stopButtonCounter);
  Serial.print(": ");

  switch (state) {
    case IDLE: {
      Serial.println("IDLE");
      // reset_motors();
      stopButtonCounter = 0;
      isButtonActivated = false;
      if ((startButtonState == LOW) || (sensorValue < thresholdValue)) {
        // release_raincoat();
        if (startButtonState == LOW) {
          isButtonActivated = true;
        }
        else {
          isButtonActivated = false;
        }
        state = RAINCOAT_RELEASE;
      }
      delay(100);
    }
    break;

    case RAINCOAT_RELEASE: {
      Serial.println("RAINCOAT-RELEASED");
      release_raincoat();
      state = WIPER_ACTIVE;
    }
    break;

    case WIPER_ACTIVE: {
      Serial.println("WIPER-ACTIVATED");
      activate_wiper();
      if (stopButtonState == LOW) {
        stopButtonCounter = stopButtonCounter + 1;
      }
      
      if (((stopButtonState == LOW) && (stopButtonCounter = 2)) || ((sensorValue >= thresholdValue) && (isButtonActivated == false))) {
        // stopButtonCounter = 0;
        deactivate_wiper();
        state = WIPER_INACTIVE;
      }
    }
    break;

    case WIPER_INACTIVE: {
      Serial.println("WIPER-DEACTIVATED");
      // deactivate_wiper();
      if ((startButtonState == LOW) && (stopButtonState == LOW)) {
        reset_raincoat();
        state = RAINCOAT_RESET;
      } else if ((sensorValue < thresholdValue) && (stopButtonCounter == 0)) {
        state = WIPER_ACTIVE;
      }
      delay(100);
    }
    break;

    case RAINCOAT_RESET: {
      Serial.println("RAINCOAT-RESETTED");
      // reset_raincoat();
      delay(500);
      state = IDLE;
    }
    break;
  }
  // delay(500);
}

// initialize the motor angle position
void reset_motors() {
  wiperServo.write(0);
  rainCoatServo.write(0);
  delay(500);
}

void release_raincoat() {
  rainCoatServo.write(180);
  // delay(500);
}

void activate_wiper() {
  wiperServo.write(0);
  delay(500);

  wiperServo.write(180);
  delay(500);
}

void deactivate_wiper() {
  wiperServo.write(0);
  delay(500);
}

void reset_raincoat() {
  rainCoatServo.write(0);
  delay(500);
}


void stop_button_interrupt() {
  Serial.println("Stop button interrupt activated");
  reset_motors();
}