/**
	
	main.cpp
	Purpose: To controll the application
	@author Linus Granathz
	@version 1.0 15/06-15
*/
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Model.h"
#include "Moving_Model.h"
#include "objloader.h"
#include <iostream>
#include "Main.h"
#include <math.h>
#include <vector>
#include "Models_info.h"
#include "Model_Complex.h"
#include "Math_Methods.h"
#include "Texture.h"
#include "Ghost.h"
#include "Level_Loader.h"
#include "Game_Vectors.h"

void reshape(int w, int h);
void display(void);
void init(void);
void calculate_center(GLfloat vertices[3][2]);
void keyboard_handler(unsigned char, int, int);
void keyboard_release_handler(unsigned char, int, int);
void mouse_handler(int, int);
void mouse_press_handler(int,int,int, int);
void iddle(void);
void update(int);
void update_time(void);
void check_gravity(void);
void move_forward(void);
void move_backward(void);
void move_left(void);
void move_right(void);
void check_doors(void);

Collision_Box *cameraCollisionBox;

bool w_down = false;
bool s_down = false;
bool a_down = false;
bool d_down = false;
static bool warped = false;

Texture *textures[TEXTURE_SIZE] = { NULL };


std::vector< glm::vec3 > ghost_vertices;
std::vector< glm::vec2 > ghost_uvs;
std::vector< glm::vec3 > ghost_normals;

std::vector< glm::vec3 > ak47_vertices;
std::vector< glm::vec2 > ak47_uvs;
std::vector< glm::vec3 > ak47_normals;

std::vector< glm::vec3 > block_vertices;
std::vector< glm::vec2 > block_uvs;
std::vector< glm::vec3 > block_normals;

std::vector< glm::vec3 > ground_vertices;
std::vector< glm::vec2 > ground_uvs;
std::vector< glm::vec3 > ground_normals;

std::vector< glm::vec3 > tunnel_vertices;
std::vector< glm::vec2 > tunnel_uvs;
std::vector< glm::vec3 > tunnel_normals;

std::vector< glm::vec3 > sign_vertices;
std::vector< glm::vec2 > sign_uvs;
std::vector< glm::vec3 > sign_normals;

std::vector< glm::vec3 > tower_vertices;
std::vector< glm::vec2 > tower_uvs;
std::vector< glm::vec3 > tower_normals;

std::vector< glm::vec3 > wall_vertices;
std::vector< glm::vec2 > wall_uvs;
std::vector< glm::vec3 > wall_normals;

std::vector< glm::vec3 > ladder_vertices;
std::vector< glm::vec2 > ladder_uvs;
std::vector< glm::vec3 > ladder_normals;

std::vector< glm::vec3 > door_vertices;
std::vector< glm::vec2 > door_uvs;
std::vector< glm::vec3 > door_normals;


enum PlayerState{ INAIR, ONGROUND, ONLADDER};
int playerState = ONGROUND;
enum Buffers{ ARRAYBUFFER ,ELEMENT_BUFFER, BUFFER_AMMOUNT };
enum Uniform{ VCOLOR, AMBIENT, DIRECTION, UNIFORM_SIZE};

GLuint buffers[BUFFER_AMMOUNT];
GLuint voa[1];

GLfloat playerspeed = 0.015, yspeed = 0, gravity = 0.00006, jumppower = 0.028;

GLuint gVAO[1];
GLuint uniformID[3];
Shader *shader;

std::vector<Model*> models;
std::vector<int> keys;

/* Vector used to store all the models*/
std::vector<Moving_Model*> moving_models;
/* Vector used to store all the doors*/
std::vector<Door*> doors;

/* Our main matrices */
glm::vec2 SCREEN_SIZE(800, 600);

glm::mat4 projectionMatrix;
glm::mat4 modelMatrix;
glm::mat4 viewMatrix; // Store view matrix
float fSunAngle = 57.0f;

GLuint rotateMatrixID, translateMatrixID, scaleMatrixID, colorID;
double redTriangleAngle = 0, blueTriangleAngle = 0, whiteTriangleAngle =0;

GLfloat camX, camY, camZ, cameradirectionXY = 0, cameradirectionZY = 0,prevCamX=0,prevCamY=0,prevCamZ=0;

int time_update = 1000 / 60;

