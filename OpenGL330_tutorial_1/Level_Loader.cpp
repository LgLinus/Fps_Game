#include "Level_Loader.h"
#include "Main.h"
#include "Ghost.h"
#include "Door.h"
#include "Game_Vectors.h"

bool load_level(const char* path, std::vector<Model*> &models, std::vector<Moving_Model*> &moving_models){
	FILE * file = fopen(path, "r");
	if (file == NULL){
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// If wall object
		if (strcmp(lineHeader, "WALL") == 0){
			glm::vec3 positions;
			glm::vec3 scales;
			glm::vec3 rotations;
			// Read the three coordinates and store in vertexes
			if (fscanf(file, "%f %f %f\n", &positions.x, &positions.y, &positions.z)){
				//printf("pos ok");
			}
			else{
			//	printf("positions not found");
			}
			if (fscanf(file, "%f %f %f\n", &scales.x, &scales.y, &scales.z)){
				//printf("scales ok");
			}
			else{
				//printf("scales not found");
			}
			if (fscanf(file, "%f %f %f\n", &rotations.x, &rotations.y, &rotations.z)){
				//printf("rotations ok");
			}
			else{
				//printf("rotations not found");
			}

			Model* model = new Model(block_vertices, block_uvs, block_normals, textures[BRICKS], 0);
			model->move(positions.x, positions.y, positions.z, MOVE_TO);
			model->setScale(scales.x, scales.y, scales.z);

			models.insert(models.end(), model);

		}
		else if (strcmp(lineHeader, "GHOST") == 0){
			glm::vec3 positions;
			glm::vec3 scales;
			glm::vec3 rotations;
			// Read the three coordinates and store in vertexes
			if (fscanf(file, "%f %f %f\n", &positions.x, &positions.y, &positions.z)){
				//printf("pos ok");
			}
			else{
				//printf("positions not found");
			}
			if (fscanf(file, "%f %f %f\n", &scales.x, &scales.y, &scales.z)){
				//printf("scales ok");
			}
			else{
				//printf("scales not found");
			}
			if (fscanf(file, "%f %f %f\n", &rotations.x, &rotations.y, &rotations.z)){
				//	printf("rotations ok");
			}
			else{
				//printf("rotations not found");
			}

			Ghost* model = new Ghost(ghost_vertices, ghost_uvs, ghost_normals, textures[GHOST]);
			model->move(positions.x, positions.y, positions.z, MOVE_TO);
			model->setScale(scales.x, scales.y, scales.z);

			models.insert(models.end(), model);
			moving_models.insert(moving_models.end(), model);
		}

		else if (strcmp(lineHeader, "DOOR") == 0){
			glm::vec3 positions;
			glm::vec3 scales;
			glm::vec3 rotations;
			int keyID = 0;
			// Read the three coordinates and store in vertexes

			if (fscanf(file, "%f %f %f\n", &positions.x, &positions.y, &positions.z)){
				printf("pos ok");
			}
			else{
				printf("positions not found");
			}
			if (fscanf(file, "%f %f %f\n", &scales.x, &scales.y, &scales.z)){
				printf("scales ok");
			}
			else{
				printf("scales not found");
			}
			if (fscanf(file, "%f %f %f %d \n", &rotations.x, &rotations.y, &rotations.z,&keyID)){
				printf("rotations ok");
			}
			else{
				printf("rotations not found");
			}


			//	printf("X: %f, Y: %f, Z %f \n", positions.x, positions.y, positions.z);
			Door* model = new Door(door_vertices, door_uvs, door_normals, textures[DOOR],keyID);
			model->move(positions.x, positions.y, positions.z, MOVE_TO);
			model->setScale(scales.x, scales.y, scales.z);
			model->rotateX(rotations.x);

			models.insert(models.end(), model);
			moving_models.insert(moving_models.end(), model);
			doors.insert(doors.end(), model);
		}
		else if (strcmp(lineHeader, "GHOST") == 0){
			glm::vec3 positions;
			glm::vec3 scales;
			glm::vec3 rotations;
			// Read the three coordinates and store in vertexes
			if (fscanf(file, "%f %f %f\n", &positions.x, &positions.y, &positions.z)){
				//printf("pos ok");
			}
			else{
				//printf("positions not found");
			}
			if (fscanf(file, "%f %f %f\n", &scales.x, &scales.y, &scales.z)){
				//printf("scales ok");
			}
			else{
				//printf("scales not found");
			}
			if (fscanf(file, "%f %f %f\n", &rotations.x, &rotations.y, &rotations.z)){
				//	printf("rotations ok");
			}
			else{
				//printf("rotations not found");
			}

			Ghost* model = new Ghost(ghost_vertices, ghost_uvs, ghost_normals, textures[GHOST]);
			model->move(positions.x, positions.y, positions.z, MOVE_TO);
			model->setScale(scales.x, scales.y, scales.z);

			models.insert(models.end(), model);
			moving_models.insert(moving_models.end(), model);
		}

		else if (strcmp(lineHeader, "LADDER") == 0){
			glm::vec3 positions;
			glm::vec3 scales;
			glm::vec3 rotations;
			// Read the three coordinates and store in vertexes

			if (fscanf(file, "%f %f %f\n", &positions.x, &positions.y, &positions.z)){
				printf("pos ok");
			}
			else{
				printf("positions not found");
			}
			if (fscanf(file, "%f %f %f\n", &scales.x, &scales.y, &scales.z)){
				printf("scales ok");
			}
			else{
				printf("scales not found");
			}
			if (fscanf(file, "%f %f %f\n", &rotations.x, &rotations.y, &rotations.z)){
				printf("rotations ok");
			}
			else{
				printf("rotations not found");
			}
			 
			Model* model = new Model(ladder_vertices, ladder_uvs, ladder_normals, textures[LADDER], model->LADDER);
			model->move(positions.x, positions.y, positions.z, MOVE_TO);
			model->setScale(scales.x, scales.y, scales.z);
			model->rotateX(rotations.x);

			models.insert(models.end(), model);
		}
		
	}
	return true;
	// else : parse lineHeader
}