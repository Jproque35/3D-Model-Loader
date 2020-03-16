#ifndef MESHLOADER_H
#define MESHLOADER_H
#define GLEW_STATIC
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
/*
Struct containing x,y, z coords and normal vector information
*/
typedef struct {

	float x;
	float y;
	float z;
	float normVect[4];
}
Vertex;

/*
Struct containing indices of face vertices
*/
typedef struct {

	int a;
	int b;
	int c;
	float normVect[3];

}
Face;


class meshLoader {

	private:
		vector<Vertex> verts;
		vector<Face> faces;
		float ymax;
		float xmin;
		float ymin;
		float xmax;
		float xTot;
		float yTot;
		GLuint tex_id;
		GLuint env_id;
		
		void parseLine(char * str);
		void calculateVectorNormals();
		void calculateFaceNormal(Vertex v1, Vertex v2, Vertex v3, float * arr);

	public:
		meshLoader();
		~meshLoader();

		void parseFile(const char * filename);
		void loadTexture();
		void draw();

};

#endif /* MESHLOADER_H */
