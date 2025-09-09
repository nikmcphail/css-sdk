#pragma once

#define MAX_STEAM_CONTROLLERS 8

enum { MAX_JOYSTICKS = 1, MOUSE_BUTTON_COUNT = 5, MAX_NOVINT_DEVICES = 2 };

enum joystick_axis_e {
  JOY_AXIS_X = 0,
  JOY_AXIS_Y,
  JOY_AXIS_Z,
  JOY_AXIS_R,
  JOY_AXIS_U,
  JOY_AXIS_V,
  MAX_JOYSTICK_AXES
};

enum {
  MS_WM_XBUTTONDOWN   = 0x020B,
  MS_WM_XBUTTONUP     = 0x020C,
  MS_WM_XBUTTONDBLCLK = 0x020D,
  MS_MK_BUTTON4       = 0x0020,
  MS_MK_BUTTON5       = 0x0040
};

enum input_event_type_e {
  IE_ButtonPressed = 0,
  IE_ButtonReleased,
  IE_ButtonDoubleClicked,
  IE_AnalogValueChanged,
  IE_FirstSystemEvent = 100,
  IE_Quit             = IE_FirstSystemEvent,
  IE_ControllerInserted,
  IE_ControllerUnplugged,
  IE_FirstVguiEvent = 1000,
  IE_FirstAppEvent  = 2000
};

struct input_event_t {
  int m_nType  = 0;
  int m_nTick  = 0;
  int m_nData  = 0;
  int m_nData2 = 0;
  int m_nData3 = 0;
};

typedef enum {
  SK_NULL,
  SK_BUTTON_A,
  SK_BUTTON_B,
  SK_BUTTON_X,
  SK_BUTTON_Y,
  SK_BUTTON_UP,
  SK_BUTTON_RIGHT,
  SK_BUTTON_DOWN,
  SK_BUTTON_LEFT,
  SK_BUTTON_LEFT_BUMPER,
  SK_BUTTON_RIGHT_BUMPER,
  SK_BUTTON_LEFT_TRIGGER,
  SK_BUTTON_RIGHT_TRIGGER,
  SK_BUTTON_LEFT_GRIP,
  SK_BUTTON_RIGHT_GRIP,
  SK_BUTTON_LPAD_TOUCH,
  SK_BUTTON_RPAD_TOUCH,
  SK_BUTTON_LPAD_CLICK,
  SK_BUTTON_RPAD_CLICK,
  SK_BUTTON_LPAD_UP,
  SK_BUTTON_LPAD_RIGHT,
  SK_BUTTON_LPAD_DOWN,
  SK_BUTTON_LPAD_LEFT,
  SK_BUTTON_RPAD_UP,
  SK_BUTTON_RPAD_RIGHT,
  SK_BUTTON_RPAD_DOWN,
  SK_BUTTON_RPAD_LEFT,
  SK_BUTTON_SELECT,
  SK_BUTTON_START,
  SK_BUTTON_STEAM,
  SK_BUTTON_INACTIVE_START,
  SK_VBUTTON_F1,
  SK_VBUTTON_F2,
  SK_VBUTTON_F3,
  SK_VBUTTON_F4,
  SK_VBUTTON_F5,
  SK_VBUTTON_F6,
  SK_VBUTTON_F7,
  SK_VBUTTON_F8,
  SK_VBUTTON_F9,
  SK_VBUTTON_F10,
  SK_VBUTTON_F11,
  SK_VBUTTON_F12,
  SK_MAX_KEYS
} skey_e;

enum steam_pad_axis_e {
  LEFTPAD_AXIS_X,
  LEFTPAD_AXIS_Y,
  RIGHTPAD_AXIS_X,
  RIGHTPAD_AXIS_Y,
  LEFT_TRIGGER_AXIS,
  RIGHT_TRIGGER_AXIS,
  GYRO_AXIS_PITCH,
  GYRO_AXIS_ROLL,
  GYRO_AXIS_YAW,
  MAX_STEAMPADAXIS = GYRO_AXIS_YAW
};

enum { LASTINPUT_KBMOUSE = 0, LASTINPUT_CONTROLLER = 1, LASTINPUT_STEAMCONTROLLER = 2 };

