#pragma once
#include"Personaje.h"

std::map<int, std::string> Personaj::Get_actiuni_personaj()
{
	return this->replici_personaj;
}

std::string& Personaj::Get_nume_personaj() { return this->nume_personaj; }

character_type Personaj::Get_personaj_type() const
{
	return this->tipul_de_personaj;
}

void Personaj::Get_personaj_type(character_type tip)
{
	this->tipul_de_personaj = tip;
}

void Personaj::Set_dialog(int ID,std::string dialog)
{
	this->replici_personaj.insert({ ID, dialog });
}

void Personaj::Set_actor(Actor* actor_param) {
	actor = actor_param;
}

Actor& Personaj::Get_actor() {
	return *actor;
}
