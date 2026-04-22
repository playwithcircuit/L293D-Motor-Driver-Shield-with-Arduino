/* 
Interfacing Stepper Motor 28BYJ-48 with Arduino UNO using L293D motor Driver shield
by www.playwithcircuit.com 
*/

#include <AFMotor.h>            // Library to run Stepper Motor Using Motor Driver Shield
#include <LiquidCrystal_I2C.h>  // Library to Run I2C LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Format -> (Address,Columns,Rows )

// Create the stepper motor object connected to M3 and M4
AF_Stepper motor(2048, 2);  // 2048 steps per rotation for 28BYJ-48, connected to motor ports 3 and 4

// Define button pins
const int forwardButtonPin = A1;
const int reverseButtonPin = A2;
const int stopButtonPin    = A3;

// Define potentiometer pin
const int potPin = A0;

// Variables to store motor state and direction
bool motorRunning = false;
int motorDirection = BACKWARD;  // FORWARD or BACKWARD

// Read the potentiometer value
int potValue;
int motorSpeed;

// Variable to store button states
bool forwardButtonState;
bool stopButtonState;
bool reverseButtonState;

// Inline function to check if button is pressed packed with debouncing logic
inline bool chkButtonState(int pinNum, int checkState, int debounceDelay) {
  if (((digitalRead(pinNum) == checkState) ? true : false) == true) {
    delay(debounceDelay);
    return (((digitalRead(pinNum) == checkState) ? (true) : (false)) == true);
  } else {
    return false;
  }
}

void setup() {
  // initialize the lcd
  lcd.init();
  // Turn on the Backlight
  lcd.backlight();
  // Clear the display buffer
  lcd.clear();

  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Stepper Motor");
  lcd.setCursor(0, 1);
  lcd.print("using Shield");

  // Set button pins as inputs
  pinMode(forwardButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(reverseButtonPin, INPUT_PULLUP);

  // Start with motor off
  motor.setSpeed(0);
  motor.release();  // Stop the motor

  delay(2000);

  // Clear the display buffer
  lcd.clear();
  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Motor Direction:");
  lcd.setCursor(0, 1);
  lcd.print("Stopped   ");
}

void loop() {
  // Read the potentiometer value for changing speed as per Analog input
  potValue = analogRead(potPin);
  motorSpeed = map(potValue, 0, 1023, 3, 15);

  // Read the button states
  forwardButtonState = chkButtonState(forwardButtonPin, LOW, 20);
  reverseButtonState = chkButtonState(reverseButtonPin, LOW, 20);
  stopButtonState    = chkButtonState(stopButtonPin,    LOW, 20);


  // check for Forward run
  if (forwardButtonState && (!motorRunning || motorDirection == BACKWARD)) {
    // Set cursor (Column, Row)
    lcd.setCursor(0, 1);
    lcd.print("Clock   ");
    if (motorDirection == BACKWARD) {
      motor.setSpeed(0);
      motor.release();  // Stop the motor
      delay(1000);
    }
    motorRunning = true;
    motorDirection = FORWARD;
    motor.setSpeed(motorSpeed);
    motor.step(32, FORWARD, SINGLE);  // Move one step forward
  }
  // check for Reverse run
  else if (reverseButtonState && (!motorRunning || motorDirection == FORWARD)) {
    // Set cursor (Column, Row)
    lcd.setCursor(0, 1);
    lcd.print("Anti-Clk");
    if (motorDirection == FORWARD) {
      motor.setSpeed(0);
      motor.release();  // Stop the motor
      delay(1000);
    }
    motorRunning = true;
    motorDirection = BACKWARD;
    motor.setSpeed(motorSpeed);
    motor.step(32, BACKWARD, SINGLE);  // Move one step backward
  }
  // Stop motor
  else if (stopButtonState && motorRunning) {
    // Set cursor (Column, Row)
    lcd.setCursor(0, 1);
    lcd.print("Stopped         ");
    motorRunning = false;
    motor.setSpeed(0);
    motor.release();  // Stop the motor
  } else if (motorRunning) {
    if (motorDirection == FORWARD) {
      motor.step(32, FORWARD, SINGLE);  // Continue moving forward
    } else {
      motor.step(32, BACKWARD, SINGLE);  // Continue moving backward
    }
    motor.setSpeed(motorSpeed);
    // Set cursor (Column, Row)
    lcd.setCursor(9, 1);
    lcd.print("SPD:");
    lcd.print(((motorSpeed * 100) / 15));
    lcd.print("%  ");
  }
}