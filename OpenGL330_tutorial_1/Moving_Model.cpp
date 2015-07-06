
#include "Moving_Model.h"
#include "Main.h"

Moving_Model::Moving_Model(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text,GLuint objectID)
:Model(vertices_init, uvs_init, normals_init,text,objectID){

}


void Moving_Model::set_speed(GLfloat setSpeed){
	speed = setSpeed;
}

void Moving_Model::set_direction_koefficents(GLfloat x, GLfloat y, GLfloat z){
	xKoff = x; 
	yKoff = y;
	zKoff = z;
}

void Moving_Model::update(){
	posX += speed*xKoff*get_time_update();
	posY += speed*yKoff*get_time_update();
	posZ += speed*zKoff*get_time_update();
	collisionBox->set_position(posX + getCamX(), posY + getCamY(), posZ + getCamZ());
	check_collision();
}

void Moving_Model::check_collision(){
	bool destroy = false;
	std::vector<Model*>* models = get_models();
	GLuint coll = 0, myPos=0;
	for (int i = 0; i < models->size(); i++){
		coll = models->at(i)->check_collision(collisionBox);

		if (id != models->at(i)->id){
			if (coll == 1 || coll == 3 || coll == 2){
				speed = 0;
				if (models->at(i)->getObjectID() == models->at(i)->GHOST){
					printf("KILL GHOST");
					removeFromMovingModels(get_moving_models(), models->at(i)->id);
					models->erase(models->begin() + i);
					removeFromModels(models);
					removeFromMovingModels(get_moving_models(),id);
				}
				else if (models->at(i)->getObjectID() == models->at(i)->SOLID){
					removeFromModels(models);
					removeFromMovingModels(get_moving_models(),id);
				}
			//	printf("Collision");
			}
		}
		else{
			myPos = i;
		}
	}

	//printf("MYPOS %d", myPos);
	/*if ((myPos!= 0 && (abs(posX - getCamX()) >= 20 || abs(posY - getCamY()) >= 20 || abs(posZ - getCamZ()) >= 20))){
		removeFromModels(models);
		
	}*/
}

void Moving_Model::removeFromMovingModels(std::vector<Moving_Model*>* models, GLuint id){
	bool destroy = false;
	GLuint coll = 0, myPos = -1;
	for (int i = 0; i < models->size(); i++){
		if (id == models->at(i)->id)
			myPos = i;
	}
	printf("Remove");
	if (myPos != -1)
		models->erase(models->begin() + myPos);
}