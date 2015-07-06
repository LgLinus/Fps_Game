#include "Collision_Box.h"
#include <iostream>
#include "Main.h"
Collision_Box::Collision_Box(GLfloat xleft, GLfloat xright, GLfloat yup, GLfloat ydown, GLfloat zin, GLfloat zout){
	xLeft = xleft;
	xRight = xright;
	yUp= yup;
	yDown = ydown;
	zIn = zin;
	zOut = zout;
	width = abs(xLeft - xRight);
	height = abs(yUp - yDown);
	depth = abs(zIn - zOut);
	xPos = 0; 
	yPos = 0;
	zPos = 0;
	xOffset = 0;
	yOffset = 0;
	zOffset = 0;
}

void Collision_Box::set_position(GLfloat x, GLfloat y, GLfloat z){
	xPos = x + xOffset;
	yPos = y + yOffset;
	zPos = z + zOffset;
}

void Collision_Box::set_offset(GLfloat x, GLfloat y, GLfloat z){
	xOffset = x;
	yOffset = y;
	zOffset = z;
}
int Collision_Box::check_collision(Collision_Box* otherBox){
	if (type == BULLET && otherBox->type == CAMERA || type == CAMERA && otherBox->type == BULLET){
		return 0;
	}
	if (-(width / 2) + xPos< otherBox->xPos + (otherBox->width / 2)
		&& xPos + (width / 2) > otherBox->xPos - (otherBox->width / 2)
		&& -(depth / 2) + zPos < otherBox->zPos + (otherBox->depth / 2)
		&& zPos + (depth / 2) > otherBox->zPos - (otherBox->depth / 2)){
		
		if (yPos + 1 + height / 2 < otherBox->yPos - otherBox->height / 2){

			if (abs((yPos + 1 + height / 2) - (otherBox->yPos - otherBox->height / 2))< 0.6)
				return ONTOP;
			else
				return NO_COLLISION;
		}
		else if (yPos - height / 2 > otherBox->yPos + otherBox->height / 2){
			if (abs((yPos - height / 2) - (otherBox->yPos + otherBox->height / 2)) <0.6){
				return COLLBELOW;
			}
			else
			return NO_COLLISION;
		}
		else{

			return COLLISION;
		}
	}
	/*if (xPos - abs(xLeft)< otherBox->xPos - abs((otherBox->xRight))
		&& xPos + abs(xRight) > otherBox->xPos + abs(otherBox->xLeft)
		&& -abs(zIn) + zPos < otherBox->zPos - abs((otherBox->zOut))
		&& zPos + abs(zOut) > otherBox->zPos + abs(otherBox->zIn))
		{
		printf("WOOP");
		return COLLISION;
		if (yPos + 1 + yUp < otherBox->yPos - otherBox->yDown){

			if (abs((yPos + 1 + yDown) - (otherBox->yPos - otherBox->yUp))< 0.2)
				return ONTOP;
			else
				return NO_COLLISION;
		}
		else if (yPos - yUp > otherBox->yPos + otherBox->yDown){
			if (abs((yPos - yUp) - (otherBox->yPos + otherBox->yDown)) <0.4){
				printf("COLLBELOW\n");
				return COLLBELOW;
			}
			else
				return NO_COLLISION;
		}
		else{

			printf("collision\n");
			return COLLISION;
		}
	}*/
	return 0;
}

void Collision_Box::rotateX(GLdouble angle){

	GLfloat tempXLeft, tempXRight, tempZOut, tempZIn;

	tempXLeft = xLeft*cos(angle) + sin(angle)*zIn;
	tempXRight = xRight*cos(angle) + sin(angle)*zOut;

	tempZOut = xRight*(-sin(angle)) + cos(angle)*zOut;
	tempZIn = xLeft*(-sin(angle)) + cos(angle)*zIn;

	xLeft = tempXLeft;
	xRight = tempXRight;
	zOut = tempZOut;
	zIn = tempZIn;
	width = abs(xLeft - xRight);
	depth = abs(zIn - zOut);
	printf("\n\n\n xLeft %f, xRight %f, zOut %f, Zin %f \n\n\n",xLeft,xRight,zOut,zIn);
}