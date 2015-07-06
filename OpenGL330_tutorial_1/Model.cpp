/**
	Model.cpp
	Purpose: To controll various models created from vertexes and indices. The Model 
	allows transformations such as rotation and translation. It also supports color changing.
*/
#include "Model.h"
#include "main.h"
#include <iostream>


using namespace std;
Model::Model(std::vector<glm::vec3> vertices_init, std::vector<glm::vec2> uvs_init, std::vector<glm::vec3> normals_init, Texture *text, GLuint objectID){
	//normals = normals_init;
	texture = text;
	ambient = 0.2f;
	color = &glm::vec4(1.0, 1.0, 1.0, 1.0);
	ISHUD = false;
	ignoreCollision = false;
	scaleY = 1;
	scaleX = 1;
	scaleZ = 1;
	vertices = vertices_init;
	/* Copy the vertexes */
	normals = normals_init;
	/* Copy the indices */
	uvs = uvs_init;

	normals = normals_init;
	/* If we want the model to rotate around it's middle point do that*/
	
	this->objectID = objectID;

	/* Bind the vertex and indices values to our vetrex buffer object */
	create_collision_box();
	init_buffers();

	id = get_models()->size();
}

void Model::move_collision_box(){
	collisionBox->set_position(posX + getCamX(), posY + getCamY(), posZ + getCamZ());
}


void Model::removeFromModels(std::vector<Model*>* models){
	bool destroy = false;
	GLuint coll = 0, myPos = -1;
	for (int i = 0; i < models->size(); i++){
		if (id == models->at(i)->id)
			myPos = i;
	}
	if (myPos!=-1)
		models->erase(models->begin() + myPos);
}

void Model::setScale(GLfloat scale_x, GLfloat scale_y, GLfloat scale_z){
	scaleX = scale_x;
	scaleY = scale_y;
	scaleZ = scale_z;
	//reform_texture();
	create_collision_box();
}

