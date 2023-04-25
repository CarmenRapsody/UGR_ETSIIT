//Objeto3d.h
#ifndef OBJETO3D
#define OBJETO3D
#include <vector>
#include <cmath>
#include <iostream>
//#include "file_ply_stl.h"

typedef GLfloat Vertice[3];

class Objeto3d{
	protected:
		std::vector<GLfloat> vertices;
		std::vector<GLuint> triangulos;
		//Vector de triangulos
		int nTriangulos;
		int nVertices;
		GLenum modeDraw;
		GLenum modePolygon;
		bool chess;
		bool CullFace;
		bool Drawable;
		float BoxSuperiorx,BoxSuperiory,BoxSuperiorz;
		float BoxInferiorx,BoxInferiory,BoxInferiorz;
		float centerX,centerY,centerZ;
		bool *UnusedVertex;
	public:
		Objeto3d();
		void Dibujar();
		void SetMode(GLenum m){modeDraw = m;}
		void SetModePolygon(GLenum m){modePolygon = m;}
		void ChangeChess(){chess = !chess;}
		void EnableGlCullFace(){CullFace = true;}
		void DisableGlCullFace(){CullFace = false;}
		void SetBoxSize();
		void Rescale(float x){
      		for(int i = 0; i < vertices.size(); i++){
        		vertices[i] = vertices[i] * x;
        	}
      	}
      	void AutoRescale(){
      		SetBoxSize();
      		float longitud;
      		float termino1,termino2,termino3;
      		termino1 = pow(BoxSuperiorx-BoxInferiorx,2);
      		termino2 = pow(BoxSuperiory-BoxInferiory,2);
      		termino3 = pow(BoxSuperiorz-BoxInferiorz,2);
      		float suma = termino1+termino2+termino3;
      		longitud = sqrt(suma);
      		Rescale(50.0/longitud);
      	}
      	void SetDrawable(){
      		Drawable = !Drawable;
      	}
      	void SetCenter(){
      		SetBoxSize();
      		centerX = (BoxSuperiorx+BoxInferiorx)/2;
      		centerY = (BoxSuperiory+BoxInferiory)/2;
      		centerZ = (BoxSuperiorz+BoxInferiorz)/2;
      	}
      	float getCenterx(){return centerX;}
      	float getCentery(){return centerY;}
      	float getCenterz(){return centerZ;}
      	void DeleteUnusedVertex();
      	float GetBoxSX(){return BoxSuperiorx;}
      	float GetBoxSY(){return BoxSuperiory;}
      	float GetBoxSZ(){return BoxSuperiorz;}
      	float GetBozIX(){return BoxInferiorx;}
      	float GetBoxIY(){return BoxInferiory;}
      	float GetBoxIZ(){return BoxInferiorz;}
            void DibujaLineasYSolido(float rf,float gf,float bf, float rl, float gl, float bl){
                  glPushMatrix();
                        glPushMatrix();
                              glColor3f(rf,gf,bf);
                              SetMode(GL_TRIANGLES);
                              Dibujar();
                        glPopMatrix();
                        glPushMatrix();
                              glColor3f(rl,gl,bl);
                              SetMode(GL_LINES);
                              Dibujar();
                        glPopMatrix();
                  glPopMatrix();
            }
};
#endif
