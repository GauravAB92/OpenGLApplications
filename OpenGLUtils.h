#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>

#include "OpenGLBase.h"

std::string readFileAsString(const std::string& path);
void compileShaderFile(GLuint shader, const std::string& filePath);
void linkShaderProgram(GLuint program);

