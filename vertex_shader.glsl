
#version 460 core

layout (location = 0) in vec3 worldPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 uv;

out vec4 fNormals;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;


void main()
{
	vec4 transformedPos = perspectiveMatrix * viewMatrix *modelMatrix* vec4(worldPos,1.0f);

	gl_Position = transformedPos;

	//Invert ?
	fNormals = vec4(normals,1.0);

}