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

//	Input the Post Process Texture.

layout (binding = 35) uniform sampler2D pp_inputTextureOne;			//	World Vertex Position.
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;			//	World Space Vertex Normal.
layout (binding = 37) uniform sampler2D pp_inputTextureThree;		//	View Space Vertex Position and Depth.
layout (binding = 38) uniform sampler2D pp_inputTextureFour;		//	View Space Vertex Normal.

//	Input the Noise Textures.
layout (binding = 45) uniform sampler2D t_noiseTextureOne;
layout (binding = 46) uniform sampler2D t_noiseTextureTwo;
layout (binding = 47) uniform sampler2D t_noiseTextureThree;
layout (binding = 48) uniform sampler2D t_noiseTextureFour;

//	SAMPLING.
//	Unit Square Samples.
uniform vec4 u_unitSquareSamples[SAMPLES];

//	Hemisphere Samples.
uniform vec4 u_hemisphereSamples[SAMPLES];

//	Screen Size.
uniform vec2 u_screenSize;

//	Radius.
uniform float u_hemisphereRadius;


//	Linearize the Given Depth.
float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_cameraNearFarPlaneDistance.x * u_cameraNearFarPlaneDistance.y) / (u_cameraNearFarPlaneDistance.y + u_cameraNearFarPlaneDistance.x - z * (u_cameraNearFarPlaneDistance.y - u_cameraNearFarPlaneDistance.x));	
}


//	THE VERTEX SHADER MAIN.
void main(void)
{
	//	The Noise Scale.
	vec2 noiseScale = vec2(u_screenSize.x / 4.0f, u_screenSize.y / 4.0f);

	//	World Space Vertex Position and Normal.
	vec4 worldSpaceVertexPosition = vec4(texture(pp_inputTextureOne, v_vertexPosition.xy).xyz, 1.0);
	vec3 worldSpaceVertexNormal = normalize(texture(pp_inputTextureTwo, v_vertexPosition.xy).xyz);

	//	View Space Vetex Position and Normal.
	vec4 viewSpaceVertexPositionAndDepth = texture(pp_inputTextureThree, v_vertexPosition.xy);
	vec3 viewSpaceVertexNormal = normalize((texture(pp_inputTextureFour, v_vertexPosition.xy).xyz));


	vec3 randomVector = normalize(((texture(t_noiseTextureOne, v_vertexPosition.xy * noiseScale).xyz)));

	vec3 tangent = normalize(randomVector - (viewSpaceVertexNormal * dot(randomVector, viewSpaceVertexNormal)));
	vec3 bitangent = cross(viewSpaceVertexNormal, tangent);
	mat3 TBN = mat3(tangent, bitangent, viewSpaceVertexNormal);

	float occlusion = 0.0;

	for(int i = 0; i < SAMPLES; i++)
	{
		vec3 samplePoint = (TBN * (u_hemisphereSamples[i].xyz));
		samplePoint = (samplePoint * u_hemisphereRadius) + viewSpaceVertexPositionAndDepth.xyz;
		
		vec4 offset = vec4(samplePoint, 1.0);
		offset = u_cameraPerspectiveMatrix * offset;
		offset.xyz  = offset.xyz / offset.w;
		offset.xyz = (offset.xyz * 0.5) + 0.5;	

		float sampleDepth = -texture(pp_inputTextureThree, offset.xy).w;

		float rangeCheck = smoothstep(0.0, 1.0, u_hemisphereRadius / abs(samplePoint.z - sampleDepth));
		occlusion += (sampleDepth >= samplePoint.z ? 1.0 : 0.0) * rangeCheck;

	}

	occlusion =	1.0 - (occlusion / (float(SAMPLES)));
	
	//	OUTPUT COLOR
	o_baseOutputColor = vec4(occlusion, occlusion, occlusion, 1.0);
	
}