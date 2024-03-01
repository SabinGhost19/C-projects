#pragma once
#include "Entity.h"
#include"Efecte.h"
#include"Scenariu.h"
class Producator : public Entity
{
	Concrete_Builder_Efecte Builder;
	Scenariu* Scenariu_poveste;
public:
	Producator(std::string nume):Entity(nume){}
	void Take_Scenariu(Scenariu*s);
	void Do_Job();
	virtual void Fisier_Out()override;
	/*Scenariu* Give_Scenariu()const;*/
};

