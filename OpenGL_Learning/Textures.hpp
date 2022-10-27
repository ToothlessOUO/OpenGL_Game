#pragma once
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "stb_image.h"
#include "Game_Component.hpp"
class Textures {
public:
	struct tex_pos
	{
		float pos[8];
		//从左下角开始逆时针旋转
	};
	std::vector<GLuint> textures_ids;
	std::vector<std::string> textures_names;
	std::vector<tex_pos> textures_positons;
	
	bool addTextures(const std::vector<std::string> &fileNames, const std::vector<std::string>& texture_names) {
		int num = fileNames.size();
		if (num != texture_names.size()) {
			std::cerr << "The number of file names are unequal with the textures' names !";
			return false;
		}
		textures_ids.clear();
		textures_names.clear();
		textures_positons.clear();
		GLuint* texture=new GLuint[num];
		glGenTextures(num, texture);
		for (int flag = 0; flag < num;flag++) {
			glBindTexture(GL_TEXTURE_2D, texture[flag]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/

			int width, height, nrChannels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(fileNames[flag].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else {
				std::cout << "Failed to load texture!" << std::endl;
				return false;
			}
			stbi_image_free(data);
			textures_ids.push_back(texture[flag]);
			textures_names.push_back(texture_names[flag]);
			float pos[8] = { 0,0 ,1,0,1,1,0,1 };
			tex_pos t;
			for (int i = 0; i < 8; i++) {
				t.pos[i] = pos[i];
			}
			textures_positons.push_back(t);
		}
		return true;
	}
	//设置贴图坐标
	void setTexturePos(int target_texture_id, float* pos) {
		if (target_texture_id > textures_ids.size()) {
			std::cerr << "Can not find this texture!";
			return;
		}
		for (int i = 0; i < 8; i++) {
			if (pos[i] > 1 || pos[i] < 0) {
				std::cerr << "The number is our of range !" << std::endl;
				return;
			}
		}
		for (int i = 0; i < 8; i++) {
			textures_positons[target_texture_id].pos[i] = pos[i];
		}
	}
	//便利的贴图查找——依照贴图命名进行贴图查找
	int operator[](std::string Texture_Name) {
		for (int i = 0; i < textures_names.size(); i++) {
			if (textures_names[i] == Texture_Name) {
				return i;
			}
		}
	}
	void getTextureID(const GLuint &target,GLuint &gain_texture,tex_pos &t ) {
		gain_texture = textures_ids[target];
		t = textures_positons[target];
	}
};