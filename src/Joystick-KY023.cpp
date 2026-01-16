#include "Joystick-KY023.h"

namespace {
template <typename InputType, typename OutputType>
OutputType myMap(InputType value, InputType inMin, InputType inMax, OutputType outMin, OutputType outMax) {
  return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
}  // namespace

JoystickKY023::JoystickKY023(pin_size_t xPin, pin_size_t yPin, pin_size_t switchPin, float zeroToleranceRange,
    uint8_t analogReadResolutionBits, PinMode switchPinMode)
    : _xPin(xPin), _yPin(yPin), _switchPin(switchPin), _zeroToleranceRange(zeroToleranceRange) {
  _analogReadMax = (1 << analogReadResolutionBits) - 1;

  pinMode(switchPin, switchPinMode);
}

void JoystickKY023::calibrate() {
  const uint16_t sensorCenterX = analogRead(_xPin);
  const uint16_t sensorCenterY = analogRead(_yPin);

  _centerX = myMap(sensorCenterX, static_cast<uint16_t>(0), _analogReadMax, 0.0f, 1.0f);
  _centerY = myMap(sensorCenterX, static_cast<uint16_t>(0), _analogReadMax, 0.0f, 1.0f);
}

float JoystickKY023::getX() const {
  uint16_t value = analogRead(_xPin);
  return mapValue(value, _centerX);
}

float JoystickKY023::getY() const {
  uint16_t value = analogRead(_yPin);
  return mapValue(value, _centerY);
}

float JoystickKY023::mapValue(uint16_t value, float center) const {
  float normalized = myMap(value, static_cast<uint16_t>(0), _analogReadMax, 0.0f, 1.0f);
  float result = 0.0f;
  if (normalized > center + _zeroToleranceRange) {
    result = myMap(normalized, center + _zeroToleranceRange, 1.0f, 0.0f, 1.0f);
  } else if (normalized < center - _zeroToleranceRange) {
    result = myMap(normalized, 0.0f, center - _zeroToleranceRange, -1.0f, 0.0f);
  }
  return result;
}

bool JoystickKY023::isSwitchPressed() const { return digitalRead(_switchPin) == LOW; }
