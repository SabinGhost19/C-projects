#pragma once
#include"Essence.h"

class IClass : public Essence{

public:
	IClass(const IClass& obj) = delete;
	IClass(IClass&& obj);
	IClass() = default;
	virtual void Set_Description(std::string_view description_p) = 0;
	virtual const std::string& Get_Description() = 0;
	virtual void Display_Class() = 0;

	virtual IClass& operator=(IClass&& obj)noexcept {
		if (&obj != this) {
			Essence::operator=(std::move(obj));
		}
		return *this;
	};
};

