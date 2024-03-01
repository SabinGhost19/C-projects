#pragma once
#include<iostream>
#include<vector>
class Entity
{
	std::string nume_entitate;
	static int personal_ID;
protected:
	Entity(std::string nume) :nume_entitate(nume) {incremenet_personal_ID();}
	void incremenet_personal_ID();

	std::string Get_name();
	int Get_ID()const;
	virtual void Fisier_Out() = 0;
};