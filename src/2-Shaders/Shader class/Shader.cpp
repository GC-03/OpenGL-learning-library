/*
* Shader class to read, compile and link shaders.
*
* @author Giulio Cattelan
*/

#include "Shader.h"

#include <glad.h>

#include <string>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
}

unsigned int Shader::getID()
{
	return ID;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
}

void Shader::setInt(const std::string& name, int value) const
{
}

void Shader::setFloat(const std::string& name, float value) const
{
}

void Shader::checkShaderCompilation(GLuint shader)
{
	int success;
	char infoLog[512];
	int type;
	const char* typeName;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderiv(shader, GL_SHADER_TYPE, &type);
		typeName = getShaderTypeName(type);
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << typeName << "::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}
}

const char* Shader::getShaderTypeName(int type)
{
	switch (type) {
	case GL_VERTEX_SHADER:
		return "GL_VERTEX_SHADER";
	case GL_GEOMETRY_SHADER:
		return "GL_VERTEX_SHADER";
	case GL_FRAGMENT_SHADER:
		return "GL_FRAGMENT_SHADER";
	default:
		return "GL_UNKNOWN_SHADER";
	}
}

void Shader::checkShaderProgramLink(GLuint shaderProgram)
{
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl << infoLog << std::endl;
	}
}
