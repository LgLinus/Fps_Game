#pragma once
#ifndef DOOR_H
#define Door_H

#include "Moving_Model.h"
#include <vector>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>
class Door : public Moving_Model{

public:
	using Moving_Model::Moving_Model;
	Door(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLint lockID);
	void open(void);
	void close(void);
	int get_state(void);
	enum { CLOSED, OPEN, LOCKED };
	void unlock(std::vector<int> keys);
protected:
	int state = CLOSED;
	int lockID = 0;
	GLfloat speed, xKoff, yKoff, zKoff;
	virtual void create_collision_box(void);
};
#endif