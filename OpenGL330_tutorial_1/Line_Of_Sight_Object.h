#pragma once
#ifndef LINE_OF_SIGHT_OBJECT_H
#define __Line_Of_Sight_Object_H__
#include "Moving_Model.h"
class Line_Of_Sight_Object : public Moving_Model{

public:
	using Moving_Model::Moving_Model;
	Line_Of_Sight_Object(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectId);

	virtual void update(void) override;
	void set_koeffs(GLfloat x, GLfloat y, GLfloat z);
	void check_los(void);
	bool get_in_sight(void);
	virtual void check_collision(void);
	void setInSight(bool insight);
protected:
	bool in_sight = false;
	GLfloat speed, xKoff, yKoff, zKoff;
};
#endif