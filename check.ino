#include <Keyboard.h>
#include <Mouse.h>

const int deadZone = 24;
const int maxZone = 12;
const int joyXPin = A0;    // Analog pin for X-axis of the joystick
const int joyYPin = A1;    // Analog pin for Y-axis of the joystick
const int joyButtonPin = 4; // Digital pin for the joystick button
const int button1 = 2;
const int button2 = 3;
const int mode = 0;
const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;
// mode, 0 = "mouse", joystick is mouse and joystick click is middle click. Button 1 = left click, Button 2 = right click
// mode, 1 = "wasd", joystick is wasd, mouse buttons are same.
// mode, 2 = "wasdcz", joystick is wasd, button 1 is c, button 2 is z, joystick is " "
// clicking and holding all buttons for 3 second changes mode

void setup() {
  // Initialize the Keyboard and Mouse libraries
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(joyButtonPin, INPUT_PULLUP); // Set the joystick button pin as input with an internal pull-up resistor
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}
int applyDeadAndMax(int value){
  value = value-512;
  if (abs(value)<deadZone){
    return 512;
  } else if (value>1023-maxZone){
    return 1023;
  } else if (abs(value)<maxZone){
    return 0;
  }
  return value+512;
}
int joystickHoriz() {
  return applyDeadAndMax(analogRead(joyXPin));
}

int joystickVert() {
  return applyDeadAndMax(analogRead(joyYPin));
}

bool joyPressed() {
  return !digitalRead(joyButtonPin); // Corrected the function and added '!' to invert the button state
}
bool onePressed() {
  return !digitalRead(button1);
}
bool twoPressed() {
  return !digitalRead(button2);
}

void loop() {
  // Read joystick values
  int xValue = joystickHoriz();
  int yValue = joystickVert();

  // Print joystick and button state
  Serial.print("X-Axis: ");
  Serial.print(xValue);
  Serial.print("\tY-Axis: ");
  Serial.print(yValue);
  Serial.print("\tButton: ");
  Serial.print(joyPressed() ? "Pressed" : "Released");
  Serial.print("\tButton1: ");
  Serial.print(onePressed() ? "Pressed" : "Released");
  Serial.print("\tButton2: ");
  Serial.println(twoPressed() ? "Pressed" : "Released");

  // Perform actions based on joystick and button state
  // Here you can add logic to send keyboard and mouse input based on joystick/button state
  // For example:
  if (xValue < 400) {
    // Keyboard.write('A'); // Send 'A' when joystick is moved to the left
    // Turn on the green LED and wait for a short moment
  digitalWrite(greenLED, HIGH);
  delay(100); // 100 milliseconds (0.1 second) delay

  // Turn off the green LED
  digitalWrite(greenLED, LOW);
  delay(50); // 50 milliseconds (0.05 second) delay

  // Turn on the yellow LED and wait for a short moment
  digitalWrite(yellowLED, HIGH);
  delay(100); // 100 milliseconds (0.1 second) delay

  // Turn off the yellow LED
  digitalWrite(yellowLED, LOW);
  delay(50); // 50 milliseconds (0.05 second) delay

  // Turn on the red LED and wait for a short moment
  digitalWrite(redLED, HIGH);
  delay(100); // 100 milliseconds (0.1 second) delay

  // Turn off the red LED
  digitalWrite(redLED, LOW);
  delay(50); // 50 milliseconds (0.05 second) delay
  }


  // You can add more logic for different joystick positions and button states

  
}
