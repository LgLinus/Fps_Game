
#include "Model_Complex.h"
#include "Main.h"

Model_Complex::Model_Complex(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectId)
:Model(vertices_init, uvs_init, normals_init, text, objectId){

}



int Model_Complex::check_collision(Collision_Box* otherBox){
	
	int collision = 0;
	for (int i = 0; i < collision_boxes.size(); i++){
		if (!ignoreCollision){
			collision = collision_boxes.at(i)->check_collision(otherBox);
			if (collision == collision_boxes.at(i)->COLLISION)
				return collision;

		}
	}
	return collision;
}

/**
Draws the model with the given settings.
*/
void Model_Complex::draw(){
	Model::draw();
	update_collision_boxes_position();
}
/**
	Add new collision box
*/
void Model_Complex::add_collision_box(GLfloat xLeft, GLfloat xRight, GLfloat yUp, GLfloat yDown, GLfloat zIn, GLfloat zOut){
	Collision_Box* box = new  Collision_Box(xLeft, xRight, yUp, yDown, zIn, zOut);
	collision_boxes.insert(collision_boxes.end(), box);
}

void Model_Complex::add_collision_box(Collision_Box* box){
	collision_boxes.insert(collision_boxes.end(), box);
}

void Model_Complex::update_collision_boxes_position(){
	for (int i = 0; i < collision_boxes.size(); i++){
		collision_boxes.at(i)->set_position(posX + getCamX(), posY + getCamY(), posZ+ getCamZ());
	}
}
