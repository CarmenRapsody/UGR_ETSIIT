//Claptrap.cc
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "Claptrap.h"
Claptrap::Claptrap(){
	EyeMove = 0;
	Advance = true;
	Arm_advance = true;
	Hand_advance = true;
	//Inicializar cada una de las figuras.
	//Cuerpo
	Cuerpo.setPLYfilename("body.ply");
	Cuerpo.InitFigure();
	
	//Antebrazos
	AnteBrazo1.setPLYfilename("armsup.ply");
	AnteBrazo2.setPLYfilename("armsup.ply");
	AnteBrazo1.InitFigure();
	AnteBrazo2.InitFigure();
	//Brazos
	Brazo1.setPLYfilename("armbot.ply");
	Brazo2.setPLYfilename("armbot.ply");
	Brazo1.InitFigure();
	Brazo2.InitFigure();
	//Ojo
	Eye.setPLYfilename("eye.ply");
	Eye.InitFigure();
	//Hombreras
	Hombrera1.setPLYfilename("shoulder.ply");
	Hombrera2.setPLYfilename("shoulder.ply");
	Hombrera1.InitFigure();
	Hombrera2.InitFigure();
	//Ruedas
	Rueda1.setPLYfilename("wheel.ply");
	Rueda1.InitFigure();

	SetMode(GL_TRIANGLES);
	SetModePolygon(GL_FILL);
	solid_lines = true;
	//ChangeChess();
	///////////////////
}
void Claptrap::MoveEye(float v){
	
	if(Advance){
		EyeMove+=(0.5*v);
		if(EyeMove > 4){
			Advance = !Advance;
		}
	}
	else{
		EyeMove -= (0.5*v);
		if(EyeMove < 0){
			Advance = !Advance;
		}
	}
}
void Claptrap::MoveArms(float v){
	if(Arm_advance){
		ArmMove+=(2*v);
		if(ArmMove > 60){
			Arm_advance = !Arm_advance;
		}
	}
	else{
		ArmMove-=(2*v);
		if(ArmMove <= 0){
			Arm_advance = !Arm_advance;
		}
	}
}
void Claptrap::MoveHands(float v){
	if(Hand_advance){
		HandsMove+=(2*v);
		if(HandsMove > 100){
			Hand_advance = !Hand_advance;
		}
	}
	else{
		HandsMove-=(2*v);
		if(HandsMove <= 0){
			Hand_advance = !Hand_advance;
		}
	}
}
void Claptrap::SetAllCenter(){
	Cuerpo.SetCenter();
	AnteBrazo1.SetCenter();
	AnteBrazo2.SetCenter();
	Brazo1.SetCenter();
	Brazo2.SetCenter();
	Eye.SetCenter();
	Hombrera1.SetCenter();
	Hombrera2.SetCenter();
	Rueda1.SetCenter();
}
void Claptrap::AutoRescale(){
	Cuerpo.AutoRescale();
	AnteBrazo1.AutoRescale();
	AnteBrazo2.AutoRescale();
	Brazo1.AutoRescale();
	Brazo2.AutoRescale();
	Eye.AutoRescale();
	Rueda1.AutoRescale();
}
void Claptrap::SetMode(GLenum mode){
	Cuerpo.SetMode(mode);
	Eye.SetMode(mode);
	Brazo1.SetMode(mode);
	Brazo2.SetMode(mode);
	AnteBrazo1.SetMode(mode);
	AnteBrazo2.SetMode(mode);
	Hombrera1.SetMode(mode);
	Hombrera2.SetMode(mode);
	Rueda1.SetMode(mode);
}
void Claptrap::SetModePolygon(GLenum mode){
	Cuerpo.SetModePolygon(mode);
	Eye.SetModePolygon(mode);
	Brazo1.SetModePolygon(mode);
	Brazo2.SetModePolygon(mode);
	AnteBrazo1.SetModePolygon(mode);
	AnteBrazo2.SetModePolygon(mode);
	Rueda1.SetModePolygon(mode);
	Hombrera1.SetModePolygon(mode);
	Hombrera2.SetModePolygon(mode);
}
void Claptrap::ChangeChess(){
	Cuerpo.ChangeChess();
	Eye.ChangeChess();
	Brazo1.ChangeChess();
	Brazo2.ChangeChess();
	AnteBrazo1.ChangeChess();
	AnteBrazo2.ChangeChess();
	Rueda1.ChangeChess();
	Hombrera1.ChangeChess();
	Hombrera2.ChangeChess();
}
void Claptrap::Dibujar(){
	AutoRescale();
	SetAllCenter();
	float extremo_brazo1 = AnteBrazo1.getCenterz()-AnteBrazo1.GetBoxIZ();
	float extremo_brazo2 = AnteBrazo2.getCenterz()-AnteBrazo2.GetBoxIZ();
	float extremo_mano1 = Brazo1.getCenterz()-Brazo1.GetBoxIZ();
	float extremo_mano2 = Brazo2.getCenterz()-Brazo2.GetBoxIZ();

	//Dibujar a claptrap
	glPushMatrix();
		glScalef(2,2,2);
		//Dibujar el cuerpo
		glPushMatrix();
			glRotatef(-90,0,1,0);
			glRotatef(-90,1,0,0);
			glScalef(1.5,1.5,1.5);
			glTranslatef(-Cuerpo.getCenterx(),-Cuerpo.getCentery(),-Cuerpo.getCenterz());
			if(solid_lines){
				Cuerpo.DibujaLineasYSolido(0.95,0.4,0.1,0.95,0.2,0.1);
			}
			else{
				Cuerpo.Dibujar();
			}
		glPopMatrix();

		//Dibujar hombreras
		//Hombrera derecha
		glPushMatrix();
			glTranslatef(-21,25,0);
			glRotatef(-90,0,0,1);
			glRotatef(90,0,1,0);
			glScalef(15,15,15);
			glTranslatef(-Hombrera1.getCenterx(),-Hombrera1.getCentery(),-Hombrera1.getCenterz());
			if(solid_lines){
				Hombrera1.DibujaLineasYSolido(0.1,0.9,0.1,0.1,1,0.1);
			}
			else{
				Hombrera1.Dibujar();
			}
			
		glPopMatrix();
		//Hombrera izquierda
		glPushMatrix();
			glScalef(-1,1,-1);
			glTranslatef(-21,25,0);
			glRotatef(-90,0,0,1);
			glRotatef(90,0,1,0);
			glScalef(15,15,15);
			glTranslatef(-Hombrera2.getCenterx(),-Hombrera2.getCentery(),-Hombrera2.getCenterz());
			if(solid_lines){
				Hombrera2.DibujaLineasYSolido(0.1,0.9,0.1,0.1,1,0.1);
			}
			else{
				Hombrera2.Dibujar();
			}
		glPopMatrix();
		//Dibujar el ojo
		glPushMatrix();
			glTranslatef(0,0,EyeMove);
			glTranslatef(0,19,15);
			glRotatef(-90,0,1,0);
			glScalef(0.3,0.3,0.3);
			glTranslatef(-Eye.getCenterx(),-Eye.getCentery(),-Eye.getCenterz());
			if(solid_lines){
				Eye.DibujaLineasYSolido(0.1,0.7,0.8, 0.1,0.9,1);
			}
			else{
				Eye.Dibujar();
			}
			
		glPopMatrix();
		//Dibujar las ruedas
		//Rueda 1
		glPushMatrix();
			glTranslatef(0,-30,-5);
			glRotatef(-90,0,0,1);
			glScalef(0.4,2,0.4);
			glTranslatef(-Rueda1.getCenterx(),-Rueda1.getCentery(),-Rueda1.getCenterz());
			if(solid_lines){
				Rueda1.DibujaLineasYSolido(0.2,0.2,0.2,0.1,0.1,0.1);
			}
			else{
				Rueda1.Dibujar();
			}
			
		glPopMatrix();
		//Dibujar los brazos
		//Brazo derecheo
			glPushMatrix();
				glTranslatef(-17,12,0);
				glTranslatef(0,extremo_brazo1*0.5,0);
				glRotatef(-ArmMove,0,0,1);
				glTranslatef(0,-1*(extremo_brazo1)*0.5,0);
			//Antebrazo
				glPushMatrix();
					glRotatef(-90,1,0,0);
					glScalef(0.5,0.5,0.5);
					glTranslatef(-AnteBrazo1.getCenterx(),-AnteBrazo1.getCentery(),-AnteBrazo1.getCenterz());
					if(solid_lines){
						AnteBrazo1.DibujaLineasYSolido(0.4,0.2,0.7, 0.3,0.2,0.6);
					}
					else{
						AnteBrazo1.Dibujar();
					}
					
				glPopMatrix();
			//Mano
				glPushMatrix();
					glTranslatef(0,-extremo_brazo1*0.5,0);
					glRotatef(-HandsMove,1,0,0);
					glTranslatef(0,-extremo_mano1*0.4,0);
					glRotatef(-90,1,0,0);
					glScalef(0.7,0.7,0.4);
					glTranslatef(-Brazo1.getCenterx(),-Brazo1.getCentery(),-Brazo1.getCenterz());
					if(solid_lines){
						Brazo1.DibujaLineasYSolido(0.4,0.2,0.7, 0.3,0.2,0.6);
					}
					else{
						Brazo1.Dibujar();
					}
					
				glPopMatrix();
			glPopMatrix();
		//Brazo Izquierdo
			glPushMatrix();
				glTranslatef(17,12,0);
				glTranslatef(0,extremo_brazo2*0.5,0);
				glRotatef(ArmMove,0,0,1);
				glTranslatef(0,-1*(extremo_brazo2)*0.5,0);
			//Antebrazo
				glPushMatrix();
					glRotatef(-90,1,0,0);
					glScalef(0.5,0.5,0.5);
					glTranslatef(-AnteBrazo2.getCenterx(),-AnteBrazo2.getCentery(),-AnteBrazo2.getCenterz());
					if(solid_lines){
						AnteBrazo2.DibujaLineasYSolido(0.4,0.2,0.7, 0.3,0.2,0.6);
					}
					else{
						AnteBrazo2.Dibujar();
					}
					
				glPopMatrix();
			//Mano
				glPushMatrix();
					glTranslatef(0,-extremo_brazo2*0.5,0);
					glRotatef(-HandsMove,1,0,0);
					glTranslatef(0,-extremo_mano2*0.4,0);
					glRotatef(-90,1,0,0);
					glScalef(0.7,0.7,0.4);
					glTranslatef(-Brazo2.getCenterx(),-Brazo2.getCentery(),-Brazo2.getCenterz());
					if(solid_lines){
						Brazo2.DibujaLineasYSolido(0.4,0.2,0.7, 0.3,0.2,0.6);
					}
					else{
						Brazo2.Dibujar();
					}
					
				glPopMatrix();
			glPopMatrix();		
	glPopMatrix();
}