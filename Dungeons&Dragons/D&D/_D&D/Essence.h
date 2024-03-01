#pragma once
#include "IEssence.h"
class Essence :public IEssence
{
	std::string name;
	std::list<std::pair<Ability, int>>Racial_ability;
	std::list<Attack*>List_of_attacks;
public:
	Essence() = default;
	Essence(const Essence& essence) = delete;
	Essence(Essence&& essence)noexcept;
	virtual void SetName(std::string_view name_p) override{ name = name_p; };
	virtual void Set_Racial_Ability(const Ability& ability, int points)override;
	virtual void Set_Attack(Attack* attack)override;

	virtual const std::string& GetName()override;
	virtual std::list<std::pair<Ability, int>>& Get_Racial_Ability()override;
	virtual const std::list<Attack*>& Get_Attacks()override;
	virtual const void Display_Attacks()override ;
	virtual const void Display_Abilities()override;
	virtual Essence& operator=(Essence&& essence)noexcept {
		if (&essence != this) {
			this->List_of_attacks = std::move(essence.List_of_attacks);
			this->Racial_ability = std::move(essence.Racial_ability);
			this->name = std::move(essence.name);
		}
		return *this;
	};
};

