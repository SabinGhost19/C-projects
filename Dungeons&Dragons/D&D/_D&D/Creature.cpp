#include "Creature.h"

Creature::Creature(Creature&& obj) :ICreature(std::move(obj)) {
	this->health = obj.health;
	this->category = std::move(obj.category);
	this->backGround = std::move(obj.backGround);
}

void Creature::Display_Creature()
{
	std::cout << "The name of the Creature: "
		<< this->GetName() << std::endl;
	std::cout << "Category: " << this->category << std::endl;
	std::cout << this->backGround << std::endl;
	std::cout<<"Health: "<<this->health<<std::endl;

	this->Display_Attacks();

	this->Display_Abilities();
	
}

std::string& Creature::GetCategory()
{
	return this->category;
}
int Creature::Get_Health()
{
	return this->health;
}

void Creature::Get_Hit(int damage)
{
	this->health -= damage;
}
