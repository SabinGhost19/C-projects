#include "Entity.h"
int Entity::personal_ID = 432000;

std::string Entity::Get_name() {return this->nume_entitate;}
int Entity::Get_ID()const { return this->personal_ID; }
void Entity::incremenet_personal_ID(){personal_ID++;}
