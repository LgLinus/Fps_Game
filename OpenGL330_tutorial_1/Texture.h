#ifndef TEXTURE_H
#define TEXTURE_H
#include "Dependencies\glew\glew.h"
#include <string>

class Texture{
public:
	Texture(const std::string& filename);
	virtual ~Texture();
	void Texture::bind(unsigned int unit);
	Texture(const Texture& other);
protected:
private:

	void operator=(const Texture&other){}
	GLuint m_texture;
};


#endif