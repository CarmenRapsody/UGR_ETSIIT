//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (unsigned int i=0; i<caras.size();i++)
	{
		if ( i %2 == 0 )
			glColor3f(r1,g1,b1);
		else glColor3f(r2,g2,b2);

		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{//codigo de la semana pasada
	vertices.resize(8);
	caras.resize(12);

//vertices

vertices[0].x=-tam;vertices[0].y=-tam;;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=-tam;;vertices[2].z=-tam;;
vertices[3].x=-tam;;vertices[3].y=-tam;;vertices[3].z=-tam;;
vertices[4].x=-tam;;vertices[4].y=tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;;
vertices[7].x=-tam;;vertices[7].y=tam;vertices[7].z=-tam;;

// triangulos
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=4;caras[1]._2=5;
caras[2]._0=1;caras[2]._1=6;caras[2]._2=5;
caras[3]._0=1;caras[3]._1=2;caras[3]._2=6;
caras[4]._0=2;caras[4]._1=7;caras[4]._2=3;
caras[5]._0=2;caras[5]._1=6;caras[5]._2=7;
caras[6]._0=3;caras[6]._1=7;caras[6]._2=0;
caras[7]._0=0;caras[7]._1=4;caras[7]._2=7;
caras[8]._0=7;caras[8]._1=4;caras[8]._2=6;
caras[9]._0=0;caras[9]._1=1;caras[9]._2=3;
caras[10]._0=3;caras[8]._1=4;caras[8]._2=5;



}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;// el 3 es de las tres coordenadas
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

for(int i =0; i<n_ver;i++)
{
	vertices[i].x=ver_ply[3*i];
	vertices[i].y=ver_ply[3*i+1];
	vertices[i].z=ver_ply[3*i+2];
}

caras.resize(n_car);
for(int i =0; i<n_car;i++)
{
	caras[i]._0=car_ply[3*i];
	caras[i]._1=car_ply[3*i+1];
	caras[i]._2=car_ply[3*i+2];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)//num numeros de lados
{
int i,j,c;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice
num_aux=perfil.size();
vertices.resize(num_aux*num+2);

for (j=0;j<num;j++)
  {
		for (i=0;i<num_aux;i++)
     {//para cada punto del perfil aplicamos una matriz de rotacion
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;//matriz de vertices
     }
  }

// tratamiento de las caras
//caras.resize(2*(num_aux-1)*num+num*2);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }


 // tapa inferior
if (fabs(perfil[0].x)>0.0)
{
	vertices[num_aux*num].x=0.0;
	vertices[num_aux*num].y=perfil[0].y; //perfil 0, para coger el primer punto del perfil
	vertices[num_aux*num].z=0.0;

	for(j=0;j<num; j++){
		cara_aux._0=num_aux*num;
		cara_aux._1=j*num_aux+0;
		cara_aux._2=((j+1)%num)*num_aux+0;
		caras.push_back(cara_aux);
	}

}

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
		vertices[num_aux*num+1].x=0.0; // +1 para coger el de arriba
		vertices[num_aux*num+1].y=perfil[num_aux-1].y; //num_aux-1 para coger el ultimo
		vertices[num_aux*num+1].z=0.0;         // punto del perfil

		for(j=0;j<num; j++){
			cara_aux._0=num_aux*num+1;
			cara_aux._1=j*num_aux+perfil.size()-1;
			cara_aux._2=((j+1)%num)*num_aux+perfil.size()-1;
			caras.push_back(cara_aux);
	}

 }
}


_cilindro::_cilindro(float r, float h, int n, int tapas){
	num = n;
	this->tapas = tapas;

	_vertex3f aux;
	aux.x=r; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=-h; aux.z=0.0;
	perfil.push_back(aux);
}

void _cilindro::rotacion()
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice
num_aux=perfil.size();	// número de vértices que tenemos en el perfil inicial
vertices.resize(num_aux*num);

for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }


