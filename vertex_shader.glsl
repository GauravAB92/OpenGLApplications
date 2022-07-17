
#version 460 core

layout (location = 0) in vec3 worldPos;
layout (location = 1) in vec3 vColor;

out vec4 fColor;

uniform mat4 rotationMatrix;


void main()
{
	vec4 transformedPos = rotationMatrix * vec4(worldPos,1.0f);

	gl_Position = transformedPos;

	fColor = vec4(vColor,1.0);
}