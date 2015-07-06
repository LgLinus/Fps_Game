
#ifndef Shader_H
#define __LOAD_SHADERS_H__
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm\glm.hpp"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	Shader(const std::string& filename);
	Shader();

	void Bind();

	virtual ~Shader();
	void operator=(const Shader&other){}
	GLuint getUniformLocation(char *name);
	Shader(const Shader& other){}
	void Shader::setUniform(char* name, glm::mat4 *matrix);
	void Shader::setLighting(char* name, const glm::mat4x4 &matrix);
protected:
private:
	static const int NUM_SHADERS = 2;
	std::string LoadShader(const std::string& fileName); 
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];


};
#endif // SHADER_H