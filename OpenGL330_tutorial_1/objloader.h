#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm\glm.hpp"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\projection.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

bool load_obj(const char* path, std::vector <glm::vec3 > &out_vertices,
	std::vector <glm::vec2 > &out_uvs, std::vector <glm::vec3 > &out_normals
	);