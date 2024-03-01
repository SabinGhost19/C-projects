#pragma once
#include<iostream>
#include<list>
#include"Utility.h"
class Item
{
	std::list<Ability>all_abilities;
	std::string denumire;
	std::string description;// s-a deschis etc...
public:
	Item(std::string_view denumire_p);
	std::string& Get_Description();
	Ability& Generate_Ability();
	std::string& Get_Denumire();
	//virtual void Generate_Gift();
	int Generate_Point();
	~Item() = default;
protected:
	void Set_description(std::string_view description_p);
	void Set_Abilities();
};

