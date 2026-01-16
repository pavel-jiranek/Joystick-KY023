#ifndef JOYSTICK_KY023_H
#define JOYSTICK_KY023_H

#include <Arduino.h>

/// @brief Class for reading the KY023 joystick module
class JoystickKY023 {
 public:
  /// @brief Constructor for the JoystickKY023 class.
  /// @param xPin The pin number for the X-axis.
  /// @param yPin The pin number for the Y-axis.
  /// @param switchPin The pin number for the switch.
  /// @param zeroToleranceRange The range of the zero value.
  /// @param analogReadResolutionBits The number of bits for the analog read resolution.
  /// @param switchPinMode The mode for the switch pin.
  JoystickKY023(pin_size_t xPin, pin_size_t yPin, pin_size_t switchPin, float zeroToleranceRange = 0.01f,
      uint8_t analogReadResolutionBits = 10, PinMode switchPinMode = INPUT_PULLUP);

  /// @brief Calibrate the joystick to find the center point.
  /// @details The function assumes that the joystick is centered when the
  /// function is called.
  void calibrate();

  /// @brief Read the X-value in range -1.0 to 1.0.
  float getX() const;

  /// @brief Read the Y-value in range -1.0 to 1.0.
  float getY() const;

  /// @brief Read the switch value.
  bool isSwitchPressed() const;

 private:
  pin_size_t _xPin;
  pin_size_t _yPin;
  pin_size_t _switchPin;
  float _zeroToleranceRange;
  uint16_t _analogReadMax;

  float _centerX;
  float _centerY;

  float mapValue(uint16_t value, float center) const;
};

#endif
