#version 430 core

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 256

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 v_vertexPosition;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;

//	Input the Post Process Texture.

layout (binding = 35) uniform sampler2D pp_inputTextureOne;			
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;			
layout (binding = 37) uniform sampler2D pp_inputTextureThree;		
layout (binding = 38) uniform sampler2D pp_inputTextureFour;		


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

//	Blur Direction.
uniform bool isBlurHorizontal;

//		
uniform float weights[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

//	THE VERTEX SHADER MAIN.
void main(void)
{
	

	
}