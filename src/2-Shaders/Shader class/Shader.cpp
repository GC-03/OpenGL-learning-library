/*
* Shader class to read, compile and link shaders.
*
* @author Giulio Cattelan
*/

#include "Shader.h"

#include <glad.h>

#include <string>
#include <iostream>
#include<fstream>
#include<sstream>

enum ShaderType { vertexShader, fragmentShader };
constexpr int MAX_SHADER_NUMBER = 2;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* paths[] = {vertexPath, fragmentPath};
	const char* sourceCode[MAX_SHADER_NUMBER];
	std::string stringSourceCode[MAX_SHADER_NUMBER];
	std::ifstream shaderFile[MAX_SHADER_NUMBER];

	//ensure every ifstream can throw exceptions
	for(std::ifstream& i : shaderFile)
	{
		i.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	}

	//read files and get 
	try
	{
		//open every file
		for (int i = 0; i < MAX_SHADER_NUMBER; i++) { shaderFile[i].open(paths[i]); }
		
		//put every file's content into sstreams and convert them into string
		std::stringstream shaderStream[MAX_SHADER_NUMBER];

		for (int i = 0; i < MAX_SHADER_NUMBER; i++)
		{
			shaderStream[i] << shaderFile[i].rdbuf();
			stringSourceCode[i] = shaderStream[i].str();
			sourceCode[i] = stringSourceCode[i].c_str();
		}
		
		//close every file
		for (std::ifstream& i : shaderFile) { i.close(); }
		
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	//convert into const char*
	for (int i = 0; i < MAX_SHADER_NUMBER; i++)
	{
		sourceCode[i] = stringSourceCode[i].c_str();
	}
	
	//Compilation
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &sourceCode[ShaderType::vertexShader], NULL);
	glCompileShader(vertex);
	checkShaderCompilation(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &sourceCode[ShaderType::fragmentShader], NULL);
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

void Shader::checkShaderProgramLinking(GLuint shaderProgram)
{
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl << infoLog << std::endl;
	}
}
