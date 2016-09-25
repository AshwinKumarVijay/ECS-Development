#version 430 core

// CONSTANTS - PI
const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

//	MAX LIGHTS
#define MAX_LIGHTS 16

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;


//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) in vec4 v_vertexTextureCoordinates;

//	FRAGMENT OUTPUT COLOR.
layout (location = 0) out vec4 o_baseOutputColor;



//	SAMPLING TEXTURES
//	ENVIRONMENT MAP SAMPLER CUBE.
layout (binding = 0) uniform samplerCube u_backgroundEnvironmentCubeMapOne;
layout (binding = 1) uniform samplerCube u_backgroundEnvironmentCubeMapTwo;
layout (binding = 2) uniform samplerCube u_backgroundEnvironmentCubeMapThree;
layout (binding = 3) uniform samplerCube u_backgroundEnvironmentCubeMapFour;


//	G BUFFER TEXTURES FOR SECOND PASS OF DEFERRED RENDERING.
layout (binding = 20) uniform sampler2D g_worldSpaceVertexPosition;
layout (binding = 21) uniform sampler2D g_worldSpaceVertexNormal;
layout (binding = 22) uniform sampler2D g_viewSpaceVertexPositionAndDepth;
layout (binding = 23) uniform sampler2D g_viewSpaceVertexNormal;
layout (binding = 24) uniform sampler2D g_diffuseAlbedo;
layout (binding = 25) uniform sampler2D g_specularAlbedo;
layout (binding = 26) uniform sampler2D g_emissionColorAndIntensity;
layout (binding = 27) uniform sampler2D g_metallicnessRoughnessFresnelOpacity;



//	Environment Map Intensities.
uniform vec4 u_backgroundEnvironmentIntensities;


//	AMBIENT LIGHT.
uniform vec4 u_ambientLight;

//	LIGHT DESCRIPTION STRUCT.
struct Light
{
	//	Vector of Options: Light Enabled, Locality, Light Type.
	vec4 lightEnabledShadowLightType;

	//	Vector of Options: 
	vec4 lightColorAndLightIntensity;

	//	Vector of Options: 
	vec4 lightPosition;

	//	Vector of Options: 
	vec4 lightConeDirection;

	//	Vector of Options: 
	vec4 lightAttenuationAndDistance;

	//	Vector of Options: 
	vec4 lightSpotCosCutOffAndExponent;

	//	Directional Light Depth Map.
	sampler2D lightDepthMap;
	
	//	Omnidirectional Light Depth Map.
	samplerCube pointLightDepthMap;
};


//	THE ARRAY OF LIGHTS.
uniform Light u_lights[MAX_LIGHTS];




//	
void getLightingProperties(in int lightIndex, out vec3 worldspace_vertexToEye, out vec3 worldspace_vertexToLightDirection, out vec3 worldspace_vertexNormal, out vec3 worldspace_reflectedLightDirection, out vec3 worldspace_halfVector, out vec3 lightColor, out float lightIntensity)
{
	vec3 worldspace_vertexPosition = texture(g_worldSpaceVertexPosition, v_vertexTextureCoordinates.xy).xyz;

	vec3 worldspace_lightPosition = u_lights[lightIndex].lightPosition.xyz / u_lights[lightIndex].lightPosition.w;


	//	
	worldspace_vertexToEye = normalize(u_worldCameraPosition.xyz - worldspace_vertexPosition);

	worldspace_vertexNormal = normalize(texture(g_worldSpaceVertexNormal, v_vertexTextureCoordinates.xy).xyz);


	worldspace_vertexToLightDirection = normalize(worldspace_lightPosition - worldspace_vertexPosition);

	worldspace_reflectedLightDirection = normalize(reflect(-worldspace_vertexToLightDirection, worldspace_vertexNormal));

	worldspace_halfVector = (normalize(worldspace_vertexToLightDirection + worldspace_vertexToEye));

	//	
	lightColor = u_lights[lightIndex].lightColorAndLightIntensity.xyz;

	lightIntensity = u_lights[lightIndex].lightColorAndLightIntensity.w;	
}

float computeShadowingFactor(in int lightIndex)
{
	vec3 worldspace_vertexPosition = texture(g_worldSpaceVertexPosition, v_vertexTextureCoordinates.xy).xyz;

	vec3 worldspace_lightPosition = u_lights[lightIndex].lightPosition.xyz / u_lights[lightIndex].lightPosition.w;

	vec3 vertexToLight = worldspace_vertexPosition - worldspace_lightPosition;

	float closestDepth = texture(u_lights[lightIndex].pointLightDepthMap, vertexToLight).r;

	closestDepth = closestDepth * u_cameraNearFarPlaneDistance[1];

	float currentDepth = length(vertexToLight);

	float bias = 0.05;

	float shadowingFactor = currentDepth - (bias > closestDepth ? 1.0 : 0.0);
	
	return shadowingFactor;
}


//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Initialize the Total Light.
	vec3 totalLightResult = vec3(0.0, 0.0, 0.0);
	
	//	Compute the Shadowing Factor.
	float shadowingFactor = computeShadowingFactor(0);

	//	Output the Fragment Color.
	o_baseOutputColor = vec4(shadowingFactor, shadowingFactor, shadowingFactor, 1.0);

}