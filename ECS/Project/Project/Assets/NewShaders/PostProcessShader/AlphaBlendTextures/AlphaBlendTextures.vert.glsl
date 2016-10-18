#version 430 core

//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) out vec4 v_vertexTextureCoordinates;

void main(void)
{
	vec4 vertexPosition[4] = vec4[4](vec4(-1.0, -1.0, 0.0, 1.0), vec4(1.0, -1.0, 0.0, 1.0), vec4(-1.0, 1.0, 0.0, 1.0), vec4(1.0, 1.0, 0.0, 1.0));
	vec2 textureCoordinates[4] = vec2[4](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

	v_vertexTextureCoordinates = vec4(textureCoordinates[gl_VertexID], 0.0, 1.0);

	gl_Position = vertexPosition[gl_VertexID];
}