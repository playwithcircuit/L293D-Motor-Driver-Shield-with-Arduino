/* 
Interfacing Micro Servo Motor SG90 with Arduino UNO using L293D motor Driver shield
by www.playwithcircuit.com 
*/
#include <Servo.h>                                // Library to run Servo Motor
#include <LiquidCrystal_I2C.h>                    // Library to Run I2C LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Format -> (Address,Columns,Rows )

// Create the servo object connected to SER1
Servo servo;

// Define button pins
const int forwardButtonPin = A1;
const int reverseButtonPin = A2;

// Variable so save current Servo Angle
int servoAngle;

// Define potentiometer pin
const int potPin = A0;

// Read the potentiometer value
int potValue;
// Save motor Speed
int motorSpeed;
// Save previous motor Speed
int previousSpeed;
// counter to clear speed when motor is stopped
int counter = 100;;

void setup() {

  // initialize the lcd
  lcd.init();
  // Turn on the Backlight
  lcd.backlight();
  // Clear the display buffer
  lcd.clear();

  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Servo Motor using");
  lcd.setCursor(0, 1);
  lcd.print("L293D Shield");

  // Set the arm in middle i.e at 90 degree
  servoAngle = 90;

  // Set button pins as inputs
  pinMode(forwardButtonPin, INPUT_PULLUP);
  pinMode(reverseButtonPin, INPUT_PULLUP);

  // Initialize the servo motor, Pin 10 is connected to the PWM pin of Ser1 port of Arduino Shield
  servo.attach(10);
  servo.write(servoAngle); // Set servo to neutral position (90 degrees)

  delay(2000);

  // Clear the display buffer
  lcd.clear();
  // Set cursor (Column, Row)
  lcd.setCursor(0, 0);
  lcd.print("Motor Direction:");
  lcd.setCursor(0, 1);
  lcd.print("Stopped ");
}


void displaySpeed(void){
    // Set cursor (Column, Row)
    lcd.setCursor(9, 1);
    lcd.print("SPD:");
    lcd.print(((motorSpeed*100)/10));
    lcd.print("%  ");
    counter = 0;
}

void loop() {
  // Read the potentiometer value for changing speed as per Analog input
  potValue   = analogRead(potPin);
  motorSpeed = map(potValue, 0, 1023, 0, 10);

  // Read the button states
  bool forwardButtonState = (digitalRead(forwardButtonPin) == LOW);
  bool reverseButtonState = (digitalRead(reverseButtonPin) == LOW);

  // Control the servo motor
  if (forwardButtonState) {
    // Set cursor (Column, Row)
    lcd.setCursor(0, 1);
    lcd.print("Forward ");
    // Increse Servo Angle
    servoAngle+=motorSpeed;
    if(servoAngle>180)
    {
      servoAngle = 180;
    }
    displaySpeed();
  } else if (reverseButtonState) {
    // Set cursor (Column, Row)
    lcd.setCursor(0, 1);
    lcd.print("Backward");
    // Decrease Servo Angle
    servoAngle-=motorSpeed;
    if(servoAngle<0)
    {
      servoAngle = 0;
    }
    displaySpeed();
  }
  else
  {
    if(counter++ > 100)
    {
      lcd.setCursor(0, 1);
      lcd.print("Stopped         ");
      counter = 101;
    }
    else
    {
      // Set cursor (Column, Row)
      lcd.setCursor(0, 1);
      lcd.print("Stopped ");
    }
    
    if(previousSpeed != motorSpeed)
    {
      displaySpeed();
      previousSpeed = motorSpeed;
    }
  }
  servo.write(servoAngle); // Adjust as needed for your servo's forward position
}