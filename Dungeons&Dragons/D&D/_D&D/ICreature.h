#pragma once
#include"Essence.h"

class ICreature : public Essence
{
public:
	ICreature() = default;
	ICreature(const ICreature& obj) = delete;
	ICreature(ICreature&& obj);

	virtual void Set_BackGround(std::string_view bg) = 0;
	virtual void Set_Health(int health_p) = 0;
	virtual void Set_Category(const std::string_view cat) = 0;
	virtual void Display_Creature() = 0;
	virtual void Get_Hit(int damage) = 0;
	virtual int Get_Health() = 0;
	virtual std::string& GetCategory() = 0;
	virtual ICreature& operator=(ICreature&& obj)noexcept {
		if (&obj != this) {
			Essence::operator=(std::move(obj));
		}
		return *this;
	};
};