int main(int args, char **argv){
	glutInit(&args, argv);
	glutInitContextVersion(3, 3);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(SCREEN_SIZE.x,SCREEN_SIZE.y);

	glutInitWindowPosition(0, 0);
	glutCreateWindow("TEST"); 
	glClearColor(0, 0.0, 0, 0.0); 
	glShadeModel(GL_FLAT);
	glewExperimental = GL_TRUE;
	glewInit();

	glutSetCursor(GLUT_CURSOR_NONE);
	//glEnable(GL_DEPTH_TEST);
	Shader shadertemp(".\\res\\basicShader");

	shader = &shadertemp;

	shader->Bind();
	uniformID[VCOLOR] = shader->getUniformLocation("sunLight.vColor");
	uniformID[AMBIENT] = shader->getUniformLocation("sunLight.fAmbientIntensity");
	uniformID[DIRECTION] = shader->getUniformLocation("sunLight.vDirection");
	//glUniform4fv(shader->getUniformLocation("sunLight.vColor"), 1, glm::value_ptr(sunColor));

	printf("PRE TEXUTRE");
	Texture texture(".\\res\\bricks.jpg");
	textures[BRICKS] = &texture;
	Texture shotguntext(".\\res\\texture_shotgun.bmp");
	textures[SHOTGUN] = &shotguntext;
	Texture grasstext(".\\res\\texture_grass.bmp");
	textures[GROUND] = &grasstext;
	Texture ghosttext(".\\res\\ghost.png");
	textures[GHOST] = &ghosttext;
	Texture ak47(".\\res\\ak47.png");
	textures[AK47] = &ak47;
	Texture signtext(".\\res\\sign.png");
	textures[SIGN] = &signtext;
	Texture towertext(".\\res\\tower.png");
	textures[TOWER] = &towertext;
	Texture ladertext(".\\res\\wood.png");
	textures[LADDER] = &ladertext;
	Texture doortext(".\\res\\door.png");
	textures[DOOR] = &doortext;
	texture.bind(0);

//	init_objects();
	load_obj(".\\res\\ghost.obj", ghost_vertices, ghost_uvs, ghost_normals);
	load_obj(".\\res\\ak47.obj", ak47_vertices, ak47_uvs, ak47_normals);
	load_obj(".\\res\\block.obj", block_vertices, block_uvs, block_normals);
	load_obj(".\\res\\ground.obj", ground_vertices, ground_uvs, ground_normals);
	load_obj(".\\res\\tunnel.obj", tunnel_vertices, tunnel_uvs, tunnel_normals);
	load_obj(".\\res\\sign.obj", sign_vertices, sign_uvs, sign_normals);
	load_obj(".\\res\\tower.obj", tower_vertices, tower_uvs, tower_normals);
	load_obj(".\\res\\ladder.obj", ladder_vertices, ladder_uvs, ladder_normals);
	load_obj(".\\res\\door.obj", door_vertices, door_uvs, door_normals);

	load_obj(".\\res\\wall.obj", wall_vertices, wall_uvs, wall_normals);

	load_level(".\\gamefiles\\level.txt", models,moving_models);

	// Create projection matrix with the given size, 45* view angle, 0.5znear and 200zfar
	projectionMatrix = glm::perspective(45.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 0.5f, 200.0f);

	// Setup camera matrix
	viewMatrix = glm::lookAt
		(glm::vec3(0, 0, 3),  // Position 0.0.3
		glm::vec3(0, 0, 0),  // Looks toward origin
		glm::vec3(0, 1, 0)); // Head is y axis up

	camX = 0;
	camY = 0;
	camZ = 0;
	// MOdel matrix, changes for each model ( model should be at origin)
	modelMatrix = glm::mat4(1.0f); // Identity matrix
	GLuint MatrixID = shader->getUniformLocation("MVP");
	GLuint normalMatrix = shader->getUniformLocation("normalMatrix");

	glm::mat4 MVP = projectionMatrix*viewMatrix*modelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(shader->getUniformLocation("vColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	
	//glUniform3f(shader->getUniformLocation("sunLight.vColor"), 1.0f, 1.0f, 1.0f);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_handler);
	glutKeyboardUpFunc(keyboard_release_handler);
	glutPassiveMotionFunc(mouse_handler);
	glutMouseFunc(mouse_press_handler);
	glutIdleFunc(iddle);

	// The value 1 is used as an identifier
	glutTimerFunc(time_update, update, 1);
	glutMainLoop();
	return 0;
}

Collision_Box* getCameraCollisionBox(){
	return cameraCollisionBox;
}
void update(int value){
	switch (value){
	case 1:
		update_time();
		glutTimerFunc(time_update, update, 1);
	}
}


void mouse_press_handler(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			Moving_Model *triangle = (new Moving_Model(block_vertices, block_uvs, block_normals, textures[BRICKS], GL_TRIANGLES));
			triangle->setScale(0.1, 0.1, 0.1);
			triangle->set_speed(0.2);
			triangle->move(-camX + 1 * cos(cameradirectionXY - (3.14 / 2)), -camY + 1 * -cos(cameradirectionZY - (3.14 / 2)), -camZ + 1 * sin(cameradirectionXY - (3.14 / 2)), MOVE_IGNORE_ZERO);
			//triangle.setHUD(true);
			triangle->set_direction_koefficents(cos(cameradirectionXY - (3.14 / 2)), -cos(cameradirectionZY - (3.14 / 2)), sin(cameradirectionXY - (3.14 / 2)));
			Collision_Box *box = triangle->get_collision_box();
			box->type = box->BULLET;
			
			models.insert(models.end(),triangle);
			moving_models.insert(moving_models.end(), triangle);

		}
		break;
	}
}

