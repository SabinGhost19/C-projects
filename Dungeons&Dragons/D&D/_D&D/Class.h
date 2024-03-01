#pragma once
#include "IClass.h"



class Class :public IClass
{
	std::string description;
	//std::list<passive abilities>...
public:
	Class() = default;
	Class(Class&& obj);
	Class(const Class& obj) = delete;

	virtual void Set_Description(std::string_view description_p) override{
		description=description_p; }
	virtual void Display_Class()override;
	virtual const std::string& Get_Description()override;
	friend std::ostream& operator<<(std::ostream& out, const Ability& ability);
	virtual Class& operator=(Class&& obj)noexcept {
		if (&obj != this) {
			IClass::operator=(std::move(obj));
		}
		return *this;
	};
};

