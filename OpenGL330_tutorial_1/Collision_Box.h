#pragma once
#ifndef Collision_Box
#define Collision_Box_H
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm\glm.hpp"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>

class Collision_Box{
public:
	Collision_Box(GLfloat xleft, GLfloat xright, GLfloat yup, GLfloat ydown, GLfloat zin, GLfloat zout);
	void set_position(GLfloat, GLfloat, GLfloat);
	void set_offset(GLfloat, GLfloat, GLfloat);
	const enum{ NO_COLLISION, COLLISION, ONTOP, COLLBELOW, STEPUP };
	enum{ SOLID, BULLET, CAMERA };
	int check_collision(Collision_Box*);
	void rotateX(GLdouble angle);
	GLuint type = 0;
	GLfloat xPos, yPos, zPos, xLeft, xRight, yUp, yDown, zIn, zOut, width, height, depth,xOffset,yOffset,zOffset;
private:
};

#endif