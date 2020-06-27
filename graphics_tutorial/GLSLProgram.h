#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribiute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();

private:

	int _numAttribiutes;

	void compileShader(const std::string& filePath, GLuint id);

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;


};

