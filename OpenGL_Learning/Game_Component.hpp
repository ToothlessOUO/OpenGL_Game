#pragma once
#include <GL/glut.h>//若出错请自行索引
#include <vector>
#include <string>
#include "stb_image.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Textures.hpp"

//********使用说明***********
//1.利用构造函数初始化位置及大小
//2.利用 addATexture 给目标添加贴图
//3.利用 setTexturePos设置该贴图纹理坐标
//3.根据需要调用 move rotate zoom三个方法
//4.使用 Draw方法开画！

//注：部分注释为实现方法，请自己分辨

class Game_Component {
	//从左下角开始逆时针旋转
	GLint pos[8];


	int current_texture;

	//初始化矩阵:(以一维数组表述矩阵)
	//a[n*k]={11,12......1k , 21, 22......2k , 31,32.........................nk} 
	// 平移矩阵int T[9]={1,0,dx,0,1,dy,0,0,1};      n=3   k=3
	// 旋转矩阵int R[9]={c,-s,0,s,c,0,0,0,1};         n=3    k=3      (以原点为旋转中心）[ c=cos(angle) , s=sin(angle) ] 
	// 缩放矩阵int S[9]={sx,0,0,0,sy,0,0,0,1};		  n=3	k=3
	// 点·原矩阵int P[3]={x,y,1};    k=3    m=1

	//matrixA[n*k] * matrixB[k*m]
	//本程序中 返回矩阵为3*1阵 newX=p[1][1]    newY=p[2][1]
	int** MultiplyMatrix(int a[], int b[], int n, int k, int m) {
		int** c = new int* [n];
		for (int i = 0; i < n; i++) {
			c[i] = new int[m];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				c[i][j] = 0;
				for (int v = 0; v < k; v++) {
					c[i][j] += a[i * k + v] * b[v * m + j];
				}
			}
		}
		return c;
	}

public:
	Game_Component(int x = 0, int y = 0, int width = 0, int height = 0) {
		set(x, y, width, height);
		current_texture = 0;
	}

	//(x,y)为矩形左下角
	//(x1,y1)=(x,y) ; (x2,y2)=(x+width,y) ; (x3,y3)=(x+width,y+height) ; (x4,y4)=(x,y+height)
	//set :: 强制更新
	void set(int x, int y, int width, int height) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = x + width;
		pos[3] = y;
		pos[4] = x + width;
		pos[5] = y + height;
		pos[6] = x;
		pos[7] = y + height;
	}

	//获取几何中心
	void getCenter(int& center_x, int& center_y) {
		center_x = (pos[0] + pos[4]) / 2;
		center_y = (pos[1] + pos[5]) / 2;
	}
	//移动 dx dy为对应轴该变量
	void move(int dx, int dy) {
		for (int i = 0; i < 8; i++) {
			int T[9] = { 1,0,dx,0,1,dy,0,0,1 };
			int k = i + 1;
			int P[3] = { pos[i],pos[k],1 };
			int** newP = MultiplyMatrix(T, P, 3, 3, 1);
			pos[i] = newP[0][0];
			pos[k] = newP[1][0];
			i = k;
		}
	}
	//先把<旋转中心>移到原点，旋转完毕再移动回去———move(-center_x,-center_y)——>旋转——>move(center_x,center_y)
	void rotate(double angle_弧度制, int center_x = 0, int center_y = 0) {
		double c = std::cos(angle_弧度制);
		double s = std::sin(angle_弧度制);
		move(-center_x, -center_y);
		for (int i = 0; i < 8; i++) {
			int R[9] = { c,-s,0,s,c,0,0,0,1 };
			int k = i + 1;
			int P[3] = { pos[i],pos[k],1 };
			int** newP = MultiplyMatrix(R, P, 3, 3, 1);
			pos[i] = newP[0][0];
			pos[k] = newP[1][0];
			i = k;
		}
		move(center_x, center_y);
	}
	//sx：x方向缩放倍率   sy：y方向缩放倍率
	void zoom(int sx, int sy) {
		for (int i = 0; i < 8; i++) {
			int S[9] = { sx,0,0,0,sy,0,0,0,1 };
			int k = i + 1;
			int P[3] = { pos[i],pos[k],1 };
			int** newP = MultiplyMatrix(S, P, 3, 3, 1);
			pos[i] = newP[0][0];
			pos[k] = newP[1][0];
			i = k;
		}
	}
	//请调用Texture类中的setTexture
	//开画！
	void draw(Textures &TEX,const unsigned int &target) {
		GLuint texture;
		Textures::tex_pos t;
		TEX.getTextureID(target,texture, t);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);

		glBegin(GL_POLYGON);
		glTexCoord2f(t.pos[0], t.pos[1]);
		glVertex2f(pos[0], pos[1]);
		glTexCoord2f(t.pos[2], t.pos[3]);
		glVertex2f(pos[2], pos[3]);
		glTexCoord2f(t.pos[4], t.pos[5]);
		glVertex2f(pos[4], pos[5]);
		glTexCoord2f(t.pos[6], t.pos[7]);
		glVertex2f(pos[6], pos[7]);

		glEnd();
		glDisable(GL_TEXTURE_2D);	//禁止使用纹理
		//双缓存交换缓存以显示图像
		glutSwapBuffers();
	}
	GLint* getPos() {
		return pos;
	}
	bool isCross(Game_Component g) {
		int* p = g.getPos();
		if (std::max(p[0], pos[0]) <= std::min(p[4], pos[4]) && std::max(p[1], pos[1]) <= std::min(p[5], pos[5]))
			return true;
		else
			return false;
	}
};