int get_time_update(){
	return time_update;
}

void update_time(){
	/* Move all objects */
	for (int i = 0; i < moving_models.size(); i++)
		moving_models.at(i)->update();

	/* Check gravity */
	check_gravity();

	prevCamX = camX;
	prevCamY = camY;
	prevCamZ = camZ;
	move_forward();
	move_backward();
	move_left();
	move_right();

}
void move_forward(){
	if (w_down){
		if (playerState == ONLADDER){
			camY -= 0.5f*playerspeed*get_time_update();
		}
		else{
			if (cameradirectionXY > 3.14 * 2)
				cameradirectionXY -= 3.14 * 2;
			camZ += sin(cameradirectionXY + (3.14 / 2)) *playerspeed*get_time_update();
			camX += cos(cameradirectionXY + (3.14 / 2))*playerspeed*get_time_update();
		}
	}
}

void move_backward(){
	if (s_down){
		if (playerState == ONLADDER){
			camY += 0.5f*playerspeed*get_time_update();
		}
		else{
			if (cameradirectionXY > 3.14 * 2)
				cameradirectionXY -= 3.14 * 2;

			camZ += sin(cameradirectionXY - (3.14 / 2)) *playerspeed*get_time_update();
			camX += cos(cameradirectionXY - (3.14 / 2)) *playerspeed*get_time_update();
		}
	}
}

void move_left(){
	if (a_down){
		if (cameradirectionXY > 3.14)
			cameradirectionXY -= 3.14;
		camZ += sin(cameradirectionXY) *playerspeed*get_time_update();
		camX += cos(cameradirectionXY) *playerspeed*get_time_update();
	}
}

void move_right(){
	if (d_down){
		if (cameradirectionXY > 3.14)
			cameradirectionXY -= 3.14;
		camZ -= sin(cameradirectionXY) *playerspeed*get_time_update();
		camX -= cos(cameradirectionXY) *playerspeed*get_time_update();
	}
}

void check_gravity(void){

	if (yspeed != 0 && playerState !=ONLADDER)
		playerState = INAIR;
	if (camY > 0 && yspeed < 0){
		camY = 0;
		playerState = ONGROUND;
		printf("MAYDAY");
		yspeed = 0;
	}
	else if (camY < 0){
		yspeed -= gravity*get_time_update();
	}
	if (playerState == INAIR)
	camY -= yspeed*get_time_update();
}
void mouse_handler(int x, int y){
	static int CENTERX = SCREEN_SIZE.x / 2;
	static int CENTERY = SCREEN_SIZE.y / 2;
		cameradirectionXY += 3.14 / 360 * (-SCREEN_SIZE.x/2 +x);
		
		cameradirectionZY += 3.14 / 370 * (-SCREEN_SIZE.y / 2 + y);
		if (cameradirectionZY >= 3.14 / 2 - (3.14/6))
			cameradirectionZY = 3.14 / 2 - (3.14/6);
		else if (cameradirectionZY < -3.14 / 2 + (3.14 / 6))
			cameradirectionZY = -3.14 / 2 + (3.14/6);
		if (!warped){
			glutWarpPointer(CENTERX, CENTERY);
			warped = true;
		}
		else
			warped = true;
}
void iddle(){
	warped = false;
	glutPostRedisplay();
}

