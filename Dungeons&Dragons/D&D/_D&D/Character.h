#pragma once
#include "ICharacter.h"

class Character :public ICharacter{
private:
	std::string name;
	Class class_type;//cu move constructor
	Creature creature;//cu move constructor
	std::map<int, int>value_of_points;
public:
	Character();
	virtual int Point_Equivalence(int point_value)override;
	virtual void Read_Value_of_Points(const char* filename)override;

	virtual void Update_Ability(int points_s, const Ability& ability_p)override;


	virtual void Display()override;
	virtual void DisplayAbilities()override;


	virtual void Set_Creature(Creature&& creature)override;
	virtual void Set_Class(Class&&class_param)override;
	virtual void Set_Name(std::string_view name_param)override;

	virtual std::string& Get_Name()override;
	virtual Creature& Get_CreatureType()override;
	virtual Class& Get_ClassType()override;
	virtual int Get_Necesarry_AbilityPNTs(const Ability&ability)override;
	virtual int Get_Health()override;
	virtual void Get_Hit(int damage)override;
	virtual int Attack(bool type_of_user)override;
	virtual int Attack_Choice(int choice,bool type_of_user)override;
};
void Display_Ability(const Ability& ability);

