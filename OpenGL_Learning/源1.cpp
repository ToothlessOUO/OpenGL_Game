#include <GL/glut.h>
#include <cmath>
#include "stb_image.h"
#include <iostream>
#include <string>
#include "Game_Component.hpp"
#include "Textures.hpp"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

static const int WIDTH = 1280, HEIGHT = 800;

float* normalizeColor(int Red, int Green, int Blue, int Alpha);
namespace color {
	float* g = normalizeColor(235, 231, 235, 0);
	//底色
	float* p = normalizeColor(221, 109, 80, 0);
	//副色
	float* b = normalizeColor(146, 32, 22, 0);
	//主色
}
Textures TEXTURE;

Game_Component CAT;
static const string cat_texture_file = R"(D:\Asserts\cat_15_13.png)";
static const string cat_stand_face_to_right = "C1";
static const string cat_stand_face_to_left = "C2";

//多贴图对象需要拥有临时贴图变量
string cat_texture_temp;

//可操控物件需要设置运动速度
static const float cat_speed = 3.0f;

Game_Component FISH;
Game_Component FISH_1;
static const string fish_texture_file = R"(D:\Asserts\fish_16_16.png)";
static const string fish = "F";

Game_Component PUPI;
static const string pupi_texture_file = R"(D:\Asserts\pipe_16_16.png)";
static const string pupi = "P";

Game_Component BACKGROUND;
static const string background_texture_file = R"(D:\Asserts\QQ截图20221026134331.png)";
static const string background = "G";

void initTextures() {
	vector<string> fileNames;
	fileNames.push_back(cat_texture_file);
	fileNames.push_back(cat_texture_file);
	fileNames.push_back(fish_texture_file);
	fileNames.push_back(pupi_texture_file);
	fileNames.push_back(background_texture_file);
	vector<string> names;
	names.push_back(cat_stand_face_to_right);
	names.push_back(cat_stand_face_to_left);
	names.push_back(fish);
	names.push_back(pupi);
	names.push_back(background);
	TEXTURE.addTextures(fileNames, names);
	float pos1[8] = { 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f };
	TEXTURE.setTexturePos(TEXTURE[cat_stand_face_to_right], pos1);
}
void create_cat() {
	CAT.set(1, 4, 15, 13);
}
void create_fish() {
	FISH.set(44, 44, 16, 16);
}
void create_fish_1() {
	FISH_1.set(60, 60, 4 , 4);
}
void create_pupi() {
	PUPI.set(15, 20, 16, 16);
}
void create_background() {
	BACKGROUND.set(0, 0, WIDTH/5, WIDTH/5);
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w/5, 0, h/5);
	
	//保持物体比例
}


void myDisplay() {
	glClearColor(color::g[0], color::g[1], color::g[2], color::g[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BACKGROUND.draw(TEXTURE, TEXTURE[background]);
	CAT.draw(TEXTURE, TEXTURE[cat_texture_temp]);
	FISH.draw(TEXTURE, TEXTURE[fish]);
	PUPI.draw(TEXTURE, TEXTURE[pupi]);
	FISH_1.draw(TEXTURE, TEXTURE[fish]);
	
	glutSwapBuffers();
}

//依照w a s d 操作模式对给予本元件被用户在2d限制（矩形）空间内移动的权利

void character_control_2d(int x_min, int y_min, int x_max, int y_max, int speed) {
	if ((KEY_DOWN('w') || KEY_DOWN('W'))&&CAT.getPos()[5]<=y_max) {
		CAT.move(0, speed);
	}
	if ((KEY_DOWN('a') || KEY_DOWN('A'))&&CAT.getPos()[0]>=x_min) {
		cat_texture_temp = cat_stand_face_to_left;
		CAT.move(-speed, 0);
	}
	if ((KEY_DOWN('s') || KEY_DOWN('S'))&&CAT.getPos()[1]>=y_min) {
		CAT.move(0, -speed);
	}
	if ((KEY_DOWN('d') || KEY_DOWN('D'))&&CAT.getPos()[2]<=x_max) {
		cat_texture_temp = cat_stand_face_to_right;
		CAT.move(speed, 0);
	}
}
void myKeyBoardFunc_1(unsigned char key, int x, int y) {
	character_control_2d(0, 0, WIDTH / 5, HEIGHT / 5, cat_speed);
	glutPostRedisplay();
}

void init() {
	
	glClearColor(color::g[0], color::g[1], color::g[2], color::g[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0,HEIGHT);

	initTextures();
	
	create_background();
	create_fish_1();
	create_cat();
	create_fish();
	create_pupi();

	cat_texture_temp = cat_stand_face_to_right;
}

int main(int argc,char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("KettyCatt");
	
	init();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyBoardFunc_1);
	glutMainLoop();


	return 0;
}

float* normalizeColor(int Red, int Green, int Blue, int Alpha)
{
	float* p = new float[4];
	p[0] = (float)Red / (float)256;
	p[1] = (float)Green / (float)256;
	p[2] = (float)Blue / (float)256;
	p[3] = 0;
	return p;
}
