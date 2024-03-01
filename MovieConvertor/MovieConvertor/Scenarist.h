#pragma once
#include"Entity.h"
#include<fstream>
#include"Scenariu.h"
#include<string>
#include <cassert>
#include <sstream>
//#include <cctype>

class Scenarist :public Entity{
	Scenariu *Scenariu_poveste=nullptr;
public:
	void add_dialoguri(std::string sir_complet, Scena* scena,int counter);
	void add_characters(std::string script, Scena* scena);
	void add_character_in_Scenariu(std::string script);
	Scenarist(std::string nume) :Entity(nume) {}
	void citire_poveste(const char*nume_poveste);
	void Set_characters_type();
	void add_scena(Scena* s);
	void add_order_in_FN(int ID);

	Scenariu* Give_scenariu()const;
	virtual void Fisier_Out()override;

};