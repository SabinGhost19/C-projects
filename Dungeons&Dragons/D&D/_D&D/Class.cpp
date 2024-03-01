#include "Class.h"

Class::Class(Class&& obj):IClass(std::move(obj))
{
}

void Class::Display_Class()
{
	std::cout << "The name of the Class: "
		<<this->GetName()<<std::endl;
	std::cout << this->Get_Description() << std::endl;

	this->Display_Attacks();

	this->Display_Abilities();
	
	
}
const std::string& Class::Get_Description()
{
	return this->description;
}
