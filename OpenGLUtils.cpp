#include "OpenGLUtils.h"



std::string readFileAsString(const std::string& path)
{
	std::string fileline;
	std::ifstream in;
	std::stringstream ss;

	in.open(path);
	assert(!in.fail());

	while (!in.eof())
	{
		std::getline(in, fileline);

		ss << fileline << "\n";
	}

	in.close();
	return ss.str();
}

void compileShaderFile(GLuint shader, const std::string& filePath)
{
	std::string source = readFileAsString(filePath);
	const char* temp = source.c_str();

	glShaderSource(shader, 1, &temp, nullptr);
	glCompileShader(shader);

	GLint compileStatus;
	GLint infoLogLength;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE) 
	{

		std::cerr << "Unable to compile shader " << filePath << ":\n";

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::vector<char> infoLog(infoLogLength + 1);

		glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());
		infoLog[infoLogLength] = '\0';

		std::cerr << infoLog.data() << "\n";
	}

}


void linkShaderProgram(GLuint program)
{
	glLinkProgram(program);

	GLint linkStatus;
	GLint infoLogLength;

	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		std::cerr << "Unable to link program:\n";

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::vector<char> infoLog(infoLogLength + 1);

		glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());
		infoLog[infoLogLength] = '\0';

		std::cerr << infoLog.data() << "\n";
	}
}
