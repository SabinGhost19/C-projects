#pragma once
#include<iostream>
#include<list>
#include <cstdlib>
#include <ctime>
#include<fstream>
#include<string>

enum EnvType {
		Elemente_naturale,
		Momentul_zilei,
		Starea_vremii
	};
class Environment
{
	std::list<std::string>elemente_naturale_items;
	std::list<std::string>momente_ale_zilei_items;
	std::list<std::string>starea_vremii_items;
	
public:
	Environment(){ citire_items("Fisier_environment.txt"); }
	std::string elemente_naturale();
	std::string momente_ale_zilei();
	std::string starea_vremii();
	std::string createEnv(EnvType envtype);
	
	void citire_items(const char* filename);

};

