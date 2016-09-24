#version 430 core

// CONSTANTS - PI
const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 32

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
layout (location = 20) uniform mat4 u_modelMatrix;
layout (location = 21) uniform mat3 u_inverseTransposeModelMatrix;
layout (location = 22) uniform mat4 u_modelViewMatrix;
layout (location = 23) uniform mat3 u_inverseTransposeModelViewMatrix;

//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;


//	FRAGMENT OUTPUT COLOR.
//	G BUFFER TEXTURES OUT.
layout (location = 0) out vec4 o_worldSpaceVertexPosition;
layout (location = 1) out vec4 o_worldSpaceVertexNormal;
layout (location = 2) out vec4 o_viewSpaceVertexPositionAndDepth;
layout (location = 3) out vec4 o_viewSpaceVertexNormal;
layout (location = 4) out vec4 o_diffuseAlbedo;
layout (location = 5) out vec4 o_specularAlbedo;
layout (location = 6) out vec4 o_emissionColorAndIntensity;
layout (location = 7) out vec4 o_metallicnessRoughnessFresnelOpacity;


//	SAMPLING TEXTURES
//	ENVIRONMENT MAP SAMPLER CUBE.
layout (binding = 0) uniform samplerCube u_backgroundEnvironmentCubeMapOne;
layout (binding = 1) uniform samplerCube u_backgroundEnvironmentCubeMapTwo;
layout (binding = 2) uniform samplerCube u_backgroundEnvironmentCubeMapThree;
layout (binding = 3) uniform samplerCube u_backgroundEnvironmentCubeMapFour;

//	Environment Map Intensities.
uniform vec4 u_environmentMapIntensities;

//	Linearize the Given Depth.
float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_cameraNearFarPlaneDistance.x * u_cameraNearFarPlaneDistance.y) / (u_cameraNearFarPlaneDistance.y + u_cameraNearFarPlaneDistance.x - z * (u_cameraNearFarPlaneDistance.y - u_cameraNearFarPlaneDistance.x));	
}

//	THE FRAGMENT SHADER MAIN.
void main(void)
{

	//	OUPUT WORLD SPACE VERTEX DATA.
	o_worldSpaceVertexPosition = (u_modelMatrix * v_vertexPosition);
	o_worldSpaceVertexPosition = vec4((o_worldSpaceVertexPosition.xyz / o_worldSpaceVertexPosition.w), 1.0);
	o_worldSpaceVertexNormal = vec4(normalize((u_inverseTransposeModelMatrix * v_vertexNormal)), 0.0);
	
	//	OUTPUT VIEW SPACE VERTEX DATA.
	o_viewSpaceVertexPositionAndDepth = (u_modelViewMatrix * v_vertexPosition);
	o_viewSpaceVertexPositionAndDepth = vec4(vec3(o_viewSpaceVertexPositionAndDepth.xyz / o_viewSpaceVertexPositionAndDepth.w), linearizeDepth(gl_FragCoord.z)); 
	o_viewSpaceVertexNormal = vec4(normalize(u_inverseTransposeModelViewMatrix * v_vertexNormal), 0.0);

	//	OUTPUT MATERIAL DATA.
	o_diffuseAlbedo = vec4(0.0, 0.0, 0.0, 0.0);
	o_specularAlbedo = vec4(0.0, 0.0, 0.0, 0.0);
	o_emissionColorAndIntensity = vec4(0.0, 0.0, 0.0, 0.0);
	o_metallicnessRoughnessFresnelOpacity = vec4(1.0, 1.0, 1.0, 1.0);

}