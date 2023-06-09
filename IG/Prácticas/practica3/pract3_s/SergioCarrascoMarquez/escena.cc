#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"
#include <vector>


Escena::Escena(){
	std::vector<float> lista;
	///////////////////////////////
	////////////////////////////////
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);
    clap.AutoRescale();
    animacion = false;
    steep = 0;
    speed = 0;
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {
	clap.Dibujar();
}



void Escena::dibujar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {

    std::cout << "Tecla" << Tecla1<< std::endl;
	if (toupper(Tecla1)=='Q') return 1;
	else{
		
		switch(Tecla1){
			//Ojo
			case 'E':
				clap.MoveEye(speed);
			break;
			//Antebrazos
			case 'A':
				clap.MoveArms(speed);
			break;
			//Codos
			case 'F':
				clap.MoveHands(speed);
			break;
			case 'N':
				animacion = true;
			break;
			case 'M':
				animacion = false;
			break;
			case 'U':
				speed++;
			break;
			case 'D':
				if(speed > 0){
					speed--;
				}
			break;
			case 'L':
				clap.SolidLines(false);
				clap.SetMode(GL_LINES);
				clap.SetModePolygon(GL_TRIANGLES);
			break;
			case 'P':
				clap.SolidLines(false);
				clap.SetMode(GL_POINTS);
				clap.SetModePolygon(GL_FILL);
			break;
			case 'S':
				clap.SolidLines(true);
			break;
		}
		return 0;
	}
}
void Escena::Animar(){
	dibujar();
	if(animacion){
		if (steep<20){
			clap.MoveEye(speed);
		}
		else if(steep % 2 == 0){
			clap.MoveArms(speed);
		}
		else{
			clap.MoveHands(speed);
		}
		steep++;
		steep = steep%100;
	}

}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}
