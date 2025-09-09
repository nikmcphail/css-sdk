#pragma once
#include "input_enums.h"

#define JOYSTICK_AXIS_INTERNAL(_joystick, _axis)                                               \
  (JOYSTICK_FIRST_AXIS + ((_joystick) * MAX_JOYSTICK_AXES) + (_axis))
#define JOYSTICK_AXIS(_joystick, _axis) ((AnalogCode_t)JOYSTICK_AXIS_INTERNAL(_joystick, _axis))

enum analog_code_e {
  ANALOG_CODE_INVALID = -1,
  MOUSE_X             = 0,
  MOUSE_Y,
  MOUSE_XY,
  MOUSE_WHEEL,
  JOYSTICK_FIRST_AXIS,
  JOYSTICK_LAST_AXIS = JOYSTICK_AXIS_INTERNAL(MAX_JOYSTICKS - 1, MAX_JOYSTICK_AXES - 1),
  ANALOG_CODE_LAST
};