enum game_action_set_e {
  GAME_ACTION_SET_NONE         = -1,
  GAME_ACTION_SET_MENUCONTROLS = 0,
  GAME_ACTION_SET_FPSCONTROLS,
  GAME_ACTION_SET_IN_GAME_HUD,
  GAME_ACTION_SET_SPECTATOR
};

enum game_action_set_flags_e {
  GAME_ACTION_SET_FLAGS_NONE     = 0,
  GAME_ACTION_SET_FLAGS_TAUNTING = (1 << 0)
};

enum joystick_type_e {
  INPUT_TYPE_GENERIC_JOYSTICK = 0,
  INPUT_TYPE_X360,
  INPUT_TYPE_STEAMCONTROLLER
};

enum controller_action_origin_e {
  // Steam Controller
  k_EControllerActionOrigin_None,
  k_EControllerActionOrigin_A,
  k_EControllerActionOrigin_B,
  k_EControllerActionOrigin_X,
  k_EControllerActionOrigin_Y,
  k_EControllerActionOrigin_LeftBumper,
  k_EControllerActionOrigin_RightBumper,
  k_EControllerActionOrigin_LeftGrip,
  k_EControllerActionOrigin_RightGrip,
  k_EControllerActionOrigin_Start,
  k_EControllerActionOrigin_Back,
  k_EControllerActionOrigin_LeftPad_Touch,
  k_EControllerActionOrigin_LeftPad_Swipe,
  k_EControllerActionOrigin_LeftPad_Click,
  k_EControllerActionOrigin_LeftPad_DPadNorth,
  k_EControllerActionOrigin_LeftPad_DPadSouth,
  k_EControllerActionOrigin_LeftPad_DPadWest,
  k_EControllerActionOrigin_LeftPad_DPadEast,
  k_EControllerActionOrigin_RightPad_Touch,
  k_EControllerActionOrigin_RightPad_Swipe,
  k_EControllerActionOrigin_RightPad_Click,
  k_EControllerActionOrigin_RightPad_DPadNorth,
  k_EControllerActionOrigin_RightPad_DPadSouth,
  k_EControllerActionOrigin_RightPad_DPadWest,
  k_EControllerActionOrigin_RightPad_DPadEast,
  k_EControllerActionOrigin_LeftTrigger_Pull,
  k_EControllerActionOrigin_LeftTrigger_Click,
  k_EControllerActionOrigin_RightTrigger_Pull,
  k_EControllerActionOrigin_RightTrigger_Click,
  k_EControllerActionOrigin_LeftStick_Move,
  k_EControllerActionOrigin_LeftStick_Click,
  k_EControllerActionOrigin_LeftStick_DPadNorth,
  k_EControllerActionOrigin_LeftStick_DPadSouth,
  k_EControllerActionOrigin_LeftStick_DPadWest,
  k_EControllerActionOrigin_LeftStick_DPadEast,
  k_EControllerActionOrigin_Gyro_Move,
  k_EControllerActionOrigin_Gyro_Pitch,
  k_EControllerActionOrigin_Gyro_Yaw,
  k_EControllerActionOrigin_Gyro_Roll,

