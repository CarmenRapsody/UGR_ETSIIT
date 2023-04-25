//ObjetoPLY.h
#ifndef OBJETO_PLY
#define OBJETO_PLY
#include "Objeto3d.h"
#include "file_ply_stl.h"
#include <iostream>

class ObjetoPLY:public Objeto3d{
  private:
    char* PLYfilename;
    _file_ply reader;
  public:
    ObjetoPLY(){}
    ObjetoPLY(char* PLYfilename);
    void setPLYfilename(char* PLYfilename);//Cambia el archivo PLY del que se va a leer la figura
    void InitFigure();//Inicializa los vectores de triangulos y de indice con los dados en PLYfilename
    void ShowVertex(){
    	for(int i = 0; i < triangulos.size(); i++){
        	std::cout << triangulos[i] << "\n";
    	}
    }
};

#endif
