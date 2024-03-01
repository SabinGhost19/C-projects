#include"Scena.h"

void Scena::Set_efect(std::string efect) {
	this->efecte.push_back(efect);
}

void Scena::Set_grad_comp(int nr)
{
	this->gradul_de_compatibilitate = nr;
}

int Scena::Get_gradul_compatibilitate() const
{
	return static_cast<int>(this->gradul_de_compatibilitate);
}

void Scena::Set_tip_scena(scena_type tip_scena_param){
	tip_scena = tip_scena_param;
}

scena_type Scena::Get_tip_scena() const
{
	return this->tip_scena;
}

bool Scena::verify_existence_personaj(std::string nume)
{
	for (auto index : lista_personaje_scena) {
		if (index->Get_nume_personaj() == nume) { return true; }
	}
	return false;
}

void Scena::add_personaj(Personaj* personaj)
{
	this->lista_personaje_scena.push_back(personaj);
	
}

std::list<Personaj*>& Scena::Get_lista_personaje_scena()
{
	return this->lista_personaje_scena;
}

std::string& Scena::Get_Script()
{
	return this->script;
}

std::list<std::string> Scena::Get_efecte() const
{
	return this->efecte;
}

std::list<std::string> Scena::Get_environemnt_items() const
{
	return this->lista_environment_items;
}

bool Scena::verify_singularity_characters()
{
	int count = 0;
	
	for (auto personaj : this->lista_personaje_scena) {
		count++;
	}
	if (count == 0)  return true; 
	else return false; 
}

void Scena::insert_environment_items(std::string item)
{
	this->lista_environment_items.push_back(item);
}

int Scena::Get_ID() const
{
	return this->ID_scena;
}
