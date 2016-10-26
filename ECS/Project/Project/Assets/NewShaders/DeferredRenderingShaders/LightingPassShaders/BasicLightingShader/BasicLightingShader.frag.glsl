#version 430 core

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 256

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 v_vertexPosition;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;

//	G BUFFER TEXTURES FOR SECOND PASS OF DEFERRED RENDERING.
layout (binding = 20) uniform sampler2D g_worldSpaceVertexPosition;
layout (binding = 21) uniform sampler2D g_worldSpaceVertexNormalAndDepth;
layout (binding = 24) uniform sampler2D g_diffuseAlbedoAndLitType;
layout (binding = 25) uniform sampler2D g_specularAlbedoAndLightingType;
layout (binding = 26) uniform sampler2D g_emissionColorAndIntensity;
layout (binding = 27) uniform sampler2D g_metallicnessRoughnessFresnelOpacity;


//	Post Process Textures.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;
layout (binding = 37) uniform sampler2D pp_inputTextureThree;
layout (binding = 38) uniform sampler2D pp_inputTextureFour;

//	AMBIENT LIGHT.
uniform vec4 u_ambientLight;

//	LIGHT DESCRIPTION STRUCT.
struct Light
{
	//	Light Enabled, Locality, Light Type.
	vec4 lightEnabledShadowLightType;

	//	Vector of Options: 
	vec4 lightPosition;

	//	Vector of Options: 
	vec4 lightColorAndLightIntensity;

	//	Vector of Options: 
	vec4 lightConeDirection;

	//	Vector of Options: 
	vec4 lightAttenuationAndDistance;

	//	Vector of Options: 
	vec4 lightSpotCosCutOffAndExponent;

	//	Light Color Map.
	sampler2D mainLightColorMap;

	//	Depth Color Map.
	sampler2D mainLightDepthMap;
};


//	THE ARRAY OF LIGHTS.
uniform Light u_lights[MAX_LIGHTS];



//	SAMPLING.
//	Unit Square Samples.
uniform vec4 u_unitSquareSamples[SAMPLES];

//	Hemisphere Samples.
uniform vec4 u_hemisphereSamples[SAMPLES];

//	Screen Size.
uniform vec2 u_screenSize;

//	Radius.
uniform float u_hemisphereRadius;




//	Compute the Vertex - Light values from the textures. 
void getLightingProperties(in int lightIndex, out vec3 worldspace_vertexToEye, out vec3 worldspace_vertexToLightDirection, out vec3 worldspace_vertexNormal, out vec3 worldspace_reflectedLightDirection, out vec3 worldspace_halfVector, out vec3 lightColor, out float lightIntensity)
{
	//	Compute the World Space Vertex Position.
	vec3 worldspace_vertexPosition = (texture(g_worldSpaceVertexPosition, v_vertexPosition.xy).xyz);

	//	Compute the World Space Light Position.
	vec3 worldspace_lightPosition = u_lights[lightIndex].lightPosition.xyz / u_lights[lightIndex].lightPosition.w;

	//	Compute the Vertex to Eye Direction.
	worldspace_vertexToEye = normalize(u_worldCameraPosition.xyz - worldspace_vertexPosition);

	//	Compute the Vertex Normal.
	worldspace_vertexNormal = (texture(g_worldSpaceVertexNormalAndDepth, v_vertexPosition.xy).xyz);

	//	Compute the Vertex to Light Direction.
	worldspace_vertexToLightDirection = normalize(worldspace_lightPosition - worldspace_vertexPosition);

	//	Compute the Reflected Light Direction.
	worldspace_reflectedLightDirection = normalize(reflect(-worldspace_vertexToLightDirection, worldspace_vertexNormal));

	//	Compute the World Space Half Vector.
	worldspace_halfVector = (normalize(worldspace_vertexToLightDirection + worldspace_vertexToEye));

	//	Compute the Light Color.
	lightColor = u_lights[lightIndex].lightColorAndLightIntensity.xyz;

	//	Compute the Light Intensity.
	lightIntensity = u_lights[lightIndex].lightColorAndLightIntensity.w;	
}


//	Compute the Diffuse Lighting.
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

	vec3 diffuseAlbedo = (texture(g_diffuseAlbedoAndLitType, v_vertexPosition.xy).xyz);

	diffuseColor = diffuseAlbedo * lightColor * lightIntensity * NdotL; 
}


//	Compute the Specular Lighting.
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


//	Compute the Shaded Color from the specified Light by Index. 
void computeLighting(in int lightIndex, out vec3 shadedColor)
{
	if(u_lights[lightIndex].lightEnabledShadowLightType[0] == 1.0)
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


//	THE FRAGMENT SHADER MAIN
void main(void)
{
	//	Initialize the Total Light.
	vec3 totalLightResult = vec3(0.0, 0.0, 0.0);

	//	Iterate over the Lights.
	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		//	
		if(u_lights[i].lightEnabledShadowLightType[0] == 1.0)
		{
			//	Light Color.
			vec3 lightResult = vec3(1.0, 1.0, 1.0);

			//	Light Shadow Factor.
			vec3 lightShadowFactor = vec4(texture(u_lights[i].mainLightColorMap, v_vertexPosition.xy).xyz, 1.0).xyz;

			//	Compute the Lighting.
			computeLighting(i, lightResult);

			//	Add the Light to the Total Lighting.
			totalLightResult = totalLightResult + (lightShadowFactor * lightResult);
		}

	}

	//	Compute the Ambient Color with the SSAO texture.
	vec3 ambientColor = texture(pp_inputTextureOne, v_vertexPosition.xy).xyz;

	//	Output the Color.
	o_baseOutputColor = vec4(ambientColor + totalLightResult, 1.0);
}