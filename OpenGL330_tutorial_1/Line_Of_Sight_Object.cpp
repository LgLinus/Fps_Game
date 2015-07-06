#include "Line_Of_Sight_Object.h"
#include "Main.h"
#include "Math_Methods.h"
Line_Of_Sight_Object::Line_Of_Sight_Object(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectID)
:Moving_Model(vertices_init, uvs_init, normals_init, text, BULLET){

}

void Line_Of_Sight_Object::set_koeffs(GLfloat x, GLfloat y, GLfloat z){
	xKoff = x;
	yKoff = y;
	zKoff = z;
	speed = 0.2f;
}

void Line_Of_Sight_Object::update(){
	GLfloat xDiff = posX + getCamX();
	GLfloat zDiff = posZ + getCamZ();
	GLfloat distance = calc_distance(xDiff, 0, zDiff, 0);
	speed = 0.2f;
	xDiff *= -1; zDiff *= -1;
	GLfloat angle;
	angle = calc_angle(xDiff, 0, zDiff, 0);
	xKoff = cos(angle);
	yKoff = 0;
	zKoff = sin(angle);

	posX += speed*xKoff*get_time_update();
	posY += speed*yKoff*get_time_update();
	posZ += speed*zKoff*get_time_update();
	collisionBox->set_position(posX + getCamX(), posY + getCamY(), posZ + getCamZ());
	check_collision();
}

void Line_Of_Sight_Object::setInSight(bool insight){
	in_sight = insight;
	printf("in sight: %s", in_sight ? "true" : "false");
}

void Line_Of_Sight_Object::check_collision(){
	bool destroy = false;
	std::vector<Model*>* models = get_models();
	GLuint coll = 0, myPos = 0;
	for (int i = 0; i < models->size(); i++){
		coll = models->at(i)->check_collision(collisionBox);

		if (id != models->at(i)->id){
			if (coll == 1 || coll == 3 || coll == 2){

				if (models->at(i)->getObjectID() == models->at(i)->SOLID){
					in_sight = false;
					printf("Out of line of sight");
					speed = 0;
				}
				
				//	printf("Collision");
			}
		}
		else{
			myPos = i;
		}
	}
	if (getCameraCollisionBox()->check_collision(collisionBox)){
		printf("HIT PLAYER");
		in_sight = true;
		speed = 0;
	}
}

bool Line_Of_Sight_Object::get_in_sight(){
	return in_sight;
}
