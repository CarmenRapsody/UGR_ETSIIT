//ObjetoPLY.cc
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "ObjetoPLY.h"

ObjetoPLY::ObjetoPLY(char* PLYfilename){
  this->PLYfilename = PLYfilename;
}
void ObjetoPLY::InitFigure(){
	vertices.clear();
	triangulos.clear();
	reader.open(PLYfilename);
	reader.read(vertices,triangulos);
	DeleteUnusedVertex();
}
void ObjetoPLY::setPLYfilename(char* PLYfilename){
  this->PLYfilename = PLYfilename;
}
