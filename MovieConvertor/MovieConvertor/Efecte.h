#pragma once
#include<iostream>
#include<list>
#include<fstream>
#include<string>
#include <sstream>
#include <ctime>
class Efecte{
	std::list<std::string>efecte_bune;
	std::list<std::string>efecte_rele;

public:
	virtual void set_efect_BAD(std::string word);
	virtual void set_efect_GOOD(std::string word);

	virtual std::list<std::string>&Get_efects_BAD();
	virtual std::list<std::string>&Get_efects_GOOD();
	void citire_fisier(const char*filename);

	std::string extragere_efect_GOOD();
	std::string extragere_efect_BAD();
};

class Efecte_Sonore :public Efecte{
};
class Efecte_Vizuale :public Efecte{
};


class Build_Efecte {

protected:
	virtual std::string efecte_Sonore(int coeficient)=0;
	virtual std::string efecte_Vizuale(int coeficient)=0;
};


class Concrete_Builder_Efecte : public Build_Efecte {
	Efecte_Sonore efecte_sonore;
	Efecte_Vizuale efecte_vizuale;
public:
	Concrete_Builder_Efecte() {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		efecte_sonore.citire_fisier("Ef_sonore.txt");
		efecte_vizuale.citire_fisier("Ef_vizuale.txt");
	}
	    virtual std::string efecte_Sonore(int coeficient)override;
		virtual std::string efecte_Vizuale(int coeficient)override;
};


