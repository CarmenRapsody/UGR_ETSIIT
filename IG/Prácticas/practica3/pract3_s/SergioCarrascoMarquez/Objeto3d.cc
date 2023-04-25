//Objeto3d.cc
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Objeto3d.h"

Objeto3d::Objeto3d(){}
void Objeto3d::Dibujar(){
	
	if(!chess){
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnable(GL_CULL_FACE);
		glPointSize(3);
 		glVertexPointer( 3, GL_FLOAT, 0, &vertices[0]);
		glPolygonMode(GL_FRONT_AND_BACK,modePolygon);
		glDrawElements(modeDraw,triangulos.size(),GL_UNSIGNED_INT,&triangulos[0]);
	}
	else{
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnable(GL_CULL_FACE);
		glPointSize(3);
 		glVertexPointer( 3, GL_FLOAT, 0, &vertices[0]);
 		glPolygonMode(GL_FRONT_AND_BACK,modePolygon);
 		for(int i = 0; i < triangulos.size()/3;i++){
	 		if(i%2 == 0){
 				glColor3f(0,0,15);
 			}
 			else{
 				glColor3f(0,0,0);
 			}
 			glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,&triangulos[i*3]);
 		}
	}
}
void Objeto3d::SetBoxSize(){
	//Busca la altura, el ancho y la profundidad maxima
	float xMax = vertices[0];
	float yMax = vertices[1];
	float zMax = vertices[2];

	float xMin = vertices[0];
	float yMin = vertices[1];
	float zMin = vertices[2];

	for(int i = 3; i < vertices.size()-3;i+=3){
		if(vertices[i] > xMax && UnusedVertex[i] == false){
			xMax = vertices[i];
		}
		else {
			if (vertices[i] < xMin && UnusedVertex[i] == false){
				xMin = vertices[i];
			}
		}
		
		if(vertices[i+1] > yMax && UnusedVertex[i] == false){
			yMax = vertices[i+1];
		}
		else{
			if(vertices[i+1] < yMin && UnusedVertex[i] == false){
				yMin = vertices[i+1]; 
			}
		}

		if(vertices[i+2] > zMax && UnusedVertex[i] == false){
			zMax = vertices[i+2];
		}
		else{
			if(vertices[i+2] < zMin && UnusedVertex[i] == false){
				zMin = vertices[i+2];
			}
		}
	}
	BoxSuperiorx = xMax;
	BoxSuperiory = yMax;
	BoxSuperiorz = zMax;

	BoxInferiorx = xMin;
	BoxInferiory = yMin;
	BoxInferiorz = zMin;
}
void Objeto3d::DeleteUnusedVertex(){
	UnusedVertex = new bool[vertices.size()];
	//Set all to true
	for(int i = 0; i < vertices.size(); i++){
		UnusedVertex[i] = true;
	}
	//Change when its used
	for(int i = 0; i < triangulos.size(); i++){
		UnusedVertex[triangulos[i]] = false;
	}
}