  // PS4 Dual Shock
  k_EControllerActionOrigin_PS4_X,
  k_EControllerActionOrigin_PS4_Circle,
  k_EControllerActionOrigin_PS4_Triangle,
  k_EControllerActionOrigin_PS4_Square,
  k_EControllerActionOrigin_PS4_LeftBumper,
  k_EControllerActionOrigin_PS4_RightBumper,
  k_EControllerActionOrigin_PS4_Options, // Start
  k_EControllerActionOrigin_PS4_Share,   // Back
  k_EControllerActionOrigin_PS4_LeftPad_Touch,
  k_EControllerActionOrigin_PS4_LeftPad_Swipe,
  k_EControllerActionOrigin_PS4_LeftPad_Click,
  k_EControllerActionOrigin_PS4_LeftPad_DPadNorth,
  k_EControllerActionOrigin_PS4_LeftPad_DPadSouth,
  k_EControllerActionOrigin_PS4_LeftPad_DPadWest,
  k_EControllerActionOrigin_PS4_LeftPad_DPadEast,
  k_EControllerActionOrigin_PS4_RightPad_Touch,
  k_EControllerActionOrigin_PS4_RightPad_Swipe,
  k_EControllerActionOrigin_PS4_RightPad_Click,
  k_EControllerActionOrigin_PS4_RightPad_DPadNorth,
  k_EControllerActionOrigin_PS4_RightPad_DPadSouth,
  k_EControllerActionOrigin_PS4_RightPad_DPadWest,
  k_EControllerActionOrigin_PS4_RightPad_DPadEast,
  k_EControllerActionOrigin_PS4_CenterPad_Touch,
  k_EControllerActionOrigin_PS4_CenterPad_Swipe,
  k_EControllerActionOrigin_PS4_CenterPad_Click,
  k_EControllerActionOrigin_PS4_CenterPad_DPadNorth,
  k_EControllerActionOrigin_PS4_CenterPad_DPadSouth,
  k_EControllerActionOrigin_PS4_CenterPad_DPadWest,
  k_EControllerActionOrigin_PS4_CenterPad_DPadEast,
  k_EControllerActionOrigin_PS4_LeftTrigger_Pull,
  k_EControllerActionOrigin_PS4_LeftTrigger_Click,
  k_EControllerActionOrigin_PS4_RightTrigger_Pull,
  k_EControllerActionOrigin_PS4_RightTrigger_Click,
  k_EControllerActionOrigin_PS4_LeftStick_Move,
  k_EControllerActionOrigin_PS4_LeftStick_Click,
  k_EControllerActionOrigin_PS4_LeftStick_DPadNorth,
  k_EControllerActionOrigin_PS4_LeftStick_DPadSouth,
  k_EControllerActionOrigin_PS4_LeftStick_DPadWest,
  k_EControllerActionOrigin_PS4_LeftStick_DPadEast,
  k_EControllerActionOrigin_PS4_RightStick_Move,
  k_EControllerActionOrigin_PS4_RightStick_Click,
  k_EControllerActionOrigin_PS4_RightStick_DPadNorth,
  k_EControllerActionOrigin_PS4_RightStick_DPadSouth,
  k_EControllerActionOrigin_PS4_RightStick_DPadWest,
  k_EControllerActionOrigin_PS4_RightStick_DPadEast,
  k_EControllerActionOrigin_PS4_DPad_North,
  k_EControllerActionOrigin_PS4_DPad_South,
  k_EControllerActionOrigin_PS4_DPad_West,
  k_EControllerActionOrigin_PS4_DPad_East,
  k_EControllerActionOrigin_PS4_Gyro_Move,
  k_EControllerActionOrigin_PS4_Gyro_Pitch,
  k_EControllerActionOrigin_PS4_Gyro_Yaw,
  k_EControllerActionOrigin_PS4_Gyro_Roll,

  // XBox One
  k_EControllerActionOrigin_XBoxOne_A,
  k_EControllerActionOrigin_XBoxOne_B,
  k_EControllerActionOrigin_XBoxOne_X,
  k_EControllerActionOrigin_XBoxOne_Y,
  k_EControllerActionOrigin_XBoxOne_LeftBumper,
  k_EControllerActionOrigin_XBoxOne_RightBumper,
  k_EControllerActionOrigin_XBoxOne_Menu, // Start
  k_EControllerActionOrigin_XBoxOne_View, // Back
  k_EControllerActionOrigin_XBoxOne_LeftTrigger_Pull,
  k_EControllerActionOrigin_XBoxOne_LeftTrigger_Click,
  k_EControllerActionOrigin_XBoxOne_RightTrigger_Pull,
  k_EControllerActionOrigin_XBoxOne_RightTrigger_Click,
  k_EControllerActionOrigin_XBoxOne_LeftStick_Move,
  k_EControllerActionOrigin_XBoxOne_LeftStick_Click,
  k_EControllerActionOrigin_XBoxOne_LeftStick_DPadNorth,
  k_EControllerActionOrigin_XBoxOne_LeftStick_DPadSouth,
  k_EControllerActionOrigin_XBoxOne_LeftStick_DPadWest,
  k_EControllerActionOrigin_XBoxOne_LeftStick_DPadEast,
  k_EControllerActionOrigin_XBoxOne_RightStick_Move,
  k_EControllerActionOrigin_XBoxOne_RightStick_Click,
  k_EControllerActionOrigin_XBoxOne_RightStick_DPadNorth,
  k_EControllerActionOrigin_XBoxOne_RightStick_DPadSouth,
  k_EControllerActionOrigin_XBoxOne_RightStick_DPadWest,
  k_EControllerActionOrigin_XBoxOne_RightStick_DPadEast,
  k_EControllerActionOrigin_XBoxOne_DPad_North,
  k_EControllerActionOrigin_XBoxOne_DPad_South,
  k_EControllerActionOrigin_XBoxOne_DPad_West,
  k_EControllerActionOrigin_XBoxOne_DPad_East,

