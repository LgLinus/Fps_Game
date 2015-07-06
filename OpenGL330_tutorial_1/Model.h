
#ifndef Model_H
#define Model_H
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm\glm.hpp"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "vector"
#include "Model_Skeleton.h"
#include "Texture.h"
class Model : public Model_Skeleton{
public:

	Model(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectID = NONE);
		//Model(std::vector<glm::vec3> vertices_init, GLubyte *elements_init, std::vector<glm::vec3> normals_init, std::vector<glm::vec2> uv_init, GLuint indices_ammount,
		//	GLuint numvertexes_init, GLuint numnormals_init, Texture *text, GLenum drawMode_init, bool center);
	

	//void operator=(const Model&other){}
	//Model(const Model& other){}
	enum { NONE,SOLID, BULLET, GHOST, TUNNEL, LADDER , DOOR};
	virtual void draw() override;
	void rotateX(GLdouble);
	void move(GLfloat x, GLfloat y, GLfloat z, enum move moveType);
	void setHUD(bool is_HUD);
	void setScale(GLfloat scale_x,GLfloat scale_y,GLfloat scale_z);
	void set_ignore_collision(bool);
	void set_collision_dimensions(GLfloat width, GLfloat height, GLfloat depth);
	virtual int check_collision(Collision_Box*) override;
	virtual void update(void) override;
	void removeFromList(void);
	GLfloat get_pos_x();
	GLfloat get_pos_y();
	GLfloat get_pos_z();
	GLuint id;
	void setAmbient(GLfloat ambient);
	virtual void move_collision_box();
	void removeFromModels(std::vector<Model*>* models);
	GLuint getObjectID(void);
	Collision_Box* get_collision_box(void);
protected:
	Collision_Box* collisionBox;
	const enum { VERTEXES, UVS, NORMALS, BUFFER_SIZE };
	void calculateMidPoint();
	void reform_texture(void);
	bool ignoreCollision;
	void setMidPoint(GLfloat x, GLfloat y, GLfloat z);
	GLuint voab[1];
	GLfloat ambient;
	GLuint buffers[BUFFER_SIZE];
	GLuint objectID = NONE;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	GLfloat centerX,centerY,centerZ;
	GLdouble angleX,angleY,angleZ;
	GLfloat posX, posY, posZ,scaleX,scaleY,scaleZ;
	glm::vec4* color;
	GLfloat dX, dY,dZ;
	GLenum drawMode;
	virtual void create_collision_box(void);
	Texture *texture;
	bool ISHUD;

private:
	void init_buffers(void);
};
#endif