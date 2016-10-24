
#version 430 core


//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;


//	SAMPLING TEXTURES
//	ENVIRONMENT MAP SAMPLER CUBE.
layout (binding = 0) uniform samplerCube u_backgroundEnvironmentCubeMapOne;
layout (binding = 1) uniform samplerCube u_backgroundEnvironmentCubeMapTwo;
layout (binding = 2) uniform samplerCube u_backgroundEnvironmentCubeMapThree;
layout (binding = 3) uniform samplerCube u_backgroundEnvironmentCubeMapFour;

//	Ambient Light.
uniform vec4 u_ambientLight;

//	Environment Map Intensities.
uniform vec4 u_environmentMapIntensities;

//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	o_baseOutputColor = vec4(u_ambientLight.xyz, 1.0);
}