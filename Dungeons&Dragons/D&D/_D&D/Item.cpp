#include "Item.h"

Item::Item(std::string_view denumire_p):denumire(denumire_p)
{
	Set_Abilities();

	if (denumire == "Book") {
		Set_description("The Book has been read and it generates you: ");
	}
	else if (denumire == "Portal") {
		Set_description("The Portal has been opened...-->>trevelling...-->>: ");
	}
	else if (denumire == "Door") {
		Set_description("The Door has been opened...The next Room your are stepping into:  ");
	}
}

std::string& Item::Get_Description() { return this->description; }

void Item::Set_description(std::string_view description_p) { this->description=description_p; }

 void Item::Set_Abilities()
{ 
	//not so relevant
    this->all_abilities.push_back(std::move(STRENGHT));
	this->all_abilities.push_back(std::move(INTELIGENCE));
	this->all_abilities.push_back(std::move(CONSTITUTION));
	this->all_abilities.push_back(std::move(WISDOM));
	this->all_abilities.push_back(std::move(DEXTERITY));
	this->all_abilities.push_back(std::move(CHARISMA));
}

int Item::Generate_Point()
{
	return Random::get(-5,10);
}
Ability& Item::Generate_Ability()
{
	int index = Random::get(1,6);
	if (index > 0 && index <= this->all_abilities.size()) {
		auto it = std::next(this->all_abilities.begin(), index - 1);
		return *it;
	}
	else {
		return this->all_abilities.front();
	}
}

std::string& Item::Get_Denumire()
{
	return this->denumire;
}