// tratamiento de las caras
for (j=0;j<num;j++)
  {
		for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }


 // tapa superior
	if (fabs(perfil[0].x)>0.0 && (tapas == 1 || tapas == 3))
	{
		//punto central
		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=0; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=i;
			cara_aux._2=(i+2)%(vertices.size()-1);
			caras.push_back(cara_aux);
		}
	}

 // tapa inferior
	if (fabs(perfil[num_aux-1].x)>0.0 && (tapas == 2 || tapas == 3))
	{
		//punto central
		vertice_aux.x=0;
		vertice_aux.y=perfil[1].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=1; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=(i+2)%(vertices.size()-2);
			cara_aux._2=i;
			caras.push_back(cara_aux);
		}
	}
}

//************************************************************************
// objeto por revolucion CONO
//************************************************************************

_cono::_cono(float r, float h, int n, bool tapas){

	num = n;
	this->tapas = tapas;
	_vertex3f aux;

	aux.x=0.0; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=0.0; aux.z=0.0;
	perfil.push_back(aux);
}

void _cono::rotacion()
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice
num_aux=1;
vertices.resize(num_aux+num);

	vertices[0] = perfil[0];

	for (j=0;j<num;j++){
		vertice_aux.x=perfil[num_aux].x*cos(2.0*M_PI*j/(1.0*num))+
				                perfil[num_aux].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[num_aux].x*sin(2.0*M_PI*j/(1.0*num))+
				                perfil[num_aux].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[num_aux].y;
		vertices[num_aux+j]=vertice_aux;
	}

// tratamiento de las caras
	for (i=0;i<num-1;i++){
		cara_aux._0=0;
		cara_aux._1=i+1;
		cara_aux._2=(i+2)%(num+num_aux);
		caras.push_back(cara_aux);
	}

	cara_aux._0=0;
	cara_aux._1=num;
	cara_aux._2=1;
	caras.push_back(cara_aux);

 // tapa inferior
if (fabs(perfil[1].x)>0.0 && tapas){
	vertice_aux.x=0;
  vertice_aux.y=perfil[1].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

	for(i=0; i<num-1; i++){
		cara_aux._0=vertices.size()-1;
    cara_aux._1=i+2;
    cara_aux._2=i+1;
    caras.push_back(cara_aux);
	}
	//ultima cara
	cara_aux._0=vertices.size()-1;
  cara_aux._1=1;
  cara_aux._2=vertices.size()-2;
  caras.push_back(cara_aux);
  }
}

//************************************************************************
// objeto por revolucion ESFERA
//************************************************************************

_esfera::_esfera(float r, int lat, int lon, int tapas){

	num = lon;
	this->tapas = tapas;
	_vertex3f aux;

	float rad_incremento = M_PI/lat;
	float angulo = 0;

	aux.x=0.0; aux.y=r; aux.z=0.0;
	perfil.push_back(aux);

	for(int i=0; i < lat-1; ++i){
		angulo += rad_incremento;

		aux.x = r*sin(angulo);
		aux.y = r*cos(angulo);
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	aux.x=0.0; aux.y=-r; aux.z=0.0;
	perfil.push_back(aux);
}

void _esfera::rotacion()
{
	int i,j,k;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice
	num_aux=perfil.size();	// número de vértices que tenemos en el perfil inicial
	vertices.resize((perfil.size()-2)*num+2);

	vertices[vertices.size()-2] = perfil[0]; //punto superior
	vertices[vertices.size()-1] = perfil[perfil.size()-1]; //punto inferior

	k = 0;
	for (j=0;j<num;j++)
	{
		for (i=1;i<num_aux-1;i++)
		{
			vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
			            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
			vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
			            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
			vertice_aux.y=perfil[i].y;
			vertices[k]=vertice_aux;
			++k;
	    }
	 }

// tratamiento de las caras
	for (j=0;j<num;j++)
	{
		for (i=0;i<num_aux-3;i++)
		{
			cara_aux._0=i+((j+1)%num)*(num_aux-2);
			cara_aux._1=i+1+j*(num_aux-2);
			cara_aux._2=i+1+((j+1)%num)*(num_aux-2);
			caras.push_back(cara_aux);
			cara_aux._0=i+1+j*(num_aux-2);
			cara_aux._1=i+((j+1)%num)*(num_aux-2);
			cara_aux._2=i+j*(num_aux-2);
			caras.push_back(cara_aux);
		}
	}

 // tapa superior
	if (fabs(perfil[0].x)==0.0 && (tapas == 1 || tapas == 3))
	{ //primera cara
		cara_aux._0=vertices.size()-2;
		cara_aux._1=0;
		cara_aux._2=perfil.size()-2;
		caras.push_back(cara_aux);
		auto cara_aux_anterior = cara_aux;

		k = perfil.size()-2;
		for(int i=0; i<num-2; i++)
		{
			cara_aux._0 = vertices.size()-2;
			cara_aux._1 = cara_aux_anterior._1 + k;
			cara_aux._2 = cara_aux_anterior._2 + k;
			caras.push_back(cara_aux);
			cara_aux_anterior = cara_aux;
		}

		// ultima cara
		cara_aux._0=vertices.size()-2;
		cara_aux._1=cara_aux_anterior._1 + k;
		cara_aux._2=0;
		caras.push_back(cara_aux);
	}

 //tapa inferior
if (fabs(perfil[num_aux-1].x)==0.0 && (tapas == 2 || tapas == 3))
{ //primera cara
	cara_aux._0=vertices.size()-1;
	cara_aux._1=perfil.size()-3+perfil.size()-2;
	cara_aux._2=perfil.size()-3;
	caras.push_back(cara_aux);
	auto cara_aux_anterior = cara_aux;

	k = perfil.size()-2;
	for(int i=0; i<num-2; i++)
	{
		cara_aux._0 = vertices.size()-1;
		cara_aux._1 = cara_aux_anterior._1 + k;
		cara_aux._2 = cara_aux_anterior._2 + k;
		caras.push_back(cara_aux);
		cara_aux_anterior = cara_aux;
	}
	//ultima cara
	cara_aux._0=vertices.size()-1;
	cara_aux._1=perfil.size()-3;
	cara_aux._2=cara_aux_anterior._2 + k;
	caras.push_back(cara_aux);
 }
}


_columna::_columna()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12);
altura=0.22;

};

