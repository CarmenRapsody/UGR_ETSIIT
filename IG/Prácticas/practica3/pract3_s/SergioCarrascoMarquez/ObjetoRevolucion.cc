//ObjetoRevolucion.cc
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "ObjetoRevolucion.h"
#include <cmath>
#define PI 3.14159265358979323846
#define FACTOR PI/180

ObjetoRevolucion::ObjetoRevolucion(std::vector<float> v){
	vertices = v;
}
void ObjetoRevolucion::InitVertices(std::vector<float> v){
	vertices = v;
	originalSize = vertices.size();
}
void ObjetoRevolucion::Revolucionar(){
	//Dada una lista de vertices se crean el resto de vertices del objeto
	//Se añaden vertices nuevos a la lista de vertices cada 360/RingSize grados
	//La componenete y no se modifica, solo la x y la z
	SetCoverUp();
	SetCoverDown();
	//Para cada punto
	/*
	if(v.size() == 0){
		v = vertices;
	}
	*/
	NeedReverse();
	v = vertices;
	vertices.clear();
	originalSize = v.size();
	for(int i = 0; i < originalSize/3 ; i++){
		//Añadir a la lista un nuevo vertice para formar el un anillo
		bool CanCopy = true;
		if(CoverUp && i == 0){
			CanCopy = false;
		}
		else{
			if(CoverDown && i == (originalSize/3-1)){
				CanCopy = false;
			}
		}
		if(CanCopy){
			vertices.push_back(v[3*i]);
			vertices.push_back(v[3*i+1]);
			vertices.push_back(v[3*i+2]);
			float gradoInicial;
			int pos = i*3; //Posicion de la componente x del vertice en el vector
			float DistaciaEje;

			DistaciaEje = sqrt(pow (v[pos],2)+pow(v[pos+2],2));
			//gradoInicial = asin(vertices[pos+2]/DistaciaEje);
			gradoInicial = asin(vertices[2]/DistaciaEje);
			for(int j = 0; j < RingSize-1; j++){
				float grad = (j+1)*2*PI/RingSize + gradoInicial;
				//Añadir la nueva x
				vertices.push_back(DistaciaEje*cos(grad));
				//Añadir la nueva y
				vertices.push_back(v[pos+1]);
				//Añadir la nueva z
				vertices.push_back(DistaciaEje*sin(grad));
			}
		}	
	}

	//Añadir los vertices del centro al final si es necesario
	if(CoverUp){
		/*
		vertices.push_back(v[0]);
		vertices.push_back(v[1]);
		vertices.push_back(v[2]);
		*/
		pointUp.push_back(v[0]);
		pointUp.push_back(v[1]);
		pointUp.push_back(v[2]);
		originalSize = originalSize-3;

	}
	if(CoverDown){
		/*
		vertices.push_back(v[v.size()-3]);
		vertices.push_back(v[v.size()-2]);
		vertices.push_back(v[v.size()-1]);
		*/
		pointDown.push_back(v[v.size()-3]);
		pointDown.push_back(v[v.size()-2]);
		pointDown.push_back(v[v.size()-1]);
		originalSize = originalSize-3;
	}
	sizeRevol = vertices.size();
} 
void ObjetoRevolucion::InitFaces(){
	triangulos.clear();
	std::cout << "el need reverse da " <<NReverse;
	for(int i = 0; i < (originalSize/3)-1; i++){
		int indiceAnilloSup = i*3*(RingSize);
		int indiceAnilloInf = indiceAnilloSup + 3*(RingSize);
		
		
		for(int j = 0; j < RingSize-1; j++){
			//Triangulo 1
			if(!NReverse){
				triangulos.push_back(((indiceAnilloSup/3)+j));
				triangulos.push_back(((indiceAnilloInf/3)+j));
				triangulos.push_back(((indiceAnilloInf/3)+((j+1))));
				//triangulo 2
				triangulos.push_back(((indiceAnilloSup/3)+(j)));
				triangulos.push_back(((indiceAnilloInf/3)+(j+1)));
				triangulos.push_back(((indiceAnilloSup/3)+(j+1)));
			}
			else{
				triangulos.push_back(((indiceAnilloInf/3)+j));
				triangulos.push_back(((indiceAnilloSup/3)+j));
				triangulos.push_back(((indiceAnilloInf/3)+((j+1))));
				//triangulo 2
				triangulos.push_back(((indiceAnilloInf/3)+(j+1)));
				triangulos.push_back(((indiceAnilloSup/3)+(j)));
				triangulos.push_back(((indiceAnilloSup/3)+(j+1)));
			}
			
		}
	}
	//Es necesario cerrar las caras, es decir crear caras entre el primer y ultimo elemento del anillo
	
	for(int i = 0; i < (originalSize/3)-1; i++){
		if(!NReverse){
			//triangulo 1
			triangulos.push_back(i*RingSize);
			triangulos.push_back(RingSize*(i)+RingSize-1);
			triangulos.push_back(RingSize*(i+1)+RingSize-1);
		
			//trinagulo 2
			triangulos.push_back(i*RingSize);
			triangulos.push_back(RingSize*(i+1)+RingSize-1);
			triangulos.push_back((i+1)*RingSize);
		}
		else{
			//triangulo 1
			triangulos.push_back(RingSize*(i)+RingSize-1);
			triangulos.push_back(i*RingSize);
			triangulos.push_back(RingSize*(i+1)+RingSize-1);
		
			//trinagulo 2
			triangulos.push_back(RingSize*(i+1)+RingSize-1);
			triangulos.push_back(i*RingSize);
			triangulos.push_back((i+1)*RingSize);
		}
	}
}
void ObjetoRevolucion::InitObjeto(){
	InitFigure();
	Revolucionar();
	InitFaces();
}
void ObjetoRevolucion::InitFromVector(std::vector<float> v){
	InitVertices(v);
	Revolucionar();
	InitFaces();
}
void ObjetoRevolucion::SetCoverUp(){
	if(vertices[0] == 0 && vertices[2] == 0){
		CoverUp = true;
	}
}
void ObjetoRevolucion::SetCoverDown(){
	if(vertices[vertices.size()-1] == 0 && vertices[vertices.size()-3] == 0){
		CoverDown = true;
	}
}
void ObjetoRevolucion::CreateCover(){
	CreateCoverInf();
	CreateCoverSup();

}
void ObjetoRevolucion::CreateCoverSup(){
	if(!CoverUpCreated){
		//Crear el vertice central
		//CoverUp = true;
		if(!CoverUp){
			vertices.push_back(0);
			vertices.push_back(vertices[1]);
			vertices.push_back(0);
		}
		else{
			vertices.push_back(pointUp[0]);
			vertices.push_back(pointUp[1]);
			vertices.push_back(pointUp[2]);
		}
		//Crear los triangulos
		for(int i = 0; i < RingSize-1; i++){
			if(NReverse){
				std::cout<<"necesita el Nreverse\n";
				
				triangulos.push_back(i+1);
				triangulos.push_back(i);
				triangulos.push_back(vertices.size()/3-1);
			}
			else{
				std::cout<<"No necesita el Nreverse\n";
				triangulos.push_back(i+1);
				triangulos.push_back(vertices.size()/3-1);
				triangulos.push_back(i);
			}
			
		}
		if(!NReverse){
			triangulos.push_back(RingSize-1);
			triangulos.push_back(0);
			triangulos.push_back(vertices.size()/3-1);
			CoverUpCreated = true;
		}
		else{
			triangulos.push_back(0);
			triangulos.push_back(RingSize-1);
			triangulos.push_back(vertices.size()/3-1);
			CoverUpCreated = true;
		}
		
	}
}
void ObjetoRevolucion::CreateCoverInf(){
	if(!CoverDownCreated){
		std::cout << "El cover vale " << CoverDown;
		if(!CoverDown){
			vertices.push_back(0);
			vertices.push_back(vertices[sizeRevol-2]);
			vertices.push_back(0);
		}
		else{
			vertices.push_back(pointDown[0]);
			vertices.push_back(pointDown[1]);
			vertices.push_back(pointDown[2]);
		}
		for(int i = 0; i < RingSize-1; i++){
			if(!NReverse){
				triangulos.push_back(sizeRevol/3-1-i);
				triangulos.push_back(sizeRevol/3-2-i);
				triangulos.push_back(vertices.size()/3-1);
			}
			else{
				triangulos.push_back(sizeRevol/3-2-i);
				triangulos.push_back(sizeRevol/3-1-i);
				triangulos.push_back(vertices.size()/3-1);
			}
			
		}
		if(!NReverse){
			triangulos.push_back(sizeRevol/3-RingSize);
			triangulos.push_back(sizeRevol/3-1);
			triangulos.push_back(vertices.size()/3-1);
			CoverDownCreated = true;
		}
		else{
			triangulos.push_back(sizeRevol/3-1);
			triangulos.push_back(sizeRevol/3-RingSize);
			triangulos.push_back(vertices.size()/3-1);
			CoverDownCreated = true;
		}
		
	}
}
bool ObjetoRevolucion::NeedReverse(){
	if(vertices[1] > vertices[vertices.size()-2]){
		NReverse =  true;
	}
	else{
		NReverse = false;
	}
	
	
}
void ObjetoRevolucion::Reverse(){
	unsigned int tmp;
	for(int i = 0; i < vertices.size()/2; i++){
		tmp = triangulos[i];
		triangulos[i] = triangulos[triangulos.size()-1-i];
		triangulos[triangulos.size()-1-i] = tmp;
	}
}
