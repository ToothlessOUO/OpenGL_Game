#include <GL/glut.h>
#include <cmath>
#include "stb_image.h"
#include <iostream>
#include <string>
#include "Game_Component.hpp"
#include "Textures.hpp"

//识别按键是否被按下
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

static const int WIDTH = 1280, HEIGHT = 800;
////Cat
//static const std::string Cat_Texture= "C:/Users/xiewu/Desktop/学校相关/计算机图形学/Asserts/cat_15_13.png";
//static const std::string cat_texture_stand_face_to_left = "cat_stand";
//static const std::string cat_texture_stand_face_to_right = "cat_stand_1";
//static const float cat_speed =3.0f;
// Game_Part cat;
////Ground
//static const std::string ground_texture = "C:/Users/xiewu/Desktop/学校相关/计算机图形学/Asserts/ground_64_4.png";
//static const std::string GROUND= "ground";
//Game_Part ground;
////Fish
// static const std::string fish_texture=R"(C:\Users\xiewu\Desktop\学校相关\计算机图形学\Asserts\fish_15_16.png)";
// static const std::string FISH = "fish";
// Game_Part fish;

float* normalizeColor(int Red, int Green, int Blue, int Alpha);
namespace color {
	float* g = normalizeColor(235, 231, 235, 0);//底色
	float* p = normalizeColor(221, 109, 80, 0);//副色
	float* b = normalizeColor(146, 32, 22, 0);//主色
}

//void Create_cat() {
//	cat .set(1, 4, 15, 13);
//	cat.addATexture(Cat_Texture, cat_texture_stand_face_to_left);
//	cat.addATexture(Cat_Texture, cat_texture_stand_face_to_right);
//	float pos[8] = { 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f };
//	cat.setTexturePos(cat[cat_texture_stand_face_to_right], pos);
//	cat.setTargetTexture(cat[cat_texture_stand_face_to_right]);
//}
//void Create_ground() {
//	ground.set(0, 0, 64, 64);
//	ground.addATexture(ground_texture, GROUND);
//	ground.setTargetTexture(ground[GROUND]);
//}
//void Create_fish() {
//	fish.set(4, 4, 15, 16);
//	fish.addATexture(fish_texture, FISH);
//	fish.setTargetTexture(fish[FISH]);
//}
Textures TEXTURE;

Game_Component CAT;
static const string cat_texture_file = R"(C:\Users\xiewu\Desktop\学校相关\计算机图形学\Asserts\cat_15_13.png)";
static const string cat_stand_face_to_right = "C1";
static const string cat_stand_face_to_left = "C2";

//多贴图对象需要拥有临时贴图变量
string cat_texture_temp;
//可操控物件需要设置运动速度
static const float cat_speed = 3.0f;

Game_Component FISH;
Game_Component FISH_1;
static const string fish_texture_file = R"(C:\Users\xiewu\Desktop\学校相关\计算机图形学\Asserts\fish_16_16.png)";
static const string fish = "F";

Game_Component PUPI;
static const string pupi_texture_file = R"(C:\Users\xiewu\Desktop\学校相关\计算机图形学\Asserts\pipe_16_16.png)";
static const string pupi = "P";

Game_Component BACKGROUND;
static const string background_texture_file = R"(C:\Users\xiewu\Desktop\学校相关\计算机图形学\Asserts\QQ截图20221026134331.png)";
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
	gluOrtho2D(0, w/5, 0, h/5);//保持物体比例
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

//void myKeyBoardFunc(unsigned char key, int x, int y) {
//	switch (key)
//	{
//	case 'A':
//	case 'a':
//		if (CAT.getPos()[0] <= 0) {
//			break;
//		}
//		cat_texture_temp=cat_stand_face_to_left;
//		CAT.move(-cat_speed, 0);
//		break;
//	case 'D':
//	case 'd':
//		if (CAT.getPos()[2] >= WIDTH/5) {
//			break;
//		}
//		cat_texture_temp=cat_stand_face_to_right;
//		CAT.move(cat_speed, 0);
//		break;
//	case 'w':
//	case 'W':
//		if (CAT.getPos()[5] >= HEIGHT/5) {
//			break;
//		}
//		CAT.move(0, cat_speed);
//		break;
//	case 's':
//	case 'S':
//		if (CAT.getPos()[1] <= 0) {
//			break;
//		}
//		CAT.move(0, -cat_speed);
//		break;
//		
//	default:
//		break;
//	}
//	glutPostRedisplay(); //重新执行myDisplay方法
//}
//void handleKeypress(unsigned char key, int x, int y)
//{
//	if (key == 'w')
//	{
//		for (int i = 0; i < 12; i++)
//		{
//			if (i == 1 || i == 7 || i == 10 || i == 4)
//			{
//				CAT.move(0, 1);
//			}
//		}
//		glutPostRedisplay();
//	}
//	if (key == 'd')
//	{
//		for (int i = 0; i < 12; i++)
//		{
//			if (i == 0 || i % 3 == 0)
//			{
//				CAT.move(1, 0);
//			}
//		}
//		glutPostRedisplay();
//	}
//	if (key == 's')
//	{
//		for (int i = 0; i < 12; i++)
//		{
//			if (i == 1 || i == 7 || i == 10 || i == 4)
//			{
//				CAT.move(0, -1);
//			}
//		}
//		glutPostRedisplay();
//	}
//	if (key == 'a')
//	{
//		for (int i = 0; i < 12; i++)
//		{
//			if (i == 0 || i % 3 == 0)
//			{
//				CAT.move(-1, 0);
//			}
//		}
//		glutPostRedisplay();
//	}
//}

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
