#include"Regizor.h"
class Director :public Entity {
	Scenariu* Scenariu_Poveste;
public:
	Director(std::string nume):Entity(nume){}
	void Take_Scenariu(Scenariu*s);
	void Print_Movie();
	virtual void Fisier_Out()override{}
};