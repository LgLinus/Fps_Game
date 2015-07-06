#pragma once
#ifndef MODELS_INFO_H
#define Models_Info_H
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
using namespace std;

/*****************************************/
extern vector< glm::vec3 > ghost_vertices;
extern vector< glm::vec2 > ghost_uvs;
extern vector< glm::vec3 > ghost_normals;

extern vector< glm::vec3 > ak47_vertices;
extern vector< glm::vec2 > ak47_uvs;
extern vector< glm::vec3 > ak47_normals;

extern vector< glm::vec3 > block_vertices;
extern vector< glm::vec2 > block_uvs;
extern vector< glm::vec3 > block_normals;

extern vector< glm::vec3 > ground_vertices;
extern vector< glm::vec2 > ground_uvs;
extern vector< glm::vec3 > ground_normals;

extern vector< glm::vec3 > tunnel_vertices;
extern vector< glm::vec2 > tunnel_uvs;
extern vector< glm::vec3 > tunnel_normals;

extern vector< glm::vec3 > sign_vertices;
extern vector< glm::vec2 > sign_uvs;
extern vector< glm::vec3 > sign_normals;

extern vector< glm::vec3 > tower_vertices;
extern vector< glm::vec2 > tower_uvs;
extern vector< glm::vec3 > tower_normals;

extern vector< glm::vec3 > wall_vertices;
extern vector< glm::vec2 > wall_uvs;
extern vector< glm::vec3 > wall_normals;

extern vector< glm::vec3 > ladder_vertices;
extern vector< glm::vec2 > ladder_uvs;
extern vector< glm::vec3 > ladder_normals;

extern vector< glm::vec3 > door_vertices;
extern vector< glm::vec2 > door_uvs;
extern vector< glm::vec3 > door_normals;



#endif