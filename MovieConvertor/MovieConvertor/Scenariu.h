#pragma once
#include<iostream>
#include<list>
#include"Scena.h"
#include"Personaje.h"



class Scenariu {
	std::vector<int>Fir_Narativ;
	std::string nume_scenariu;
	std::list<Scena*>lista_scene;
	std::list<Personaj*>lista_personaj;
public:
	std::list<Scena*>&Get_lista_scene();
	std::list<Personaj*>&Get_lista_personaj();
	std::string& Get_nume_scenariu();

	void Set_nume_scenariu(const std::string& nume);
	bool verify_existence_personaj(std::string nume_personaj);
	Personaj* Get_personaj_existent(std::string name);
	std::vector<int>&Get_Fir_Narativ();
};