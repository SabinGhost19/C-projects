#include "Creature.h"

ICreature::ICreature(ICreature&& obj):Essence(std::move(obj))
{

}
