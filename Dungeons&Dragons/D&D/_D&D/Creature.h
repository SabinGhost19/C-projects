#pragma once
#include"ICreature.h"

class Creature: public ICreature
{
	std::string category;
	int health;
	std::string backGround;
public:
	Creature()=default;
	Creature(const Creature& obj) = delete;
	Creature(Creature&& obj);
	virtual void Set_BackGround(std::string_view bg)override { this->backGround = bg; };
	virtual void Set_Health(int health_p) override{ this->health = health_p; };
	virtual void Set_Category(const std::string_view cat) override{ category = cat; }
	virtual void Display_Creature()override;
	friend std::ostream& operator<<(std::ostream& out, const Ability& ability);
	virtual Creature& operator=(Creature&& obj)noexcept {
		if (&obj != this) {
			ICreature::operator=(std::move(obj));
			this->category = std::move(obj.category);
			this->health = obj.health;
			this->backGround = std::move(obj.backGround);
		}
		return *this;
	};
	virtual std::string& GetCategory()override;
	virtual int Get_Health()override;
	virtual void Get_Hit(int damage)override;
	

};

