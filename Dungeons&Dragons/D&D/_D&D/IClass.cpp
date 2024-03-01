#include "IClass.h"

IClass::IClass(IClass&& obj):Essence(std::move(obj))
{
}
