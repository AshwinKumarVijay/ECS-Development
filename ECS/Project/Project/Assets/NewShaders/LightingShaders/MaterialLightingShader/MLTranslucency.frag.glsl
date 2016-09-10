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

//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
layout (location = 25) uniform vec4 u_diffuseAlbedo;
layout (location = 26) uniform vec4 u_specularAlbedo;
layout (location = 27) uniform vec4 u_emssionColorAndIntensity;
layout (location = 28) uniform vec4 u_metallicnessRoughnessFresnelOpacity;

//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;

//	UNUSED FOR THIS SHADER.
//	layout (location = 3) in vec3 v_vertexTangent;
//	layout (location = 4) in vec3 v_vertexBitangent;

//	VERTEX TEXTURE COORDINATES ONE AND TWO.
layout (location = 5) in vec2 v_vertexTextureCoordinatesOne;
layout (location = 6) in vec2 v_vertexTextureCoordinatesTwo;


//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;


//	SAMPLING TEXTURES
//	ENVIRONMENT MAP SAMPLER CUBE.
layout (binding = 0) uniform samplerCube u_backgroundEnvironmentCubeMapOne;
layout (binding = 1) uniform samplerCube u_backgroundEnvironmentCubeMapTwo;
layout (binding = 2) uniform samplerCube u_backgroundEnvironmentCubeMapThree;
layout (binding = 3) uniform samplerCube u_backgroundEnvironmentCubeMapFour;


//	Environment Map Intensities.
uniform vec4 u_environmentMapIntensities;

//	Ambient Light.
uniform vec4 u_ambientLight;

struct Light
{
	//	Vector of Options: Light Enabled, Locality, Light Type.
	vec4 lightEnabledLocalLightType;

	//	Vector of Options: 
	vec4 lightColorAndLightIntensity;

	//	Vector of Options: 
	vec4 lightPosition;

	//	Vector of Options: 
	vec4 lightConeDirection;

	//	Vector of Options: 
	vec4 lightAttenuation;

	//	Vector of Options: 
	vec4 lightSpotCosCutOffAndExponent;
};


//	The Array of Lights.
uniform Light u_lights[MAX_LIGHTS];



//	
void getLightingProperties(in int lightIndex, out vec3 worldspace_vertexToEye, out vec3 worldspace_vertexToLightDirection, out vec3 worldspace_vertexNormal, out vec3 worldspace_reflectedLightDirection, out vec3 worldspace_halfVector, out vec3 lightColor, out float lightIntensity)
{
	vec3 worldspace_vertexPosition = (u_modelMatrix * v_vertexPosition).xyz;

	vec3 worldspace_lightPosition = u_lights[lightIndex].lightPosition.xyz / u_lights[0].lightPosition.w;

	//	
	worldspace_vertexToEye = normalize(u_worldCameraPosition.xyz - worldspace_vertexPosition);

	worldspace_vertexNormal = normalize(u_inverseTransposeModelMatrix * v_vertexNormal);

	worldspace_vertexToLightDirection = normalize(worldspace_lightPosition - worldspace_vertexPosition);

	worldspace_reflectedLightDirection = normalize(reflect(-worldspace_vertexToLightDirection, worldspace_vertexNormal));

	worldspace_halfVector = (normalize(worldspace_vertexToLightDirection + worldspace_vertexToEye));

	//	
	lightColor = u_lights[lightIndex].lightColorAndLightIntensity.xyz;

	lightIntensity = u_lights[lightIndex].lightColorAndLightIntensity.w;	
}

//	
void computeDiffuseLighting(in int lightIndex, out vec3 diffuseColor)
{
	diffuseColor = vec3(0.0, 0.0, 0.0);
	
    vec3 V = vec3(0.0, 0.0, 0.0);
	vec3 L = vec3(0.0, 0.0, 0.0);
	vec3 N = vec3(0.0, 0.0, 0.0);
	vec3 R = vec3(0.0, 0.0, 0.0);  
    vec3 H = vec3(0.0, 0.0, 0.0);

	vec3 lightColor = vec3(0.0, 0.0, 0.0);
	float lightIntensity = 0.0;

	getLightingProperties(lightIndex, V, L, N, R, H, lightColor, lightIntensity);

	float NdotL = clamp(dot(N, L), 0.0, 1.0);

	diffuseColor = u_diffuseAlbedo.xyz * lightColor * lightIntensity * NdotL; 
}


//	
void computeSpecularLighting(int lightIndex, out vec3 specularColor)
{
	specularColor = vec3(0.0, 0.0, 0.0);

    vec3 V = vec3(0.0, 0.0, 0.0);
	vec3 L = vec3(0.0, 0.0, 0.0);
	vec3 N = vec3(0.0, 0.0, 0.0);
	vec3 R = vec3(0.0, 0.0, 0.0);  
    vec3 H = vec3(0.0, 0.0, 0.0);

	vec3 lightColor = vec3(0.0, 0.0, 0.0);
	float lightIntensity = 0.0;

	getLightingProperties(lightIndex, V, L, N, R, H, lightColor, lightIntensity);
}


//	
void computeLighting(in int lightIndex, out vec3 shadedColor)
{
	if(u_lights[lightIndex].lightEnabledLocalLightType[0] == 1.0)
	{
		vec3 diffuseColor = vec3(0.0, 0.0, 0.0);
		vec3 specularColor = vec3(0.0, 0.0, 0.0);

		computeDiffuseLighting(lightIndex, diffuseColor);
		computeSpecularLighting(lightIndex, specularColor);

		shadedColor = diffuseColor + specularColor;
	}
	else
	{
		shadedColor = vec3(0.0, 0.0, 0.0);
	}
}


//	THE FRAGMENT SHADER MAIN.
void main(void)
{

	//	Initialize the Total Light.
	vec3 totalLightResult = vec3(0.0, 0.0, 0.0);

	//	Iterate over the Lights.
	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		//	Initialize the Light.
		vec3 lightResult = vec3(0.0, 0.0, 0.0);

		//	Compute the Lighting.
		computeLighting(i, lightResult);

		//	Add the Light to the Total Lighting.
		totalLightResult = totalLightResult + lightResult;
	}
	
	//	Output the Fragment Color.
	o_baseOutputColor = vec4(totalLightResult.xyz, u_diffuseAlbedo.w);
}