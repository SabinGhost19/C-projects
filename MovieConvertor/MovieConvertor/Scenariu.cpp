#pragma once
#include"Scenariu.h"

std::list<Scena*>& Scenariu::Get_lista_scene(){return this->lista_scene;}
std::list<Personaj*>& Scenariu::Get_lista_personaj() {return this->lista_personaj;}

Personaj* Scenariu::Get_personaj_existent(std::string name)
{
	for (auto index : this->Get_lista_personaj()) {
		if (index->Get_nume_personaj() == name) {
			return index;
		}
	}
	return nullptr;
}

std::string& Scenariu::Get_nume_scenariu(){return this->nume_scenariu;}

void Scenariu::Set_nume_scenariu(const std::string& nume){this->nume_scenariu = nume;}

std::vector<int>& Scenariu::Get_Fir_Narativ() {return this->Fir_Narativ;}

bool Scenariu::verify_existence_personaj(std::string nume_personaj)
{
	for (auto index : this->Get_lista_personaj()) {
		if (index->Get_nume_personaj() == nume_personaj) { return true; }

	}
	return false;
}


