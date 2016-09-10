#pragma once

enum class InputEventType : int
{
	//	Input Events
	INPUT_NO_EVENT = -1,
	INPUT_KEY_PRESS = 0,
	INPUT_KEY_RELEASE = 1,
	INPUT_MOUSE_CLICK = 2,
	INPUT_MOSE_RELEASE = 3,
};

enum class InputType : int
{
	//	No Key Detected.
	KEY_UNKNOWN = -1,

	KEY_SPACE = 32,

	//	Letter Key Codes.
	KEY_A = 65,
	KEY_B =	66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,

	//	Non-Letter Key Codes.
	KEY_ESCAPE = 256,
	KEY_ENTER = 257,
	KEY_TAB = 258,
	KEY_BACKSPACE = 259,
	KEY_INSERT = 260,
	KEY_DELETE = 261,

	//	Arrow Key Codes
	KEY_RIGHT = 262,
	KEY_LEFT = 263,
	KEY_DOWN = 264,
	KEY_UP = 265
};