#pragma once

enum class ResourceEventType
{
	RESOURCE_ADDED = 0,
	RESOURCE_UPDATED = 1,
	RESOURCE_DESTROYED = 2,
};

enum class ResourceType : int
{
	//	Geometry Resource Type
	GEOMETRY_RESOURCE = 8,

	//	Light Resource Type
	LIGHT_RESOURCE = 16,

	//	Material Resource Type
	MATERIAL_RESOURCE = 32,

	//	Shader Resource Type
	SHADER_RESOURCE = 64,

	//	Texture Resource Type
	TEXTURE_RESOURCE = 128
};