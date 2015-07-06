#include "Math_Methods.h"
#include <iostream>
GLfloat calc_angle(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2){

	GLfloat angle = atan2f(y1 - y2, x1 - x2);

	return angle;
}


GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2){
	GLfloat distance = 0;
	GLfloat xDiff = x1 - x2;
	GLfloat yDiff = y1 - y2;

	distance = sqrt((pow(xDiff, 2) + pow(yDiff, 2)));

	return distance;
}

GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2){
	GLfloat distance = 0;
	GLfloat xDiff = x1 - x2;
	GLfloat yDiff = y1 - y2;
	GLfloat zDiff = z1 - z2;

	distance = sqrt((pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff,2)));

	return distance;
}