  // XBox 360
  k_EControllerActionOrigin_XBox360_A,
  k_EControllerActionOrigin_XBox360_B,
  k_EControllerActionOrigin_XBox360_X,
  k_EControllerActionOrigin_XBox360_Y,
  k_EControllerActionOrigin_XBox360_LeftBumper,
  k_EControllerActionOrigin_XBox360_RightBumper,
  k_EControllerActionOrigin_XBox360_Start, // Start
  k_EControllerActionOrigin_XBox360_Back,  // Back
  k_EControllerActionOrigin_XBox360_LeftTrigger_Pull,
  k_EControllerActionOrigin_XBox360_LeftTrigger_Click,
  k_EControllerActionOrigin_XBox360_RightTrigger_Pull,
  k_EControllerActionOrigin_XBox360_RightTrigger_Click,
  k_EControllerActionOrigin_XBox360_LeftStick_Move,
  k_EControllerActionOrigin_XBox360_LeftStick_Click,
  k_EControllerActionOrigin_XBox360_LeftStick_DPadNorth,
  k_EControllerActionOrigin_XBox360_LeftStick_DPadSouth,
  k_EControllerActionOrigin_XBox360_LeftStick_DPadWest,
  k_EControllerActionOrigin_XBox360_LeftStick_DPadEast,
  k_EControllerActionOrigin_XBox360_RightStick_Move,
  k_EControllerActionOrigin_XBox360_RightStick_Click,
  k_EControllerActionOrigin_XBox360_RightStick_DPadNorth,
  k_EControllerActionOrigin_XBox360_RightStick_DPadSouth,
  k_EControllerActionOrigin_XBox360_RightStick_DPadWest,
  k_EControllerActionOrigin_XBox360_RightStick_DPadEast,
  k_EControllerActionOrigin_XBox360_DPad_North,
  k_EControllerActionOrigin_XBox360_DPad_South,
  k_EControllerActionOrigin_XBox360_DPad_West,
  k_EControllerActionOrigin_XBox360_DPad_East,

