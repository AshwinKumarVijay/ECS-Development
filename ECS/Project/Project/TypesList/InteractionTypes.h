#pragma once

enum class InteractionEventType : int
{
	NO_CAMERA = 10,
	NEXT_CAMERA = 11,
	PREVIOUS_CAMERA = 12,


	//	
	MOVE_FORWARD = 20,
	MOVE_BACKWARD = 21,
	MOVE_LEFT = 22,
	MOVE_RIGHT = 23,
	MOVE_UP = 24,
	MOVE_DOWN = 25,

	//	
	ROLL_RIGHT = 26,
	ROLL_LEFT = 27,
	PITCH_UP = 28,
	PITCH_DOWN = 29,
	YAW_RIGHT = 30,
	YAW_LEFT = 31



};