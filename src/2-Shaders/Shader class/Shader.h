/*
* Shader class to read, compile and link shaders.
* 
* @author Giulio Cattelan
*/
#ifndef SHADER_H
#define SHADER_H

#include <glad.h>

#include <string>

class Shader
{
public:

	//Shader constructor
	Shader(const char* vertexPath, const char*  fragmentPath);

	//ID getter
	unsigned int getID() const;

	//Use the shader
	void use() const;

	//Uniform setters
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:

	//Shader program ID
	unsigned int ID;

	void checkShaderCompilation(GLuint shader);
	const char* getShaderTypeName(int type);
	void checkShaderProgramLinking(GLuint shaderProgram);
};

#endif // !SHADER_H
