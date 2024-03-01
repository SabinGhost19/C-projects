#include "Essence.h"
std::ostream& operator<<(std::ostream& out, const Ability& ability)
{

	switch (ability) {
	case STRENGHT:
		return out << "STRENGHT";
	case CHARISMA:
		return out << "CHARISMA";
	case INTELIGENCE:
		return out << "INTELIGENCE";
	case WISDOM:
		return out << "WISDOM";
	case DEXTERITY:
		return out << "DEXTERITY";
	case CONSTITUTION:
		return out << "CONSTITUTION";
	}

	// TODO: insert return statement here
}


Essence::Essence(Essence&& essence)noexcept
{
	this->List_of_attacks=std::move(essence.List_of_attacks);
	this->Racial_ability = std::move(essence.Racial_ability);
	this->name = std::move(essence.name);
	
}

void Essence::Set_Racial_Ability(const Ability& ability, int points)
{
	std::pair<Ability, int> NewPair = std::make_pair(ability, points);
	this->Racial_ability.push_back(NewPair);
}

void Essence::Set_Attack(Attack* attack)
{
	this->List_of_attacks.push_back(attack);
}

const std::string& Essence::GetName()
{
	return this->name;
}

std::list<std::pair<Ability, int>>& Essence::Get_Racial_Ability()
{
	return this->Racial_ability;
}

const std::list<Attack*>& Essence::Get_Attacks()
{
	return this->List_of_attacks;
}

const void Essence::Display_Attacks()
{
	int nr = 1;
	for (auto attack : this->List_of_attacks) {
		std::cout << nr << ". " << attack->description <<CYAN<< "->"<<RESET<<"points require:" <<CYAN<< attack->points <<RESET<< " " << GREEN<<attack->bonus_ability <<RESET<< std::endl; nr++;
	}
	return void();
}

const void Essence::Display_Abilities()
{
	std::cout << "Lista de abilitati: \n";
	for (auto ability : this->Get_Racial_Ability()) {
		std::cout << GREEN<<ability.first <<RESET<< " " << ability.second << std::endl;
	}
	std::cout << "\n";
}



