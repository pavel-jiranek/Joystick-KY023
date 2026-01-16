#include <Joystick-KY023.h>

constexpr pin_size_t X_PIN = A0;
constexpr pin_size_t Y_PIN = A1;
constexpr pin_size_t SWITCH_PIN = A2;

JoystickKY023 joystick(X_PIN, Y_PIN, SWITCH_PIN);

float lastX = 0.0f;
float lastY = 0.0f;
bool lastSwitchPressed = true;

void setup() {
  Serial.begin(9600);
  joystick.calibrate();
}

void loop() {
  const float currentX = joystick.getX();
  const float currentY = joystick.getY();
  const bool isSwitchPressed = joystick.isSwitchPressed();

  if (lastX != currentX || lastY != currentY) {
    Serial.print("X = ");
    Serial.print(currentX, 2);
    Serial.print(", Y = ");
    Serial.println(currentY, 2);
  }

  if (isSwitchPressed != lastSwitchPressed) {
    if (isSwitchPressed)
      Serial.println("Switch: Pressed");
    else
      Serial.println("Switch: Released");
  }

  lastX = currentX;
  lastY = currentY;
  lastSwitchPressed = isSwitchPressed;
}
