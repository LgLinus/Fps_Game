#pragma once
#ifndef Math_Methods
#define MATH_METHODS_H

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
GLfloat calc_angle(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2);
#endif