  // SteamController V2
  k_EControllerActionOrigin_SteamV2_A,
  k_EControllerActionOrigin_SteamV2_B,
  k_EControllerActionOrigin_SteamV2_X,
  k_EControllerActionOrigin_SteamV2_Y,
  k_EControllerActionOrigin_SteamV2_LeftBumper,
  k_EControllerActionOrigin_SteamV2_RightBumper,
  k_EControllerActionOrigin_SteamV2_LeftGrip_Lower,
  k_EControllerActionOrigin_SteamV2_LeftGrip_Upper,
  k_EControllerActionOrigin_SteamV2_RightGrip_Lower,
  k_EControllerActionOrigin_SteamV2_RightGrip_Upper,
  k_EControllerActionOrigin_SteamV2_LeftBumper_Pressure,
  k_EControllerActionOrigin_SteamV2_RightBumper_Pressure,
  k_EControllerActionOrigin_SteamV2_LeftGrip_Pressure,
  k_EControllerActionOrigin_SteamV2_RightGrip_Pressure,
  k_EControllerActionOrigin_SteamV2_LeftGrip_Upper_Pressure,
  k_EControllerActionOrigin_SteamV2_RightGrip_Upper_Pressure,
  k_EControllerActionOrigin_SteamV2_Start,
  k_EControllerActionOrigin_SteamV2_Back,
  k_EControllerActionOrigin_SteamV2_LeftPad_Touch,
  k_EControllerActionOrigin_SteamV2_LeftPad_Swipe,
  k_EControllerActionOrigin_SteamV2_LeftPad_Click,
  k_EControllerActionOrigin_SteamV2_LeftPad_Pressure,
  k_EControllerActionOrigin_SteamV2_LeftPad_DPadNorth,
  k_EControllerActionOrigin_SteamV2_LeftPad_DPadSouth,
  k_EControllerActionOrigin_SteamV2_LeftPad_DPadWest,
  k_EControllerActionOrigin_SteamV2_LeftPad_DPadEast,
  k_EControllerActionOrigin_SteamV2_RightPad_Touch,
  k_EControllerActionOrigin_SteamV2_RightPad_Swipe,
  k_EControllerActionOrigin_SteamV2_RightPad_Click,
  k_EControllerActionOrigin_SteamV2_RightPad_Pressure,
  k_EControllerActionOrigin_SteamV2_RightPad_DPadNorth,
  k_EControllerActionOrigin_SteamV2_RightPad_DPadSouth,
  k_EControllerActionOrigin_SteamV2_RightPad_DPadWest,
  k_EControllerActionOrigin_SteamV2_RightPad_DPadEast,
  k_EControllerActionOrigin_SteamV2_LeftTrigger_Pull,
  k_EControllerActionOrigin_SteamV2_LeftTrigger_Click,
  k_EControllerActionOrigin_SteamV2_RightTrigger_Pull,
  k_EControllerActionOrigin_SteamV2_RightTrigger_Click,
  k_EControllerActionOrigin_SteamV2_LeftStick_Move,
  k_EControllerActionOrigin_SteamV2_LeftStick_Click,
  k_EControllerActionOrigin_SteamV2_LeftStick_DPadNorth,
  k_EControllerActionOrigin_SteamV2_LeftStick_DPadSouth,
  k_EControllerActionOrigin_SteamV2_LeftStick_DPadWest,
  k_EControllerActionOrigin_SteamV2_LeftStick_DPadEast,
  k_EControllerActionOrigin_SteamV2_Gyro_Move,
  k_EControllerActionOrigin_SteamV2_Gyro_Pitch,
  k_EControllerActionOrigin_SteamV2_Gyro_Yaw,
  k_EControllerActionOrigin_SteamV2_Gyro_Roll,

  // Switch - Pro or Joycons used as a single input device.
  // This does not apply to a single joycon
  k_EControllerActionOrigin_Switch_A,
  k_EControllerActionOrigin_Switch_B,
  k_EControllerActionOrigin_Switch_X,
  k_EControllerActionOrigin_Switch_Y,
  k_EControllerActionOrigin_Switch_LeftBumper,
  k_EControllerActionOrigin_Switch_RightBumper,
  k_EControllerActionOrigin_Switch_Plus,  // Start
  k_EControllerActionOrigin_Switch_Minus, // Back
  k_EControllerActionOrigin_Switch_Capture,
  k_EControllerActionOrigin_Switch_LeftTrigger_Pull,
  k_EControllerActionOrigin_Switch_LeftTrigger_Click,
  k_EControllerActionOrigin_Switch_RightTrigger_Pull,
  k_EControllerActionOrigin_Switch_RightTrigger_Click,
  k_EControllerActionOrigin_Switch_LeftStick_Move,
  k_EControllerActionOrigin_Switch_LeftStick_Click,
  k_EControllerActionOrigin_Switch_LeftStick_DPadNorth,
  k_EControllerActionOrigin_Switch_LeftStick_DPadSouth,
  k_EControllerActionOrigin_Switch_LeftStick_DPadWest,
  k_EControllerActionOrigin_Switch_LeftStick_DPadEast,
  k_EControllerActionOrigin_Switch_RightStick_Move,
  k_EControllerActionOrigin_Switch_RightStick_Click,
  k_EControllerActionOrigin_Switch_RightStick_DPadNorth,
  k_EControllerActionOrigin_Switch_RightStick_DPadSouth,
  k_EControllerActionOrigin_Switch_RightStick_DPadWest,
  k_EControllerActionOrigin_Switch_RightStick_DPadEast,
  k_EControllerActionOrigin_Switch_DPad_North,
  k_EControllerActionOrigin_Switch_DPad_South,
  k_EControllerActionOrigin_Switch_DPad_West,
  k_EControllerActionOrigin_Switch_DPad_East,
  k_EControllerActionOrigin_Switch_ProGyro_Move,    // Primary Gyro in Pro Controller, or Right
                                                    // JoyCon
  k_EControllerActionOrigin_Switch_ProGyro_Pitch,   // Primary Gyro in Pro Controller, or Right
                                                    // JoyCon
  k_EControllerActionOrigin_Switch_ProGyro_Yaw,     // Primary Gyro in Pro Controller, or Right
                                                    // JoyCon
  k_EControllerActionOrigin_Switch_ProGyro_Roll,    // Primary Gyro in Pro Controller, or Right
                                                    // JoyCon Switch JoyCon Specific
  k_EControllerActionOrigin_Switch_RightGyro_Move,  // Right JoyCon Gyro generally should
                                                    // correspond to Pro's single gyro
  k_EControllerActionOrigin_Switch_RightGyro_Pitch, // Right JoyCon Gyro generally should
                                                    // correspond to Pro's single gyro
  k_EControllerActionOrigin_Switch_RightGyro_Yaw,   // Right JoyCon Gyro generally should
                                                    // correspond to Pro's single gyro
  k_EControllerActionOrigin_Switch_RightGyro_Roll,  // Right JoyCon Gyro generally should
                                                    // correspond to Pro's single gyro
  k_EControllerActionOrigin_Switch_LeftGyro_Move,
  k_EControllerActionOrigin_Switch_LeftGyro_Pitch,
  k_EControllerActionOrigin_Switch_LeftGyro_Yaw,
  k_EControllerActionOrigin_Switch_LeftGyro_Roll,
  k_EControllerActionOrigin_Switch_LeftGrip_Lower,  // Left JoyCon SR Button
  k_EControllerActionOrigin_Switch_LeftGrip_Upper,  // Left JoyCon SL Button
  k_EControllerActionOrigin_Switch_RightGrip_Lower, // Right JoyCon SL Button
  k_EControllerActionOrigin_Switch_RightGrip_Upper, // Right JoyCon SR Button

