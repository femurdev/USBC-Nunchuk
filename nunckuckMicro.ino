#include <Keyboard.h>
#include <Mouse.h>

// Constants for joystick and button pins
const int joyXPin = A0;
const int joyYPin = A1;
const int joyButtonPin = 4;
const int buttonZ = 2;
const int buttonC = 3;

// Joystick deadzone and sensitivity settings
const int deadZone = 16;
const int maxZone = 12;
const float sensitivity = 1.0f;
const float joySlope = 1.5;
const int triggerPoint = 200;

// Mouse wheel control settings
const int wheelPerc = 1024;
const int timeBetweenPoll = 5;
const int timeBetweenPollWheel = 10;

// LED pins for different modes
const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;

// LED blinking duration
const int ledTime = 100;

// Variables for mode handling and key presses
int mode = 1; // change for startup mode
const int modes = 2;
unsigned long modeChangeStartTime = 0;
bool zWasPressed = false;
bool cWasPressed = false;
bool joyWasPressed = false;

// Key-press tracking for WASDCZ mode
bool wKeyWasPressed = false;
bool aKeyWasPressed = false;
bool sKeyWasPressed = false;
bool dKeyWasPressed = false;
bool zKeyWasPressed = false;
bool cKeyWasPressed = false;
bool spacebarKeyWasPressed = false;

void setup() {
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);

  pinMode(buttonZ, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(joyButtonPin, INPUT_PULLUP);

  // Set LED pins as OUTPUTd
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize LEDs to OFF state
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  controlLEDs();
}

// Function to apply deadzone and maximum values to joystick input
int applyDeadAndMax(int value) {
  value = value - 512;
  if (abs(value) < deadZone) {
    return 0;
  } else if (value > 512 - maxZone) {
    return 512;
  } else if (value < -512 + maxZone) {
    return -512;
  }
  return value;
}

// Functions to read joystick input
int joystickHoriz() {
  return applyDeadAndMax(analogRead(joyXPin));
}

int joystickVert() {
  return applyDeadAndMax(analogRead(joyYPin));
}

// Functions to check button states
bool joyPressed() {
  return !digitalRead(joyButtonPin);
}

bool zPressed() {
  return !digitalRead(buttonZ);
}

bool cPressed() {
  return !digitalRead(buttonC);
}

// Function to map joystick input in an exponential manner
int mapExponential(int value) {
  return getSign(value) * constrain(round(pow(abs(value) / 128.0, joySlope) * 128.0), -128, 128);
}

void releaseKey(char c){
    if (cKeyWasPressed && (c == 'c')){
    Keyboard.release('C');
    cKeyWasPressed = false;
  }
  if (zKeyWasPressed && (c == 'z')){
    Keyboard.release('Z');
    zKeyWasPressed = false;
  }
  if (wKeyWasPressed && (c == 'w')){
    Keyboard.release('w');
    wKeyWasPressed = false;
  }
  if (aKeyWasPressed && (c == 'a')){
    Keyboard.release('a');
    aKeyWasPressed = false;
  }
  if (sKeyWasPressed && (c == 's')){
    Keyboard.release('s');
    sKeyWasPressed = false;
  }
  if (dKeyWasPressed && (c == 'd')){
    Keyboard.release('d');
    dKeyWasPressed = false;
  }
  if (spacebarKeyWasPressed && (c == ' ')){
    Keyboard.release(' ');
    spacebarKeyWasPressed = false;
  }
}

// Function to determine the sign of a value
int getSign(int value) {
  if (value > 0) {
    return 1; // Positive
  } else if (value < 0) {
    return -1; // Negative
  } else {
    return 0; // Zero
  }
}

// Function to control LEDs based on the current mode
void controlLEDs() {
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // Blink the LEDs to indicate the mode number (mode + 1)
  for (int i = 0; i < mode + 1; i++) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
    delay(ledTime); // Blink for ledTime milliseconds
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    delay(ledTime); // Wait for ledTime milliseconds
  }

  // Keep the corresponding LED on based on the current mode
  if (mode == 0) {
    digitalWrite(redLED, HIGH);
  } else if (mode == 1) {
    digitalWrite(yellowLED, HIGH);
  } else if (mode == 2) {
    digitalWrite(greenLED, HIGH);
  }
}

