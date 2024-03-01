#include "Character.h"

Character::Character()
{
	Read_Value_of_Points("value_of_points.txt");
}

int Character::Point_Equivalence(int point_value)
{
	if (point_value > 30) { return 10; }
	if (point_value < 1) { return -5; }

	return this->value_of_points[point_value];
}


void Character::Read_Value_of_Points(const char* filename)
{
	std::ifstream inputFile(filename);
	try {
		if (!inputFile.is_open()) {
			throw std::runtime_error("Eroare la deschiderea fisierului!");
			// cu cod de eroare
		}
		int number;
		int index = 1;
		while (inputFile >> number) {
			if (index == 1 || index == 30) {
				std::pair<int, int > NewPair = std::make_pair(index, number);
				this->value_of_points.insert(NewPair);
				index++;
			}
			else {
				std::pair<int, int > NewPair = std::make_pair(index, number);
				this->value_of_points.insert(NewPair);
				index++;
				NewPair = std::make_pair(index, number);
				this->value_of_points.insert(NewPair);
				index++;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Eroare: " << e.what() << std::endl;
		inputFile.close();
	}
	inputFile.close();

}

void Character::Update_Ability(int points_s, const Ability& ability_p)
{
	for (auto it : this->Get_CreatureType().Get_Racial_Ability()) {
		if (it.first == ability_p) {
			it.second += points_s;
			std::cout << "UPDATED" << std::endl;
			break;
		}
	}
	
}

void Character::Display()
{

	std::cout << GREEN<<"Characterul tau: " << this->Get_Name() <<RESET <<std::endl;
	std::cout << "\nCREATURA proprie :";
	std::cout<<this->creature.GetCategory();
	std::cout << "\nCLASA proprie:";
	std::cout<<this->class_type.GetName();

	std::cout << YELLOW<<"\n\nAbilities: \n"<<RESET;
	DisplayAbilities();
	std::cout << YELLOW<<"\n\nAttacks: \n\n"<<RESET;
	this->creature.Display_Attacks();
	this->class_type.Display_Attacks();
}

void Character::DisplayAbilities()
{
	
	for (auto index : this->creature.Get_Racial_Ability()) {
		int points = 0;
		points += index.second;
		for (auto index2 : this->class_type.Get_Racial_Ability()) {
			if (index.first == index2.first) {
				points += index2.second; break;
			}
		}
		switch (index.first) {
		case STRENGHT:
			std::cout << GREEN<<"\tSTRENGHT"<<RESET;
			break;
		case CHARISMA:
			std::cout << GREEN << "\tCHARISMA" << RESET;
			break;
		case INTELIGENCE:
			std::cout << GREEN << "\tINTELIGENCE" << RESET;
			break;
		case WISDOM:
			std::cout << GREEN << "\tWISDOM" << RESET;
			break;
		case DEXTERITY:
			std::cout << GREEN << "\tDEXTERITY" << RESET;
			break;
		case CONSTITUTION:
			std::cout << GREEN << "\tCONSTITUTION" << RESET;
			break;
		default:
			std::cout << " ";
		}
		std::cout << " : " << this->Point_Equivalence(points) << std::endl;
	}
}


void Character::Set_Creature(Creature&& creature)
{
	this->creature = std::move(creature);
}

void Character::Set_Class(Class&& class_param)
{
	this->class_type = std::move(class_param);
}

void Character::Set_Name(std::string_view name_param)
{
	this->name = name_param;
}

std::string& Character::Get_Name()
{
	return this->name;
}

Creature& Character::Get_CreatureType()
{
	return this->creature;
}

Class& Character::Get_ClassType()
{
	return this->class_type;
}

int Character::Get_Necesarry_AbilityPNTs(const Ability& ability)
{
	int adding_points=0;
	for (auto index : this->Get_ClassType().Get_Racial_Ability()) {
		if (index.first == ability) {
			adding_points += index.second;
			break;
		}
	}
	for (auto index : this->Get_CreatureType().Get_Racial_Ability()) {
		if (index.first == ability) {
			adding_points += index.second;
			break;
		}
	}
	
	return this->Point_Equivalence(adding_points);
 }

int Character::Get_Health()
{
	return this->Get_CreatureType().Get_Health();
}

void Character::Get_Hit(int damage)
{
	this->Get_CreatureType().Get_Hit(damage);
}

int Character::Attack(bool type_of_user)
{
	int choice;
	int damage;
	if (type_of_user) {
		while (1) {
			std::cout << "Ce tip de atacuri doresti sa folosesti: \n";
			std::cout << "enter the number: \n";
			std::cout << YELLOW<<"Default attacks: 1\n"<<RESET;
			std::cout << YELLOW<<"Special attacks: 2\n"<<RESET;
			std::cin >> choice;
			if (choice == 1) {
				this->creature.Display_Attacks();
				return Attack_Choice(choice, true);
			}
			else if (choice == 2) {
				this->class_type.Display_Attacks();
				return Attack_Choice(choice, true);
			}
			else {
				std::cout << "Ai intodus indicele atacului gresit,te rog introdu o cifra corespunzatoare atacului dorit cum este afisat mai sus!\n";
			}
		}
	}
	else {
		choice = Random::get(1, 2);
		if (choice == 1) {
			return Attack_Choice(choice,false);
		}
		else {
			return Attack_Choice(choice,false);
		}
	}

	return 0;
}

int Character::Attack_Choice(int choice,bool type_of_user)
{
	if (choice == 1) {
		if (type_of_user) {

			while (1) {
				try {
					std::cout << "Enter the nr for the Attack: ";
					std::cin >> choice;
					if (choice > this->creature.Get_Attacks().size()) { throw(0); }
					else { break; }
				}
				catch (int error) {
					std::cout << ITALIC<<"Ai intodus indicele atacului gresit,te rog introdu o cifra corespunzatoare atacului dorit cum este afisat mai sus!\n"<<RESET;
				}
			}
		}
		else {
			int size = static_cast<int>(this->Get_CreatureType().Get_Attacks().size());
			choice = Random::get(1, size);
		}
		
		for (auto index : this->creature.Get_Attacks()) {
			choice--;
			if (type_of_user) { 
				if (choice == 1) {
					std::cout << ITALIC<<"Points required for this attack type: " << index->points << std::endl;;
					std::cout << "Nr of bonus points from your personal character: " << RESET
						<< MAGENTA << this->Get_Necesarry_AbilityPNTs(index->bonus_ability)
						<< RESET << " of " << GREEN;
					Display_Ability(index->bonus_ability);
					std::cout<< RESET << std::endl;
				}
				return static_cast<int>(index->points-this->Get_Necesarry_AbilityPNTs(index->bonus_ability)); }
		}
	}
	else {
		if (type_of_user) {
			while (1) {
				try {
					std::cout << "Enter the nr for the Attack: ";
					std::cin >> choice;
					if (choice > this->class_type.Get_Attacks().size()) { throw(0); }
					else { break; }
				}
				catch (int error) {
					std::cout << ITALIC<<"Ai intodus indicele atacului gresit,te rog introdu o cifra corespunzatoare atacului dorit cum este afisat mai sus!\n"<<RESET;
				}
			}
		}
		else {
			int size = static_cast<int>(this->Get_CreatureType().Get_Attacks().size());
			choice = Random::get(1, size);
		}
		for (auto index : this->class_type.Get_Attacks()) {
			choice--;
			if (choice == 0) { 
				if (type_of_user) {
					std::cout << ITALIC<<"Points required for this attack type: " << index->points<< std::endl;;
					std::cout << "Nr of bonus points from your personal character: " << RESET
						<< MAGENTA << this->Get_Necesarry_AbilityPNTs(index->bonus_ability);
					std::cout<< RESET << " of " << GREEN;
					Display_Ability(index->bonus_ability);
					std::cout << RESET << std::endl;
				}
				return static_cast<int>(index->points - this->Get_Necesarry_AbilityPNTs(index->bonus_ability));
			}
		}
	}
	return 0;
}
