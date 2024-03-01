#include "Environment.h"

void Environment::citire_items(const char*filename)
{
	
	std::fstream My_file;
	std::string file = filename;
	std::string buffer;
	My_file.open(file, std::ios::in);
	if (My_file.is_open()) {


		while (My_file>>buffer) {
			if (buffer == "end") { break; }
			this->elemente_naturale_items.push_back(buffer);
		}
		while (My_file >> buffer) {
			if (buffer == "end") { break; }
			this->momente_ale_zilei_items.push_back(buffer);
		}
		while (My_file >> buffer) {
			
			this->starea_vremii_items.push_back(buffer);
		}
	}
	My_file.close();

}
std::string Random(std::list<std::string> list,int randomizer) {
	for (auto index : list) {
		if (randomizer == 0) { return index; }
		randomizer--;
	}
	return nullptr;
}
std::string Environment::elemente_naturale() {
	int random_number =static_cast<int>( std::rand() % static_cast<size_t>(elemente_naturale_items.size()));
	return Random(elemente_naturale_items,random_number);
}

std::string Environment:: momente_ale_zilei() {
	int random_number = static_cast<int>(std::rand() % static_cast<size_t>(momente_ale_zilei_items.size()));
	return Random(momente_ale_zilei_items, random_number);
}
std::string Environment::starea_vremii() {
	int random_number = static_cast<int>(std::rand() % static_cast<size_t>(starea_vremii_items.size()));
	return Random(starea_vremii_items, random_number);
}
std::string Environment::createEnv(EnvType envtype) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	switch (envtype) {
	case Elemente_naturale: return elemente_naturale();
	case Momentul_zilei:    return momente_ale_zilei();
	case Starea_vremii:    return starea_vremii();
	}
	
	throw "invalid Environment item type";
}

