
#ifndef Main_H
#define __Main_H__
#include "glm\glm.hpp"
#include <iostream>
#include <vector>
#include "Moving_Model.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Line_of_Sight_Object.h"
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
void rotate(double angle, int axis);
void translate(float x, float y, float z);
void set_color_main(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void send_model_matrix(void);
void send_model_matrix(glm::mat4);
void set_color(const glm::vec4&);
Collision_Box* getCameraCollisionBox(void);
Line_Of_Sight_Object* create_los_object(bool in_sight);
Texture** get_textures(void);
std::vector<Model*>* get_models(void);
std::vector<Moving_Model*>* get_moving_models(void);
int get_time_update(void);
void uniform_set_ambient(GLfloat ambient);
Shader* getShader(void);

enum Textures{ BRICKS, SHOTGUN, GROUND, GHOST, AK47, SIGN, TOWER, LADDER, DOOR, TEXTURE_SIZE };
extern Texture *textures[TEXTURE_SIZE];

GLfloat getCameradirectionXY();
GLfloat getCameradirectionZY();
GLfloat getCamX();
GLfloat getCamY();
GLfloat getCamZ();

glm::mat4 getProjectionMatrix(void);
glm::mat4* getModelMatrix(void);
glm::mat4 getviewMatrix(void);
/* use conditional compilation to disable definitions when necessary */



enum move { MOVE_IGNORE_ZERO, MOVE_RELATIVE, MOVE_TO };

#endif // SHADER_H