void Model::reform_texture(){
	glBindVertexArray(voab[0]);
	GLfloat **verticearray;
	verticearray = (GLfloat**)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);

	for (int i = 0; i < 1; i++){
		verticearray[i][4] = verticearray[i][4]*scaleY;
		verticearray[i][5] *= scaleX;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Model::create_collision_box(void){
	GLfloat lowX, lowY, lowZ, highX, highY, highZ;
	lowX = vertices[0][0];
	highX = vertices[0][0];
	lowY = vertices[0][1];
	highY = vertices[0][1];
	lowZ = vertices[0][2];
	highZ = vertices[0][2];

	/* Find lowest and highest values*/
	for (int i = 0; i < vertices.size(); i++){

		// Lowest, highest X value
		if (vertices[i][0] < lowX)
			lowX = vertices[i][0];
		if (vertices[i][0] > highX)
			highX = vertices[i][0];

		// Lowest, highest Y value
		if (vertices[i][1] < lowY)
			lowY = vertices[i][1];
		if (vertices[i][1] > highY)
			highY = vertices[i][1];

		// Lowest, highest Z value
		if (vertices[i][2] < lowZ)
			lowZ= vertices[i][2];
		if (vertices[i][2] > highZ)
			highZ = vertices[i][2];
	}
	lowX *= scaleX;
	highX *= scaleX;
	lowY *= scaleY;
	highY *= scaleY;
	lowZ *= scaleZ;
	highZ *= scaleZ;
	collisionBox = new Collision_Box(lowX,highX,lowY,highY,lowZ,highZ);
}

GLuint Model::getObjectID(void){
	return objectID;
}

void Model::removeFromList(void){
	
}
void Model::setAmbient(GLfloat ambient){
	this->ambient = ambient;
}

void Model::update(){
	
}
/** 
	Initializes the buffers for the model 
*/
void Model::init_buffers(){
	glGenVertexArrays(1, voab);
	glBindVertexArray(voab[0]);

	glGenBuffers(BUFFER_SIZE, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEXES]);

	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[UVS]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ELEMENTS]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indicesSize,
	//	indices, GL_STATIC_DRAW);

	// Normal vectors
	glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMALS]);
	glBufferData(GL_ARRAY_BUFFER,normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

/**
	Draws the model with the given settings.
*/
void Model::draw(){
	glBindVertexArray(voab[0]);
	
	texture->bind(0);
	
	glm::mat4* modelMatrix = getModelMatrix();
	glm::mat4 modelToCamera =*getModelMatrix();
	glm::mat4 scaleMatrix = { 
		glm::vec4(scaleX, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, scaleY, 0.0f, 0.0f), 
		glm::vec4(0.0f, 0.0f, 0.0f, scaleZ), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };

	*modelMatrix = glm::mat4(1.0f);// Changes for each model !

	/* IF the object is not part of the hub, transform it*/
	if (!ISHUD){
		*modelMatrix = glm::rotate(*modelMatrix, getCameradirectionZY(), glm::vec3(1, 0, 0));//rotating in clockwise direction
	*modelMatrix = glm::rotate(*modelMatrix, getCameradirectionXY(), glm::vec3(0, 1, 0));//rotating in clockwise direction

	*modelMatrix = glm::translate(*modelMatrix, glm::vec3(getCamX() + posX, getCamY() + posY, getCamZ() + posZ));//translating to negative z-axis
	*modelMatrix = glm::rotate(*modelMatrix, (GLfloat)angleX, glm::vec3(0, 1, 0));//rotating in clockwise direction
	collisionBox->set_position(getCamX() + posX, getCamY() + posY, getCamZ() + posZ);
//	printf("%d", getCamX() + posX);
	}
	/* If it is, stick it to the screen*/
	else{
		*modelMatrix = glm::translate(*modelMatrix, glm::vec3(posX, posY, posZ));//translating to negative z-axis
	}

	*modelMatrix = glm::scale(*modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));
	send_model_matrix();
	modelToCamera = glm::rotate(modelToCamera, getCameradirectionZY(), glm::vec3(1, 0, 0));
	modelToCamera = glm::translate(glm::mat4(1.0), glm::vec3(posX, posY, posZ));
	*modelMatrix = glm::rotate(*modelMatrix, (GLfloat)angleX, glm::vec3(0, 1, 0));//rotating in clockwise direction

	//// We need to trasnsform normals properly, it's done by transpose of inverse matrix of rotations and scales
	glm::mat4x4 lighting = glm::transpose(glm::inverse(modelToCamera));
	getShader()->setLighting("normalMatrix",lighting);
	uniform_set_ambient(ambient);
	//glDrawElements(drawMode, indicesSize, GL_UNSIGNED_BYTE, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Model::setHUD(bool is_HUD){
	ISHUD = is_HUD;
}
/**
	Calculates the center point of the vertexes, this allows the model to
	rotate around it's own axis. Only used if center is set to false in constructor
*/
void Model::calculateMidPoint(){
	float totalX=0, totalY=0, totalZ=0, toCenterX, toCenterY, toCenterZ;

	/* Retrieve total X and Y position*/
	for (int i = 0; i < vertices.size(); i++){
		totalX += vertices[i][0];
		totalY += vertices[i][1];
		totalZ += vertices[i][2];
	}
	/* Get average coordinate (middlepoint)*/
	toCenterX = totalX / vertices.size();
	toCenterY = totalY / vertices.size();
	toCenterZ = totalZ / vertices.size();

	setMidPoint(toCenterX, toCenterY, toCenterZ);

}
void Model::set_ignore_collision(bool ignore){
	ignoreCollision = ignore;
}
/**
	Sets the middle point for the model
	@param dx steps in x-axis to move to get to middlepoint
	@param dy steps in y-axis to move to get to middlepoint
*/
void Model::setMidPoint(GLfloat dx, GLfloat dy, GLfloat dz){
	dX = dx;
	dY = dy;
	dZ = dz;
	for (int i = 0; i < vertices.size(); i++){
		vertices[i][0] -= dx;
		vertices[i][1] -= dy;
		vertices[i][2] -= dZ;
	}
	for (int i = 0; i < vertices.size(); i++){
		//printf("X: %f, Y: %f Z: %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
	}
}

/**
	Rotate the model around x-axis with the given angle
	@param angle to rotate
*/
void Model::rotateX(GLdouble angle){
	angleX = angle;
	collisionBox->rotateX(angle);
}

/**
	Move the model with the given coordinates
	@param x steps to move in x-axis
	@param y steps to move in y-axis
	@param z steps to move in z-axis
	@param move_type defines if the model should move relative to it's position 
	or if it should teleport to the given location.
*/
void Model::move(GLfloat x, GLfloat y, GLfloat z, enum move move_type){
	switch (move_type){
	case MOVE_IGNORE_ZERO:
		if (x != 0)
			posX = x;
		if (y != 0)
			posY = y;
		if (z != 0)
			posZ = z;
		break;

	case MOVE_RELATIVE:
		posX += x;
		posY += y;
		posZ += z;

	case MOVE_TO:
		posX = x;
		posY = y;
		posZ = z;
	}
}



/* Getters for the position of the model */
GLfloat Model::get_pos_y(){
	return posY;
}
GLfloat Model::get_pos_x(){
	return posX;
}
GLfloat Model::get_pos_z(){
	return posZ;
}

void Model::set_collision_dimensions(GLfloat width, GLfloat height, GLfloat depth){
	collisionBox->width = width;
	collisionBox->height = height;
	collisionBox->depth = depth;
}

int Model::check_collision(Collision_Box* otherBox){
	if (!ignoreCollision)
		return collisionBox->check_collision(otherBox);
	else
		return 0;
	
}

Collision_Box* Model::get_collision_box(void){
	return collisionBox;
}
