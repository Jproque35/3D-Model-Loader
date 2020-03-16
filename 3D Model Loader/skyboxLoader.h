#ifndef SKYBOXLOADER_H
#define SKYBOXLOADER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <SOIL/SOIL.h>
#include <math.h>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>

class skyboxLoader {

	private:
		GLuint tex_id[6];

	public:
		skyboxLoader();
		~skyboxLoader();

		void loadTextures();
		void draw();

};

#endif /* SKYBOXLOADER_H */