/*
* Implementation of the Shader class.
*
* Library used: GLFW3, GLAD
* @author Giulio Cattelan
*/

/*
#include "Shader.h"

#include <glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

static std::string readShaderSourceCode(const char* shaderPath);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* vertexSourceCode;
	const char* fragmentSourceCode;

	//Read source code
	try
	{
		vertexSourceCode = readShaderSourceCode(vertexPath).c_str();
		fragmentSourceCode = readShaderSourceCode(fragmentPath).c_str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		std::cerr << e.what() << std::endl;
		throw;
	}
	
	//Compilation
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSourceCode, NULL);
	glCompileShader(vertex);
	checkShaderCompilation(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSourceCode, NULL);
	glCompileShader(fragment);
	checkShaderCompilation(fragment);

	//Linking
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkShaderProgramLinking(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

unsigned int Shader::getID() const
{
	return ID;
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
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
		std::cerr << "ERROR::SHADER::" << typeName << "::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
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

void Shader::checkShaderProgramLinking(GLuint shaderProgram)
{
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl << infoLog << std::endl;
	}
}

/*
* Funzione statica per leggere i file sorgente degli shader
*/
static std::string readShaderSourceCode(const char* shaderPath)
{
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	//ensure ifstream can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open file
		shaderFile.open(shaderPath);

		//put file's content into sstreams
		shaderStream << shaderFile.rdbuf();

		//close file
		shaderFile.close();

	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER_SOURCE_CODE::PATH: " << shaderPath << std::endl;
		throw;
	}

	//return in string
	return shaderStream.str();
}
*/