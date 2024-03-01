#pragma once
#include<iostream>
#include"Personaje.h"
#include<list>

typedef enum {
	STATICA,
	DINAMICA
}scena_type;
static int scena_id = 1;

class Scena {
	int gradul_de_compatibilitate;
    int ID_scena;
	std::string script;
	scena_type tip_scena;
	std::list<std::string>efecte;
	std::list<Personaj*>lista_personaje_scena;
	std::list<std::string>lista_environment_items;
public:

	Scena(std::string script_param) :script(script_param) { ID_scena = scena_id; scena_id++; }

	
	int Get_gradul_compatibilitate()const;
	int Get_ID()const;
	scena_type Get_tip_scena()const;
	std::list<Personaj*>&Get_lista_personaje_scena();
	std::string& Get_Script();
	std::list<std::string>Get_efecte()const;
	std::list<std::string>Get_environemnt_items()const;

	void Set_tip_scena(scena_type tip_scena_param);
	void Set_grad_comp(int nr);
	void Set_efect(std::string efect);

	bool verify_existence_personaj(std::string nume);
	void add_personaj(Personaj* personaj);


	bool verify_singularity_characters();
	void insert_environment_items(std::string itme);
};