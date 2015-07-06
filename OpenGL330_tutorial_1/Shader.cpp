//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.cxx ---
//
//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Shader.h"


Shader::Shader(){

}

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram(); // Create program with an ID

	/* Create vertex shader, file extension vs*/
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);

	/* Create fragment shader(color), file extension fs*/
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	/* Link program display error if it occurs*/
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR: Linking failed");

	/* Validate program display error if it occurs */
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR: Program is invalid");

}

Shader::~Shader(){

	/* Detach and delete the shaders*/
	for (int i = 0; i < NUM_SHADERS; i++){
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	/* Delete the program */
	glDeleteProgram(m_program);
}

void Shader::Bind(){
	glUseProgram(m_program);
}

/* Create shader*/
GLuint Shader::CreateShader(const std::string& text, unsigned int shaderType){

	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader c reation failed" << std::endl;
	
	const GLchar* p[1];
	GLint lengths[1];
	p[0] = text.c_str();
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	/* Compile the shader */
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: Compilation failed");

	return shader;

}

std::string  Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void  Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
GLuint Shader::getUniformLocation(char* name){
	GLuint res = glGetUniformLocation(m_program, name);
	if (res != -1)
		return res;
	else{
	// 	printf("Error retrieving location : %s", name);
		return res;
	}
}

void Shader::setUniform(char* name, glm::mat4 *matrix){
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(*matrix));
}

void Shader::setLighting(char* name,const glm::mat4x4 &matrix){
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
