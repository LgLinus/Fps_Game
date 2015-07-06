/**

main.cpp
Purpose: Door that the player can open, close and unlock
@author Linus Granathz
@version 1.0 15/07-02
*/
#include "Moving_Model.h"
#include "Door.h"
Door::Door(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLint lockID)
:Moving_Model(vertices_init, uvs_init, normals_init, text, DOOR){
	this->lockID = lockID;

	if (this->lockID == 0)
		state = CLOSED;
	else if (this->lockID == -1)
		open();
	else
		state = LOCKED;

	printf("\n state %d\nlockID %d : \n", state,lockID);
	create_collision_box();
}

void Door::open(){
	state = OPEN;
	ignoreCollision = true;
	printf("OPEN");
	rotateX(angleX + (3.14 / 2));

}


void Door::create_collision_box(void){
	GLfloat lowX, lowY, lowZ, highX, highY, highZ;
	lowX = vertices[0][0];
	highX = vertices[0][0];
	lowY = vertices[0][1];
	highY = vertices[0][1];
	lowZ = vertices[0][2];
	highZ = vertices[0][2];

	/* Find lowest and highest values*/
	for (int i = 0; i < vertices.size(); i++){

		// Lowest, highest X value
		if (vertices[i][0] < lowX)
			lowX = vertices[i][0];
		if (vertices[i][0] > highX)
			highX = vertices[i][0];

		// Lowest, highest Y value
		if (vertices[i][1] < lowY)
			lowY = vertices[i][1];
		if (vertices[i][1] > highY)
			highY = vertices[i][1];

		// Lowest, highest Z value
		if (vertices[i][2] < lowZ)
			lowZ = vertices[i][2];
		if (vertices[i][2] > highZ)
			highZ = vertices[i][2];
	}
	lowX *= scaleX *1.5;
	highX *= scaleX * 1.5;
	lowY *= scaleY;
	highY *= scaleY;
	lowZ *= scaleZ* 1.5;
	highZ *= scaleZ* 1.5;
	collisionBox = new Collision_Box(lowX, highX, lowY, highY, lowZ, highZ);
}

void Door::unlock(std::vector<int> keys){
	if (state == CLOSED){
		open();
		return;
	}
	for (int i = 0; i < keys.size();i++){
		printf("KEY VALUE %d \n", keys.at(i));
		if (keys.at(i) == lockID){
			open();
			break;
		}
	}
}

void Door::close(){
	state = CLOSED;
	ignoreCollision = false;
	printf("CLOSE");
	rotateX(angleX - (3.14 / 2));
}

int Door::get_state(){
	return state;
}