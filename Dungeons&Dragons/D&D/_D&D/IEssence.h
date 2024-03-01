#pragma once
#include<iostream>
#include"Utility.h"
#include"string_view"
#include<utility>
#include<list>

class IEssence
{
public:
	//virtual void Display() = 0;
	virtual void SetName(std::string_view name_p) = 0;
	virtual void Set_Racial_Ability(const Ability& ability, int points)=0;
	virtual void Set_Attack(Attack* attack) = 0;

	virtual const std::string& GetName() = 0;
	virtual const std::list<std::pair<Ability, int>>& Get_Racial_Ability() = 0;
	virtual const std::list<Attack*>&Get_Attacks() = 0;
	virtual const void Display_Attacks()= 0;
	virtual const void Display_Abilities() = 0;
	//virtual Essence& operator=(Essence&& obj)noexcept = 0;
};