/**
	Initialize, create our models
*/
void init(){

	glEnableClientState(GL_VERTEX_ARRAY);
	cameraCollisionBox = new Collision_Box(1.2, 2.0, 0,2.4, 0, 1.7);
	//cameraCollisionBox->set_offset(-2.4,-1.2,-0.5);
	cameraCollisionBox->type = cameraCollisionBox->CAMERA;
	cameraCollisionBox->set_position(0, 0, 0);
	Model* triangle;
	triangle = (new Model(ak47_vertices, ak47_uvs, ak47_normals, textures[AK47])); 
	triangle->move(0.5, -1, 0 -0.10, MOVE_TO);
	triangle->set_ignore_collision(true);
	triangle->setHUD(true);
	models.insert(models.end(), triangle);
	//Model triangle;
	
	triangle = (new Model(ground_vertices, ground_uvs, ground_normals,textures[GROUND]));
	triangle->move(200, -1, 200, MOVE_TO);
	triangle->set_ignore_collision(true);
	triangle->setAmbient(0.55f);
	models.insert(models.end(), triangle);
	////models.at(1).rotateX(45);
	////models.at(1).move(-0.5 ,-0.2, 0, MOVE_IGNORE_ZERO);
	///*for (int i = 0; i < 10; i++){
	//	triangle = *(new Model(high_cubes_vertexes, high_cube_indices, cube_normals, 36, 24, 24, textures[BRICKS], GL_TRIANGLES));
	//	triangle.move(-8 * i, 0, -20, MOVE_IGNORE_ZERO);
	//	triangle.set_collision_dimensions(4.0, 10.0, 4.0);
	//	models.insert(models.end(), triangle);
	//}*/



	//for (int i = 0; i < 10; i++){
	//	triangle = (new Model(block_vertices, block_uvs, block_normals, textures[BRICKS], triangle->SOLID));
	//	triangle->setScale(1.0, 3.0, 1.0);
	//	triangle->move(-8 * i, 0, -16, MOVE_IGNORE_ZERO);
	//	models.insert(models.end(), triangle);
	//}

	//triangle = (new Model(block_vertices, block_uvs, block_normals, textures[BRICKS], triangle->SOLID));
	////triangle->setScale(1.0, 3.0, 1.0);
	//triangle->move(0, 0, 0, MOVE_IGNORE_ZERO);
	////models.insert(models.end(), triangle);
	//

	//for (int i = 0; i < 10; i++){
	//	Ghost* moving_triangle = (new Ghost(ghost_vertices, ghost_uvs, ghost_normals, textures[GHOST]));
	//	moving_triangle->move(16 - 32 * i, -2, 4 + 24, MOVE_TO);
	//	moving_triangle->rotateX(2 * 3.14 / 8 * i);
	//	moving_triangle->set_speed(0.015f);
	//	moving_triangle->set_direction_koefficents(cos(cameradirectionXY - (3.14 / 2)), -cos(cameradirectionZY - (3.14 / 2)), sin(cameradirectionXY - (3.14 / 2)));
	//	models.insert(models.end(), moving_triangle);
	//	moving_models.insert(moving_models.end(), moving_triangle);
	//}

	////for (int i = 0; i < 20; i++){
	////	for (int j = 0; j < 10; j++){
	////		triangle = *(new Model(floating_platform_vertexes, floating_platform_indices, cube_normals, 36, 24, 24, textures[BRICKS], GL_TRIANGLES));
	////		triangle.move(-4 * i + 82, 5, -44 + j*4, MOVE_IGNORE_ZERO);
	////		triangle.set_collision_dimensions(4.0, 4.0, 4.0);
	////		models.insert(models.end(), triangle);
	////	}
	////}

	////triangle = *(new Model(floating_platform_vertexes, floating_platform_indices, cube_normals, 36, 24, 24, textures[BRICKS], GL_TRIANGLES));
	////triangle.move(-8 , 16, -32, MOVE_IGNORE_ZERO);
	////models.insert(models.end(), triangle);


	//for (int i = 0; i < 10; i++){
	//	triangle = (new Model(block_vertices, block_uvs, block_normals, textures[BRICKS], triangle->SOLID));
	//	triangle->move(-8 * i, 0, -8, MOVE_IGNORE_ZERO);
	//	////triangle.setHUD(true);
	//	//triangle.setColor(0.0, 0.0, 1.0, 1.0);
	//	models.insert(models.end(), triangle);

	//}

	//triangle = (new Model(tower_vertices, tower_uvs, tower_normals, textures[TOWER], triangle->SOLID));
	//triangle->move(-40, -2, 80, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(wall_vertices, wall_uvs, wall_normals, textures[BRICKS], triangle->SOLID));
	//triangle->move(-56, -2, 80, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(tower_vertices, tower_uvs, tower_normals, textures[TOWER], triangle->SOLID));
	//triangle->move(-80, -2, 80, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(wall_vertices, wall_uvs, wall_normals, textures[BRICKS], triangle->SOLID));
	//triangle->move(-84, -2, 96, MOVE_IGNORE_ZERO);
	//triangle->rotateX(3.14 / 2);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(tower_vertices, tower_uvs, tower_normals, textures[TOWER], triangle->SOLID));
	//triangle->move(-80, -2, 120, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(wall_vertices, wall_uvs, wall_normals, textures[BRICKS], triangle->SOLID));
	//triangle->move(-56, -2, 120, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(tower_vertices, tower_uvs, tower_normals, textures[TOWER], triangle->SOLID));
	//triangle->move(-40, -2, 120, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(wall_vertices, wall_uvs, wall_normals, textures[BRICKS], triangle->SOLID));
	//triangle->move(-40, -2, 96, MOVE_IGNORE_ZERO);
	//triangle->rotateX(3.14 / 2);
	//models.insert(models.end(), triangle);


	//triangle = (new Model(ladder_vertices, ladder_uvs, ladder_normals, textures[LADDER], triangle->LADDER));
	//triangle->move(64, -0.5, 32, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(ladder_vertices, ladder_uvs, ladder_normals, textures[LADDER], triangle->LADDER));
	//triangle->move(64, -0.5 + 6, 32, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(ladder_vertices, ladder_uvs, ladder_normals, textures[LADDER], triangle->LADDER));
	//triangle->move(64, -0.5 + 12, 32, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);

	//triangle = (new Model(block_vertices, block_uvs, block_normals, textures[BRICKS], triangle->SOLID));
	//triangle->move(64-3,13, 32, MOVE_IGNORE_ZERO);
	//models.insert(models.end(), triangle);
	////for (int i = 0; i < 10; i++){
	////	triangle = (new Model(sign_vertices, sign_uvs, sign_normals, textures[SIGN], triangle->SOLID));
	////	triangle->move(-8 * i, 0, 32, MOVE_IGNORE_ZERO);
	////	////triangle.setHUD(true);
	////	//triangle.setColor(0.0, 0.0, 1.0, 1.0);
	////	models.insert(models.end(), triangle);
	////}

	//for (int i = 0; i < 10; i++){
	//	Model_Complex * model_triangle = (new Model_Complex(tunnel_vertices, tunnel_uvs, tunnel_normals, textures[BRICKS], triangle->TUNNEL));
	//	model_triangle->move(-4 * i, 0, -48, MOVE_IGNORE_ZERO);
	//	Collision_Box* box = new Collision_Box(5, 1, 1, 3, 1, 1.4);
	//	box->set_offset(0, 0, -2);
	//	model_triangle->add_collision_box(box);
	//	box = new Collision_Box(5, 1, 1, 3, 1, 1.2);
	//	box->set_offset(0, 0, 2);
	//	model_triangle->add_collision_box(box);
	//	models.insert(models.end(), model_triangle);
	//	box = new Collision_Box(7, 1,0, 3, 0.6, 6);
	//	box->set_offset(-1, 3, 1);
	//	model_triangle->add_collision_box(box);

	//}
	//for (int i = 0; i < 10; i++){
	//	//triangle = *(new Model(cube_vertexes, cube_indices, cube_normals, 36, 24, 24, textures[BRICKS], GL_TRIANGLES));
	//	//triangle.move(-64 * i, 0, -32, MOVE_IGNORE_ZERO);
	//	//triangle.setScale(0.5, 4.0, 0.5);
	//	//////triangle.setHUD(true);
	//	////triangle.setColor(0.0, 0.0, 1.0, 1.0);
	//	//models.insert(models.end(), triangle);

	//}

	// make and bind the VAO
	glGenVertexArrays(1, gVAO);
	glBindVertexArray(gVAO[0]);

	GLuint gVBO[1];

	// make and bind the VBO
	glGenBuffers(1, gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[0]);

	// Put the three triangle verticies into the VBO
	GLfloat vertexData[] = {
		//  X     Y     Z
		-0.1f, -0.8f, 0.0f,
		0.0f , 0.8f, 0.0f,
		0.1f , -0.8f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// connect the xyz to the "vPosition" attribute of the vertex shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//models.at(2).rotateX(0);
	//models.at(2).setColor(1, 0, 0, 1);

}
std::vector<Moving_Model*>* get_moving_models(){
	return &moving_models;
}
void keyboard_release_handler(unsigned char key, int x, int y){
	printf("RELEASED");
	key = toupper(key);
	switch (key){
	case 'W':
				w_down = false;
			break;

	case 'S':
				s_down = false;
			break;

	case 'A':
				a_down = false;
			break;

	case 'D':
				d_down = false;

			break;
}
}
void uniform_set_ambient(GLfloat ambient){
	glUniform1f(uniformID[AMBIENT], ambient);
}

/* Handles the keyboard input, used for moving the arrow*/
void keyboard_handler(unsigned char key, int x, int y){
	key = toupper(key);
	switch (key){

	case 32:
		if (playerState == ONGROUND)
			yspeed = jumppower;
		break;
	case 'X':
		fSunAngle += 3.14 / 180 * 100;
		//glutPostRedisplay();
		break;

	case 'Z':
		fSunAngle -= 3.14 / 180 * 100;
		//glutPostRedisplay();
		break;

	case 'W':
		w_down = true;
		break;
	case 'E':
		check_doors();
		break;
	case 'Q':
		printf("ADD KEY %d ",keys.size());
		keys.insert(keys.end(), keys.size());
		break;
	case 'S':	
			s_down = true;
		break;

	case 'A':
			a_down = true;
		break;

	case 'D':
			d_down = true;
		
		break;
	}
}

/**
	Render the scene
*/
void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	set_color(glm::vec4(1.0, 1.0, 1.0, 1.0));
	// Projection matrix : 45° Field of View, aspect ratio, display range : 1 unit <-> 200 units
	projectionMatrix = glm::perspective(30.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 1.0f, 200.0f);
	glUniformMatrix4fv(shader->getUniformLocation("prespective"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	// Camera matrix
	viewMatrix = glm::lookAt(
		glm::vec3(0, 0, 1), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	GLfloat tx = 0, ty = 0, tz =1;

	textures[0]->bind(0);
	glUniformMatrix4fv(shader->getUniformLocation("camera"), 1, GL_FALSE, glm::value_ptr(viewMatrix));



	// Model matrix : an identity matrix (model will be at the origin)
	modelMatrix = glm::mat4(1.0f);// Changes for each model !
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 2));//scalling by 2x
	// 
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));//translating to negative z-axis
	//modelMatrix = glm::rotate(modelMatrix, cameradirectionXY, glm::vec3(0, 1, 0));//rotating in clockwise direction
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(camX, camY, -5 + camZ));//translating to negative z-axis


	//modelMatrix = glm::translate(modelMatrix, glm::vec3(camX, camY, -5 + camZ));//translating to negative z-axis
	//printf("camx %f, camy %f, camz %f, camdirection %f, caX-tx %f, camY-ty %f, camZ-tz %f\n", camX, camY, camZ,cameradirectionXY*180 / 3.14,camX-tx,camY-ty,camZ-tz);
	send_model_matrix();

	//glBindVertexArray(gVAO[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	/**
		Draw all models
	*/
	//for (int i = 0; i < models.size();i++)
	//models.at(2).draw();
	float fSine = sin(fSunAngle*3.1415 / 180.0);
	glm::vec3 vSunPos(cos(fSunAngle*3.1415 / 180.0) * 70, sin(fSunAngle*3.1415 / 180.0) * 70, -10.0);

	glm::vec3 normalizesun = -glm::normalize(vSunPos);

	GLfloat normalizearray[3] = { normalizesun.x, normalizesun.y, normalizesun.z };
	glUniform1f(uniformID[AMBIENT], 0.15f);
	glUniform3fv(uniformID[DIRECTION], 1, glm::value_ptr(normalizesun));
	glm::vec3 sunColor(1.0f, 1.0f, 1.0f);
	glUniform3fv(uniformID[VCOLOR],1, glm::value_ptr(sunColor));

	//cameraCollisionBox->set_position(0, 0, 0);

	
	for (int i = 0; i < models.size(); i++){

		models.at(i)->draw();
		int coll = models.at(i)->check_collision(cameraCollisionBox);
		if (models.at(i)->getObjectID() == models.at(i)->LADDER){
			if (coll == 1){
				playerState = ONLADDER;
			}
			else if (coll == 2)
			{
				playerState = ONGROUND;
				if (yspeed < 0){
					yspeed = 0;
					//	camY = prevCamY;
				}
			}
			else if (coll == 3)
			{
				
				if (yspeed > 0){
					yspeed = 0;
					camY = prevCamY;
				}
			}
		}
		else{
			if (coll == 1){
				printf("..");
				camX = prevCamX;
				camY = prevCamY;
				camZ = prevCamZ;
			}
			else if (coll == 2)
			{
				playerState = ONGROUND;
				if (yspeed < 0){
					yspeed = 0;
					//	camY = prevCamY;
				}
			}
			else if (coll == 3)
			{
				if (yspeed > 0){
					yspeed = 0;
					camY = prevCamY;
				}
			}
			else if (coll == 4)
			{
				printf("SETUPU");
				camY -= 0.2f;
			}
		}
	}

	glFlush();

}
Line_Of_Sight_Object* create_los_object(bool in_sight){
	Line_Of_Sight_Object* los = new Line_Of_Sight_Object(block_vertices, block_uvs, block_normals, textures[BRICKS], in_sight);

	return los;
}