  // Added in SDK 1.45
  k_EControllerActionOrigin_PS4_DPad_Move,
  k_EControllerActionOrigin_XBoxOne_DPad_Move,
  k_EControllerActionOrigin_XBox360_DPad_Move,
  k_EControllerActionOrigin_Switch_DPad_Move,

  // Added in SDK 1.51
  k_EControllerActionOrigin_PS5_X,
  k_EControllerActionOrigin_PS5_Circle,
  k_EControllerActionOrigin_PS5_Triangle,
  k_EControllerActionOrigin_PS5_Square,
  k_EControllerActionOrigin_PS5_LeftBumper,
  k_EControllerActionOrigin_PS5_RightBumper,
  k_EControllerActionOrigin_PS5_Option, // Start
  k_EControllerActionOrigin_PS5_Create, // Back
  k_EControllerActionOrigin_PS5_Mute,
  k_EControllerActionOrigin_PS5_LeftPad_Touch,
  k_EControllerActionOrigin_PS5_LeftPad_Swipe,
  k_EControllerActionOrigin_PS5_LeftPad_Click,
  k_EControllerActionOrigin_PS5_LeftPad_DPadNorth,
  k_EControllerActionOrigin_PS5_LeftPad_DPadSouth,
  k_EControllerActionOrigin_PS5_LeftPad_DPadWest,
  k_EControllerActionOrigin_PS5_LeftPad_DPadEast,
  k_EControllerActionOrigin_PS5_RightPad_Touch,
  k_EControllerActionOrigin_PS5_RightPad_Swipe,
  k_EControllerActionOrigin_PS5_RightPad_Click,
  k_EControllerActionOrigin_PS5_RightPad_DPadNorth,
  k_EControllerActionOrigin_PS5_RightPad_DPadSouth,
  k_EControllerActionOrigin_PS5_RightPad_DPadWest,
  k_EControllerActionOrigin_PS5_RightPad_DPadEast,
  k_EControllerActionOrigin_PS5_CenterPad_Touch,
  k_EControllerActionOrigin_PS5_CenterPad_Swipe,
  k_EControllerActionOrigin_PS5_CenterPad_Click,
  k_EControllerActionOrigin_PS5_CenterPad_DPadNorth,
  k_EControllerActionOrigin_PS5_CenterPad_DPadSouth,
  k_EControllerActionOrigin_PS5_CenterPad_DPadWest,
  k_EControllerActionOrigin_PS5_CenterPad_DPadEast,
  k_EControllerActionOrigin_PS5_LeftTrigger_Pull,
  k_EControllerActionOrigin_PS5_LeftTrigger_Click,
  k_EControllerActionOrigin_PS5_RightTrigger_Pull,
  k_EControllerActionOrigin_PS5_RightTrigger_Click,
  k_EControllerActionOrigin_PS5_LeftStick_Move,
  k_EControllerActionOrigin_PS5_LeftStick_Click,
  k_EControllerActionOrigin_PS5_LeftStick_DPadNorth,
  k_EControllerActionOrigin_PS5_LeftStick_DPadSouth,
  k_EControllerActionOrigin_PS5_LeftStick_DPadWest,
  k_EControllerActionOrigin_PS5_LeftStick_DPadEast,
  k_EControllerActionOrigin_PS5_RightStick_Move,
  k_EControllerActionOrigin_PS5_RightStick_Click,
  k_EControllerActionOrigin_PS5_RightStick_DPadNorth,
  k_EControllerActionOrigin_PS5_RightStick_DPadSouth,
  k_EControllerActionOrigin_PS5_RightStick_DPadWest,
  k_EControllerActionOrigin_PS5_RightStick_DPadEast,
  k_EControllerActionOrigin_PS5_DPad_Move,
  k_EControllerActionOrigin_PS5_DPad_North,
  k_EControllerActionOrigin_PS5_DPad_South,
  k_EControllerActionOrigin_PS5_DPad_West,
  k_EControllerActionOrigin_PS5_DPad_East,
  k_EControllerActionOrigin_PS5_Gyro_Move,
  k_EControllerActionOrigin_PS5_Gyro_Pitch,
  k_EControllerActionOrigin_PS5_Gyro_Yaw,
  k_EControllerActionOrigin_PS5_Gyro_Roll,

