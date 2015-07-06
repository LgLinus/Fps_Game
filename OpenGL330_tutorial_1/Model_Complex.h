#pragma once
#ifndef MOVING_MODEL_H
#define __Model_Complex_H__
#include "Model.h"
class Model_Complex : public Model{

public:
	using Model::Model;
	using Model::draw;
	virtual void draw() override;
	Model_Complex(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectId);
	
	void add_collision_box(GLfloat xLeft, GLfloat xRight, GLfloat yUp, GLfloat yDown, GLfloat zIn, GLfloat zOut);
	void Model_Complex::add_collision_box(Collision_Box* box);
	virtual int check_collision(Collision_Box*) override;
private:
	std::vector<Collision_Box*> collision_boxes;
	void update_collision_boxes_position(void);
	GLfloat speed, xKoff, yKoff, zKoff;
};
#endif