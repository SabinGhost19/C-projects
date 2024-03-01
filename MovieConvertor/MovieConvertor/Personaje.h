#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<utility>
#include"Actor.h"

class Personaj {

	std::string nume_personaj;
	character_type tipul_de_personaj;
	Actor *actor;
	std::map<int,std::string>replici_personaj;
	
public:
	void Get_personaj_type(character_type tip);
	void Set_dialog(int ID,std::string dialog);
	std::map<int,std::string> Get_actiuni_personaj();

	Personaj(std::string nume):nume_personaj(nume){}

	std::string& Get_nume_personaj();
	character_type Get_personaj_type()const;
	void Set_actor(Actor* actor_param);
	Actor& Get_actor();

};