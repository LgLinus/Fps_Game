#include "Texture.h"
#include "stb_image.h"
#include <iostream>
Texture::Texture(const std::string& filename){
	int width, height, numComponents;
	unsigned char*  imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		printf("Texture loading failed for %s\n", filename);
	glGenTextures(1, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);

	/* Allows you to read the texture outside of it's size. Exa,ple if size is 512x512, 513x512 will be read as 1x512*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/* Allows you to rezise the texture if it's needed. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Level is mipmapping, using different resolutions for different distances. */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture(){
	glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned int unit){
	glActiveTexture(GL_TEXTURE + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}