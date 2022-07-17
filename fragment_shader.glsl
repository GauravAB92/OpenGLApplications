
#version 460 core

in vec4 fNormals;

void main()
{
	gl_FragColor = fNormals;
}