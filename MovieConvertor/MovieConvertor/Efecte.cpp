#include "Efecte.h"
std::string Concrete_Builder_Efecte::efecte_Sonore(int coeficient){
	if (coeficient < 15) {
		return efecte_sonore.extragere_efect_BAD();
	}
	else { return efecte_sonore.extragere_efect_GOOD(); }
}

std::string Concrete_Builder_Efecte::efecte_Vizuale(int coeficient) {
	if (coeficient < 15) {
		return efecte_vizuale.extragere_efect_BAD();
	}
	else { return efecte_vizuale.extragere_efect_GOOD(); }
}

std::list<std::string>& Efecte::Get_efects_GOOD() { return this->efecte_bune; }
std::list<std::string>& Efecte::Get_efects_BAD() { return this->efecte_rele; }

void Efecte::set_efect_GOOD(std::string word) {this->efecte_bune.push_back(word);}
void Efecte::set_efect_BAD(std::string word) {this->efecte_rele.push_back(word);}
std::string Efecte::extragere_efect_GOOD() {
	int random_number = static_cast<int>(std::rand() % static_cast<size_t>(efecte_bune.size()));
	for (auto efect : this->efecte_bune) {
		if (random_number == 0) { return efect; }
		random_number--;
	}
}
std::string Efecte::extragere_efect_BAD() {
	int random_number = static_cast<int>(std::rand() % static_cast<size_t>(efecte_rele.size()));
	for (auto efect : this->efecte_rele) {
		if (random_number == 0) { return efect; }
		random_number--;
	}
}
void Efecte::citire_fisier(const char* filename) {
	std::fstream My_file;
	std::string file = filename;
	std::string buffer;
	
	My_file.open(file, std::ios::in);
	if (My_file.is_open()) {
		    std::getline(My_file, buffer);
			std::istringstream iss(buffer);
			std::string word;
			while (iss >> word) {
				set_efect_BAD(word);
			}
			std::getline(My_file, buffer);
			std::istringstream iss2(buffer);
			while (iss2 >> word) {
				set_efect_GOOD(word);
			}
	}
	My_file.close();
}


