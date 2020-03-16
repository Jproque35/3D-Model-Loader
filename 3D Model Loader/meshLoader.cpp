#include "meshLoader.h"

/*
Constructor. Sets values to default 0.0
*/
meshLoader::meshLoader() {
	ymax = 0.0;
	xmax = 0.0;
	xmin = 0.0;
	ymin = 0.0;
	xTot = 0.0;
	yTot = 0.0;
}

meshLoader::~meshLoader() {
	
}

/*
Parse a given model file
*/
void meshLoader::parseFile(const char * filename) {
	//Open file
	fstream f;
	f.open(filename);

	if (f.is_open()) {

		//If not at end of file, parse it
		while (!f.eof()) {

			char temp[256];

			f.getline(temp, 256);
			parseLine(temp);

		}

	}

	f.close();

	calculateVectorNormals();

	//Values for use when applying texture coordinates
	xTot = abs(xmax) + abs(xmin);
	yTot = abs(ymax) + abs(ymin);

}

/*
Parse a single line accordingly
*/
void meshLoader::parseLine(char * str) {

	if (strlen(str) == 0)
		return;

	//Determine if line involves face or vertex
	if ( str[0] == 'v' ) {

		verts.push_back(Vertex());

		//Retrieve our desired coordinates
		sscanf(str, "v %f %f %f", &verts.back().x, &verts.back().y, &verts.back().z);

		for (int i = 0; i < 4; i++) 
			verts.back().normVect[i] = 0.0;

		//Gather relevant minimum/maximum coordinate data
		if (verts.back().y > ymax)
			ymax = verts.back().y;
		else if (verts.back().y < ymin)
			ymin = verts.back().y;

		if (verts.back().x > xmax)
			xmax = verts.back().x;
		else if (verts.back().x < xmin)
			xmin = verts.back().x;

	} else if ( str[0] == 'f' ) {

		faces.push_back(Face());

		//Retrieve our desired vertices
		sscanf(str, "f %i %i %i", &faces.back().a, &faces.back().b, &faces.back().c);

	}

}

/*
Calculate vertex normals
*/
void meshLoader::calculateVectorNormals() {

	//Go through all the faces
	for (int i = 0; i < faces.size(); i++) {

		int vert1 = faces[i].a - 1;
		int vert2 = faces[i].b - 1;
		int vert3 = faces[i].c - 1;

		//Calculate face normal to get relevant data
		calculateFaceNormal(verts[vert1], verts[vert2], verts[vert3], faces[i].normVect);

		//Add face normal vector to vectors
		for (int j = 0; j < 3; j++) {
			verts[vert1].normVect[j] += faces[i].normVect[j];
			verts[vert2].normVect[j] += faces[i].normVect[j];
			verts[vert3].normVect[j] += faces[i].normVect[j];
		}

	}

	//Normalize our normal vectors
	for (int i = 0; i < verts.size(); i++) {

		float a = verts[i].normVect[0];
		float b = verts[i].normVect[1];
		float c = verts[i].normVect[2];

		float length = sqrt(a * a + b * b + c * c);

		verts[i].normVect[0] /= length;
		verts[i].normVect[1] /= length;
		verts[i].normVect[2] /= length;

	}

}

/*
Cal;culate our face normal by performing a cross product and normalizing it
*/
void meshLoader::calculateFaceNormal(Vertex v1, Vertex v2, Vertex v3, float * arr) {
	float Qx = v2.x - v1.x;
	float Qy = v2.y - v1.y;
	float Qz = v2.z - v1.z;
	float Px = v3.x - v1.x;
	float Py = v3.y - v1.y;
	float Pz = v3.z - v1.z;

	float desire[] = { Py*Qz - Pz*Qy, Pz*Qx - Px*Qz, Px*Qy - Py*Qx };

	float length = abs( sqrt(((Py*Qz - Pz*Qy) * (Py*Qz - Pz*Qy)) + ((Pz*Qx - Px*Qz) * (Pz*Qx - Px*Qz)) + ((Px*Qy - Py*Qx) * (Px*Qy - Py*Qx))) );

	arr[0] = desire[0]/length;
	arr[1] = desire[1]/length;
	arr[2] = desire[2]/length;
}

/*
Load our environment and texture
*/
void meshLoader::loadTexture() {

	//Load image file and bind it
	tex_id = SOIL_load_OGL_texture
		(
		"rock.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	env_id = SOIL_load_OGL_texture
		(
		"cm_back.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	
	//For Reflection Map
	
	/*
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	*/
	//For Texture
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

/*
Draw our teapot 
*/
void meshLoader::draw() {

	//For Reflection Map
	
	/*
	glBindTexture(GL_TEXTURE_2D, env_id);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_T);
	*/
	//For Texture
	glBindTexture(GL_TEXTURE_2D, tex_id);

	//Code below for GLEW; not implemented
	//glBindTexture(GL_TEXTURE_2D, env_id);
	//glActiveTexture(GL_TEXTURE0);
	/*
	//glEnable(GL_TEXTURE_2D);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	*/

	//glActiveTexture(GL_TEXTURE1);
	//glEnable(GL_TEXTURE_2D);

	//Draw our faces
	glBegin(GL_TRIANGLES);
	
	
	for (unsigned int i = 0; i < faces.size(); i++) {

		int vert1 = faces[i].a - 1;
		int vert2 = faces[i].b - 1;
		int vert3 = faces[i].c - 1;

		glNormal3f( -verts[vert1].normVect[0], -verts[vert1].normVect[1], -verts[vert1].normVect[2] );
		glTexCoord2f((verts[vert1].x + abs(xmin)) / xTot, (verts[vert1].y + abs(ymin)) / yTot);
		glVertex3f(verts[vert1].x, verts[vert1].y, verts[vert1].z);

		glNormal3f( -verts[vert2].normVect[0], -verts[vert2].normVect[1], -verts[vert2].normVect[2] );
		glTexCoord2f((verts[vert2].x + abs(xmin)) / xTot, (verts[vert2].y + abs(ymin)) / yTot);
		glVertex3f(verts[vert2].x, verts[vert2].y, verts[vert2].z);

		glNormal3f( -verts[vert3].normVect[0], -verts[vert3].normVect[1], -verts[vert3].normVect[2] );
		glTexCoord2f((verts[vert3].x + abs(xmin)) / xTot, (verts[vert3].y + abs(ymin)) / yTot);
		glVertex3f(verts[vert3].x, verts[vert3].y, verts[vert3].z);

		float arr[3];

		calculateFaceNormal(verts[vert1], verts[vert2], verts[vert3], arr);

		glNormal3fv(arr);

	}

	glEnd();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_T);

	//More code for GLEW below
	//glActiveTexture(GL_TEXTURE0);
	/*
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	*/
	//glActiveTexture(GL_TEXTURE1);
	//glDisable(GL_TEXTURE_2D);


}



