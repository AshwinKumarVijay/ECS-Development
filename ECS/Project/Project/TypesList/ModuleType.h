#pragma once

//	Module Types
enum class ModuleType : long int
{
	//	
	NO_MODULE = 0,

	//	The Global Event Signature.
	GLOBAL = 1,

	//	The Entity Manager Signature.
	ENTITY_MANAGER = 2,

	//	The Input Manager Signature.
	INPUT_MANAGER = 3,

	//	The Material Manager Signature.
	MATERIAL_MANAGER = 4,

	//	The Geometry Manager Signature.
	GEOMETRY_MANAGER = 5,

	//	The Light Manager Signature.
	LIGHT_MANAGER = 6,

	//	The Texture Manager Signature.
	TEXTURE_MANAGER = 7,

	//	The Shader Manager Signature.
	SHADER_MANAGER = 8,

	//	The Hierarchy System Signature.
	HIERARCHY_SYSTEM = 9,

	//	The Transform System Signature.
	TRANSFORM_SYSTEM = 10,

	//	The Rendering System Signature.
	RENDERING_SYSTEM = 11,

	//	The Physics System Signature.
	PHYSICS_SYSTEM = 12,

	//	The Debug System Signature.
	DEBUG_SYSTEM = 13,

	//	The Camera System Signature.
	CAMERA_SYSTEM = 14,

	//	The Interaction Generation System Signature.
	INPUT_SYSTEM = 15,

	//	The Movement System Signature.
	MOVEMENT_SYSTEM = 16,

	//	The Interaction Movement Response System.
	INTERACTION_MOVEMENT_RESPONSE_SYSTEM = 18,

	//	The Planet Maker System.
	PLANET_MAKER_SYSTEM = 19

};