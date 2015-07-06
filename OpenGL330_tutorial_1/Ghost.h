#pragma once
#ifndef GHOST_H
#define _GHOSTl_H__
#include "Moving_Model.h"
#include "Line_Of_Sight_Object.h"
class Ghost : public Moving_Model{

public:
	using Moving_Model::Moving_Model;
	Ghost(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text);
	virtual void update(void) override;
private:
	GLfloat active_distance = 45.0f;
	GLfloat maxspeed = 0.005f * 2;	
	Line_Of_Sight_Object* los_object;
	int counter = 120*4;
	bool in_sight = false;
};
#endif