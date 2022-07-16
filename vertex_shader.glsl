
#version 460 core

layout (location = 0) in vec3 worldPositions;

void main()
{
	gl_Position = vec4(worldPositions,1.0);

}