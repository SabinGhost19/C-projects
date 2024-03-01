#pragma once
#include<iostream>
typedef enum {
	PRINCIPAL,
	FIGURANT
}character_type;

class Actor
{
	std::string nume;
	int stare_spirit;
	character_type type;  //principal sau figurant
public:
	Actor(std::string nume);
	void set_stare_spirit(int stare);
	void set_type(character_type tip);
	std::string& get_nume();
	int get_stare_spirit()const;
    character_type get_type()const;

};

