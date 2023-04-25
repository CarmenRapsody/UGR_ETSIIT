//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD,SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );


void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
void    draw_seleccion(int r, int g, int b);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

//bool para indicar si se han calculado las normales
bool b_normales_caras;
bool b_normales_vertices;

//caracteristica para definir como se va a hacer
_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1); //num1: numero de lados

vector<_vertex3f> perfil;
int num;
};

//*************************************************************************
// clase objeto cilindro
//*************************************************************************

class _cilindro: public _triangulos3D
{
public:

  // if{
  //    tapas == 1 -> tapa superior
  //    tapas == 2 -> tapa inferior
  //    tapas == 3 -> ambas tapas
  // }
  // else{
  //    no hay tapas
  // }

  _cilindro(float r=1, float h=1, int n=20, int tapas=3);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  int tapas;
};

//*************************************************************************
// clase objeto cono
//*************************************************************************

class _cono: public _triangulos3D
{
public:

  // tapas = true -> tapa activada
  // tapas = false -> tapa desactivada

  _cono(float r=1.0, float h=1, int n=20, bool tapas=true);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  bool tapas;
};

//************************************************************************
// clase objeto esfera
//************************************************************************

class _esfera: public _triangulos3D
{
public:

  // if{
  //    tapas == 1 -> tapa superior
  //    tapas == 2 -> tapa inferior
  //    tapas == 3 -> ambas tapas
  // }
  // else{
  //    no hay tapas
  // }

  _esfera(float r=1, int lat=6, int lon=6, int tapas=3);
  void  rotacion();

  //añadir metodo para calcular la normal

  vector<_vertex3f> perfil;
  int num;
  int tapas;
};


//************************************************************************
// Articulado
//************************************************************************

class _columna: public _triangulos3D
{
public:
       _columna();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;


protected:
_rotacion  rodamiento;

};

/* escalera      */
class _escalera: public _triangulos3D
{
public:
       _escalera();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;


};


/* techo    */
class _techo: public _triangulos3D
{
public:
       _techo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_piramide techo;


};

//************************************************************************

class _pantenon: public _triangulos3D
{
public:
       _pantenon();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void    seleccion();

float giro_techo;
float giro_columna;

float giro_techo_min;
float giro_techo_max;

float sube_techo;
float sube_techo_min;
float sube_techo_max;

float sube_escal;
float sube_escal_min;
float sube_escal_max;

//pr5
float  color_pick[3];
int    color_selec[3][3];
int    activo[3];
int    piezas;


protected:
_escalera  escalera;
_columna   columna;
_techo     techo;
};