void loop() {
  // Check for mode switch
  if (joyPressed() && zPressed() && cPressed()) {
    if (modeChangeStartTime == 0) {
      modeChangeStartTime = millis();
    } else {
      if (millis() - modeChangeStartTime > 3000) {
        mode = (mode == modes - 1) ? 0 : mode + 1;
        modeChangeStartTime = 0;
        Serial.println(mode);
        controlLEDs(); // Update LEDs to reflect the new mode
        Mouse.release(MOUSE_LEFT);
        Mouse.release(MOUSE_RIGHT);
        Mouse.release(MOUSE_MIDDLE);
        Keyboard.releaseAll();
      }
    }
  } else if (modeChangeStartTime != 0) {
    modeChangeStartTime = 0;
  }

  // Handle different modes
  if (mode == 0) {
    // Mode 0: Mouse control
    if (cPressed() && joyPressed()) {
      // Scroll
      Mouse.move(0, 0, mapExponential(-joystickVert() / wheelPerc));
      delay(timeBetweenPollWheel);
      return;
    } else {
      int xOffset = mapExponential(joystickHoriz() / 16);
      int yOffset = mapExponential(joystickVert() / 16);
      Mouse.move(xOffset, -yOffset); // Invert Y-axis for typical mouse movement
    }
    // Mouse button clicks
    if (cPressed() && !cWasPressed) {
      cWasPressed = true;
      Mouse.press(MOUSE_LEFT);
    }
    if (cWasPressed && !cPressed()) {
      cWasPressed = false;
      Mouse.release(MOUSE_LEFT);
    }
    if (zPressed() && !zWasPressed) {
      zWasPressed = true;
      Mouse.press(MOUSE_RIGHT);
    }
    if (zWasPressed && !zPressed()) {
      zWasPressed = false;
      Mouse.release(MOUSE_RIGHT);
    }
    if (joyPressed() && !joyWasPressed) {
      joyWasPressed = true;
      Mouse.press(MOUSE_MIDDLE);
    }
    if (joyWasPressed && !joyPressed()) {
      joyWasPressed = false;
      Mouse.release(MOUSE_MIDDLE);
    }
  } else if (mode == 1) {
    // Mode 1: WASDCZ control
    int xOffset = 0;
    int yOffset = 0;

    int horiz = joystickHoriz();
    int vert = joystickVert();

    // horiz wins
    // Serial.print("hoiz greater: ");
    // Serial.print(abs(horiz)>abs(vert));
    // Serial.print("\t");
    // Serial.print(abs(horiz));
    // Serial.print(" > ");
    // Serial.println(abs(vert));
    // if A isn't pressed, press it
    if (!aKeyWasPressed && abs(horiz)>triggerPoint && getSign(horiz) == -1){
      Keyboard.press('a');
      aKeyWasPressed = true;
      releaseKey('d');
    }
    // if D isn't pressed, press it
    else if (!dKeyWasPressed && abs(horiz)>triggerPoint&& getSign(horiz) == 1){
      Keyboard.press('d');
      dKeyWasPressed = true;
      releaseKey('a');
    } else if (abs(horiz)<triggerPoint) {
      releaseKey('a');
      releaseKey('d');
    }
    // vert wins
    // Serial.print("vert greater: ");
    // Serial.print(abs(horiz)>abs(vert));
    // Serial.print("\t");
    // Serial.print(abs(horiz));
    // Serial.print(" < ");
    // Serial.println(abs(vert));

    // if W isn't pressed, press it
    if (!wKeyWasPressed && abs(vert)>triggerPoint && getSign(vert) == 1){
      Keyboard.press('w');
      wKeyWasPressed = true;
      releaseKey('s');
    } 
    // if S isn't pressed, press it
    else if (!sKeyWasPressed && abs(vert)>triggerPoint && getSign(vert) == -1){
      Keyboard.press('s');
      sKeyWasPressed = true;
      releaseKey('w');
    } else if (abs(vert)<triggerPoint) {
      releaseKey('w');
      releaseKey('s');
    }
    
    // if (horiz==0 && vert==0) {
    //   Keyboard.releaseAll();
    // }
  }
  if (joyPressed() && !joyWasPressed) {
      joyWasPressed = true;
      Keyboard.press(' ');
      spacebarKeyWasPressed = true;
      
    }
    if (joyWasPressed && !joyPressed()) {
      joyWasPressed = false;
      Keyboard.release(' ');
      spacebarKeyWasPressed = false;
    }

    if (zPressed() && !zWasPressed) {
      zWasPressed = true;
      Keyboard.press('z');
      zKeyWasPressed = true;
      
    }
    if (zWasPressed && !zPressed()) {
      zWasPressed = false;
      Keyboard.release('z');
      zKeyWasPressed = false;
    }

    if (cPressed() && !cWasPressed) {
      cWasPressed = true;
      Keyboard.press('c');
      cKeyWasPressed = true;
      
    }
    if (cWasPressed && !cPressed()) {
      cWasPressed = false;
      Keyboard.release('c');
      cKeyWasPressed = false;
    }
    Serial.println(cPressed());

  delay(timeBetweenPoll);
}
