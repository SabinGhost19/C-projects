#include "Actor.h"

Actor::Actor(std::string nume)
{
	this->nume = nume;
}

void Actor::set_stare_spirit(int stare)
{
	this->stare_spirit = stare;
}

void Actor::set_type(character_type tip)
{
	this->type = tip;
}

std::string& Actor::get_nume()
{
	return this->nume;
}

int Actor::get_stare_spirit() const
{
	return this->stare_spirit;
}

character_type Actor::get_type() const
{
	return this->type;
}