void _columna::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glTranslatef(-0.5,altura,0); //posicion en los ejes glTranslatef(x,y,z);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,altura,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,altura,0.5);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,altura,0.5);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,altura,-0.5);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,altura,-0.5);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //columna
glPopMatrix();
}

//************************************************************************
// 													Practica 3 
//************************************************************************

_escalera::_escalera()
{
altura=0.3;
anchura=1.0;
};

/*Implementacion de la escalera, pasos
		- glPushMatrix();
		- funciones que modifiquen la instancia
		- instancia.draw(...);
		- glPushMatrix();

*/
void _escalera::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0,-0.4,0); //posicion cuadrada con las columnas
glScalef(1.5,0.1,1.3);  //funcion para cambiar las dimensiones de la figura,  glScalef(anchura,altura,largura);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);//cubo, escalon 1		  									x,      y      z
glPopMatrix();

glPushMatrix();
glTranslatef(0,-0.5,0);
glScalef(1.7,0.1,1.5);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);  //cubo, escalon 2
glPopMatrix();

glPushMatrix();
glTranslatef(0,-0.6,0);
glScalef(1.9,0.1,1.7);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //cubo, escalon 3
glPopMatrix();



}

//************************************************************************


_techo::_techo()
{
altura=1.0;
anchura=1.75;
};

void _techo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.7,0.8,1.7);  //piramide dimensionada para que encaje con las columnas
techo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

}
//************************************************************************

_pantenon::_pantenon()
{
giro_techo=2.0; //valor inicial
giro_columna=0.0;
giro_techo_min=-9;  //tope inferior de movimiento
giro_techo_max=20;	//tope superior de movimiento

sube_techo=0.0; //valor inicial
sube_techo_min=-9; //tope inferior de movimiento
sube_techo_max=20;//tope superior de movimiento

sube_escal=0.0; //valor inicial
sube_escal_min=-9; //tope inferior de movimiento
sube_escal_max=20; //tope superior de movimiento

};


void _pantenon::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glRotatef(sube_escal,2,2,2);
escalera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);


glPushMatrix();
glRotatef(giro_columna,0,1,0); // glRotatef(variable para el movimiento,x,y,z); poner 1 en el eje en el que va a rotar
glTranslatef(0.0,-0.1,0.0); //ajuste en el ejey
glRotatef(sube_escal,0,1,0);
columna.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.6,0); //ajuste en el ejey
glRotatef(giro_techo,0,0,1); //rota alrededor del ejez
techo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


};
