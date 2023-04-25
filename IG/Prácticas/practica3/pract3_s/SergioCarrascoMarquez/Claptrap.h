	//Claptrap.h
	#ifndef CALPTRAP_H
	#define CALPTRAP_H

	#include "ObjetoPLY.h"
	class Claptrap{
private:
	ObjetoPLY Hombrera1,Hombrera2;
	ObjetoPLY Cuerpo;
	ObjetoPLY Eye;
	ObjetoPLY AnteBrazo1,AnteBrazo2;
	ObjetoPLY Brazo1,Brazo2;
	ObjetoPLY Rueda1;
	float EyeMove;
	float ArmMove;
	float HandsMove;
	bool Advance;
	bool Arm_advance;
	bool Hand_advance;
	bool solid_lines;
public:
	Claptrap();
	void Dibujar();
	void AutoRescale();
	void SetAllCenter();
	void MoveEye(float v);
	void MoveArms(float v);
	void MoveHands(float v);
	void SetMode(GLenum mode);
	void SetModePolygon(GLenum mode);
	void ChangeChess();
	void SolidLines(bool state){solid_lines = state;}
};
#endif
