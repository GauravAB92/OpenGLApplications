
#version 460 core

layout (location = 0) in vec3 worldPositions;
layout (location = 1) in vec3 vColor;

out vec4 fColor;

void main()
{
	gl_Position = vec4(worldPositions,1.0);

	fColor = vec4(vColor,1.0);
}