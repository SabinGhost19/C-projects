#pragma once
#include<iostream>
#include"Creature.h"
#include"Class.h"
#include<map>
#include <fstream>
#include <string>

class ICharacter
{
public:
	ICharacter(const ICharacter& obj) = delete;
	//ICharacter(ICharacter&& obj);
	ICharacter() = default;

	virtual int Point_Equivalence(int point_value)=0;
	virtual void Read_Value_of_Points(const char* filename)=0;

	virtual void Update_Ability(int points_s, const Ability& ability_p)=0;
	virtual void Display() = 0;
	virtual void DisplayAbilities() = 0;

	virtual void Set_Creature(Creature&& creature)=0;
	virtual void Set_Class(Class&& class_param)=0;
	virtual void Set_Name(std::string_view name_param) = 0;

	virtual std::string& Get_Name() = 0;
	virtual Creature& Get_CreatureType() = 0;
	virtual Class& Get_ClassType() = 0;
	virtual int Get_Necesarry_AbilityPNTs(const Ability& ability)=0;
	virtual int Get_Health() = 0;
	virtual int Attack(bool type_of_user) = 0;
	virtual int Attack_Choice(int choice,bool type_of_user)=0;
	virtual void Get_Hit(int damage)=0;

};

