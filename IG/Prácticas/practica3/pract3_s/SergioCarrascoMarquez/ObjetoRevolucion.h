//ObjetoRevolucion.h
#ifndef OBJETO_REVOLUCION
#define OBJETO_REVOLUCION
#include <vector>
#include "Objeto3d.h"
#include "ObjetoPLY.h"
class ObjetoRevolucion:public ObjetoPLY{
private:
	//std::vector<float> verticesRevolucion;
	int RingSize; 
	int originalSize;
	bool CoverUp;
	bool CoverDown;
	bool CoverUpCreated;
	bool CoverDownCreated; 
	int sizeRevol;
	std::vector<float> v;
	std::vector<float> pointUp;
	std::vector<float> pointDown;
	bool NReverse;
public:
	ObjetoRevolucion(){
		CoverDownCreated = false;
		CoverUpCreated = false;
		RingSize = 0;
		NReverse = false;
	}
	ObjetoRevolucion(std::vector<float> v);
	void InitVertices(std::vector<float> v);
	void Revolucionar();
	void InitFaces();
	void InitObjeto();
	void SetCoverUp();
	void SetCoverDown();
	void SetRingSize(int s){RingSize = s;}
	void MulRingSize(){RingSize = RingSize *2;Revolucionar();InitFaces();}
	void CreateCover();
	void CreateCoverSup();
	void CreateCoverInf();
	void InitFromVector(std::vector<float> v);
	void GetNVer(){std::cout << vertices.size();}
	void Reverse();
	bool NeedReverse();
};
#endif