Shader* getShader(){
	return shader;
}

std::vector<Model*>* get_models(void){
	return &models;
}
/**
	Set the rotatation matrix for z-axis
*/
void rotate(double angle, int axis){
	angle = angle * (3.14 / 180);
	GLfloat rotateMatrix[4][4] = {
		{ cos(angle), sin(angle), 0, 0 },
		{ -sin(angle), cos(angle), 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	glUniformMatrix4fv(rotateMatrixID, 1, GL_FALSE, &rotateMatrix[0][0]);
}

/**
	Change the translation matrix
	@param x steps on x-axis
	@param y steps on y-axis
	@param z steps on z-axis
*/
void translate(float x, float y, float z){

	/* Construct the translation matrix*/
	GLfloat translateMatrix[4][4] = {
		{ 1, 0, 0, x },
		{ 0, 1, 0, y },
		{ 0, 0, 1, z },
		{ 0, 0, 0, 1 }
	};

	// Send the matrix to our shader
	glUniformMatrix4fv(translateMatrixID, 1, GL_TRUE, &translateMatrix[0][0]);
}

/**	
	Change the color 
	@param r red color
	@param g green color
	@param b blue color
	@param a alpha
*/
void set_color_main(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	GLfloat color[4] = { r, g, b, a };

	// Send the color to our shader
	glUniform4fv(colorID,1,&color[0]);
}

glm::mat4 getProjectionMatrix(){
	return projectionMatrix;
}

glm::mat4* getModelMatrix(){
	return &modelMatrix;
}


glm::mat4 getviewMatrix(){
	return viewMatrix;

}

GLfloat getCameradirectionXY(){
	return cameradirectionXY;
}
GLfloat getCameradirectionZY(){
	return cameradirectionZY;
}


GLfloat getCamX(){
	return camX;
}
GLfloat getCamY(){
	return camY;
}
GLfloat getCamZ(){
	return camZ;
}

void send_model_matrix(){
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
void set_color(const glm::vec4 &color){
	//glUniformMatrix4fv(shader->getUniformLocation("in_color"), 1, GL_FALSE, glm::value_ptr(color));
}
/*
void send_model_matrix(glm::mat4 model_matrix){
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
}*/

Texture** get_texutre(){
	return textures;
}

void check_doors(){
	for (int i = 0; i < doors.size(); i++){
		if (calc_distance(doors.at(i)->get_pos_x() + camX, 0, doors.at(i)->get_pos_y() + camY, 0, doors.at(i)->get_pos_z() + camZ, 0) < 6){
			if (doors.at(i)->get_state() == doors.at(i)->CLOSED ||doors.at(i)->get_state() == doors.at(i)->LOCKED){
				doors.at(i)->unlock(keys);
			}
			else if (doors.at(i)->get_state() == doors.at(i)->OPEN){
				doors.at(i)->close();
			}
		}
	}
}