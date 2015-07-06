#pragma once
#ifndef MOVING_MODEL_H
#define __Moving_Model_H__
#include "Model.h"
class Moving_Model : public Model{

public:
	using Model::Model;
	Moving_Model(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text , GLuint objectId);
	void set_speed(GLfloat);
	void set_direction_koefficents(GLfloat koffX, GLfloat koffY, GLfloat koffZ);
	void Moving_Model::removeFromMovingModels(std::vector<Moving_Model*>* models, GLuint id);

	void Moving_Model::update(void);
	void Moving_Model::check_collision(void);
protected:

	GLfloat speed, xKoff, yKoff, zKoff;
};
#endif