  k_EControllerActionOrigin_XBoxOne_LeftGrip_Lower,
  k_EControllerActionOrigin_XBoxOne_LeftGrip_Upper,
  k_EControllerActionOrigin_XBoxOne_RightGrip_Lower,
  k_EControllerActionOrigin_XBoxOne_RightGrip_Upper,
  k_EControllerActionOrigin_XBoxOne_Share,

  // Added in SDK 1.53
  k_EControllerActionOrigin_SteamDeck_A,
  k_EControllerActionOrigin_SteamDeck_B,
  k_EControllerActionOrigin_SteamDeck_X,
  k_EControllerActionOrigin_SteamDeck_Y,
  k_EControllerActionOrigin_SteamDeck_L1,
  k_EControllerActionOrigin_SteamDeck_R1,
  k_EControllerActionOrigin_SteamDeck_Menu,
  k_EControllerActionOrigin_SteamDeck_View,
  k_EControllerActionOrigin_SteamDeck_LeftPad_Touch,
  k_EControllerActionOrigin_SteamDeck_LeftPad_Swipe,
  k_EControllerActionOrigin_SteamDeck_LeftPad_Click,
  k_EControllerActionOrigin_SteamDeck_LeftPad_DPadNorth,
  k_EControllerActionOrigin_SteamDeck_LeftPad_DPadSouth,
  k_EControllerActionOrigin_SteamDeck_LeftPad_DPadWest,
  k_EControllerActionOrigin_SteamDeck_LeftPad_DPadEast,
  k_EControllerActionOrigin_SteamDeck_RightPad_Touch,
  k_EControllerActionOrigin_SteamDeck_RightPad_Swipe,
  k_EControllerActionOrigin_SteamDeck_RightPad_Click,
  k_EControllerActionOrigin_SteamDeck_RightPad_DPadNorth,
  k_EControllerActionOrigin_SteamDeck_RightPad_DPadSouth,
  k_EControllerActionOrigin_SteamDeck_RightPad_DPadWest,
  k_EControllerActionOrigin_SteamDeck_RightPad_DPadEast,
  k_EControllerActionOrigin_SteamDeck_L2_SoftPull,
  k_EControllerActionOrigin_SteamDeck_L2,
  k_EControllerActionOrigin_SteamDeck_R2_SoftPull,
  k_EControllerActionOrigin_SteamDeck_R2,
  k_EControllerActionOrigin_SteamDeck_LeftStick_Move,
  k_EControllerActionOrigin_SteamDeck_L3,
  k_EControllerActionOrigin_SteamDeck_LeftStick_DPadNorth,
  k_EControllerActionOrigin_SteamDeck_LeftStick_DPadSouth,
  k_EControllerActionOrigin_SteamDeck_LeftStick_DPadWest,
  k_EControllerActionOrigin_SteamDeck_LeftStick_DPadEast,
  k_EControllerActionOrigin_SteamDeck_LeftStick_Touch,
  k_EControllerActionOrigin_SteamDeck_RightStick_Move,
  k_EControllerActionOrigin_SteamDeck_R3,
  k_EControllerActionOrigin_SteamDeck_RightStick_DPadNorth,
  k_EControllerActionOrigin_SteamDeck_RightStick_DPadSouth,
  k_EControllerActionOrigin_SteamDeck_RightStick_DPadWest,
  k_EControllerActionOrigin_SteamDeck_RightStick_DPadEast,
  k_EControllerActionOrigin_SteamDeck_RightStick_Touch,
  k_EControllerActionOrigin_SteamDeck_L4,
  k_EControllerActionOrigin_SteamDeck_R4,
  k_EControllerActionOrigin_SteamDeck_L5,
  k_EControllerActionOrigin_SteamDeck_R5,
  k_EControllerActionOrigin_SteamDeck_DPad_Move,
  k_EControllerActionOrigin_SteamDeck_DPad_North,
  k_EControllerActionOrigin_SteamDeck_DPad_South,
  k_EControllerActionOrigin_SteamDeck_DPad_West,
  k_EControllerActionOrigin_SteamDeck_DPad_East,
  k_EControllerActionOrigin_SteamDeck_Gyro_Move,
  k_EControllerActionOrigin_SteamDeck_Gyro_Pitch,
  k_EControllerActionOrigin_SteamDeck_Gyro_Yaw,
  k_EControllerActionOrigin_SteamDeck_Gyro_Roll,
  k_EControllerActionOrigin_SteamDeck_Reserved1,
  k_EControllerActionOrigin_SteamDeck_Reserved2,
  k_EControllerActionOrigin_SteamDeck_Reserved3,
  k_EControllerActionOrigin_SteamDeck_Reserved4,
  k_EControllerActionOrigin_SteamDeck_Reserved5,
  k_EControllerActionOrigin_SteamDeck_Reserved6,
  k_EControllerActionOrigin_SteamDeck_Reserved7,
  k_EControllerActionOrigin_SteamDeck_Reserved8,
  k_EControllerActionOrigin_SteamDeck_Reserved9,
  k_EControllerActionOrigin_SteamDeck_Reserved10,
  k_EControllerActionOrigin_SteamDeck_Reserved11,
  k_EControllerActionOrigin_SteamDeck_Reserved12,
  k_EControllerActionOrigin_SteamDeck_Reserved13,
  k_EControllerActionOrigin_SteamDeck_Reserved14,
  k_EControllerActionOrigin_SteamDeck_Reserved15,
  k_EControllerActionOrigin_SteamDeck_Reserved16,
  k_EControllerActionOrigin_SteamDeck_Reserved17,
  k_EControllerActionOrigin_SteamDeck_Reserved18,
  k_EControllerActionOrigin_SteamDeck_Reserved19,
  k_EControllerActionOrigin_SteamDeck_Reserved20,

  k_EControllerActionOrigin_Switch_JoyConButton_N, // With a Horizontal JoyCon this will be Y or
                                                   // what would be Dpad Right when vertical
  k_EControllerActionOrigin_Switch_JoyConButton_E, // X
  k_EControllerActionOrigin_Switch_JoyConButton_S, // A
  k_EControllerActionOrigin_Switch_JoyConButton_W, // B

  k_EControllerActionOrigin_PS5_LeftGrip,
  k_EControllerActionOrigin_PS5_RightGrip,
  k_EControllerActionOrigin_PS5_LeftFn,
  k_EControllerActionOrigin_PS5_RightFn,

  k_EControllerActionOrigin_Count, // If Steam has added support for new controllers origins
                                   // will go here.
  k_EControllerActionOrigin_MaximumPossibleValue =
      32767, // Origins are currently a maximum of 16 bits.
};