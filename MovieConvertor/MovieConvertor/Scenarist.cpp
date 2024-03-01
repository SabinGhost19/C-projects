#include"Scenarist.h"

bool verify_Dinamical_scene(std::string sir) {
	std::string primulCuvant;
	size_t pozitieSpatiu = sir.find(' ');
	// Verificăm dacă spațiul a fost găsit
	if (pozitieSpatiu != std::string::npos) {
		primulCuvant = sir.substr(0, pozitieSpatiu);
	}
	if (primulCuvant[static_cast<size_t>(primulCuvant.size()-1)] == ':') { return true; }
	return false;
}
bool not_sentence_begining(std::string word) {
	if (word[0] == '.' || word[0] == '!' || word[0] == '?') { return true; }
	return false;
}
void Scenarist::add_characters(std::string script, Scena* scena) {
	std::string word;
	std::istringstream iss(script);
	iss >> word;
	int count = 0;
	while (iss >> word) {
		if (std::isupper(word[0]) && count != 0 && (!not_sentence_begining(word))) {
			if (!scena->verify_existence_personaj(word)) {
				if (this->Scenariu_poveste->verify_existence_personaj(word)) {
					Personaj* new_scene_personaj = this->Scenariu_poveste->Get_personaj_existent(word);
					
					scena->add_personaj(new_scene_personaj);
				}
				else {
					Personaj* personaj = new Personaj(word);
					this->Scenariu_poveste->Get_lista_personaj().push_back(personaj);
					scena->add_personaj(personaj);
				}
			}
		}
		count++;
	}
}
void Scenarist:: add_character_in_Scenariu(std::string script) {
	std::string word;
	std::istringstream iss(script);
	iss >> word;
	int count = 0;
	while (iss >> word) {
		if (std::isupper(word[0]) && count != 0) {
			if (!this->Scenariu_poveste->verify_existence_personaj(word)) {
				Personaj* personaj = new Personaj(word);
				this->Scenariu_poveste->Get_lista_personaj().push_back(personaj);
			}
		}
		count++;
	}
}
size_t find_ending(std::string sir) {
	size_t pozitieEnd = sir.find('\n');
	if (pozitieEnd == std::string::npos) {
		pozitieEnd = sir.find('.');
		if (pozitieEnd == std::string::npos) {
			pozitieEnd = sir.find('!');
			if (pozitieEnd == std::string::npos) {
				pozitieEnd = sir.find('?');
			}
		}
	}
	return pozitieEnd;
}

void Scenarist::add_dialoguri(std::string sir_complet,Scena*scena,int counter) {
	while (sir_complet != "") {
		if (counter == 0) { sir_complet = sir_complet.substr(1); }
		counter++;
		size_t pozitieEnd = find_ending(sir_complet);
		std::string dialog;
		// Verificăm dacă caracterul '\n' a fost găsit
		if (pozitieEnd != std::string::npos) {
			// Extragem subsirul până la caracterul '\n'
			dialog = sir_complet.substr(0, pozitieEnd);

			// Eliminăm subsirul din șirul complet
			sir_complet.erase(0, pozitieEnd + 1);
		}
		std::string name;
		//extragem cuvantul 
		size_t pozitiePrimulSpatiu = dialog.find(' ');
		if (pozitiePrimulSpatiu != std::string::npos) {
			name = dialog.substr(0, pozitiePrimulSpatiu);
			dialog.erase(0, pozitiePrimulSpatiu + 1);
		}
		//eliminam :
		size_t pozitieDouaPuncte = name.find(':');
		if (pozitieDouaPuncte != std::string::npos) {
			name.erase(pozitieDouaPuncte, 1);
		}

		add_characters(dialog, scena);
		
		if (!scena->verify_existence_personaj(name)) {
			if (this->Scenariu_poveste->verify_existence_personaj(name)) {
				Personaj* new_scene_personaj = this->Scenariu_poveste->Get_personaj_existent(name);
				
				scena->add_personaj(new_scene_personaj);
			}
			else {
				Personaj* personaj = new Personaj(name);
				this->Scenariu_poveste->Get_lista_personaj().push_back(personaj);
				scena->add_personaj(personaj);
			}
		}
		//adugare linie de dialog:
		for (auto index : this->Scenariu_poveste->Get_lista_personaj()) {
			if (index->Get_nume_personaj() == name) {
				index->Set_dialog(scena->Get_ID(), dialog);
			}
		}
	}

}
void Scenarist::add_scena(Scena* s) {
	this->Scenariu_poveste->Get_lista_scene().push_back(s);
}
void Scenarist::add_order_in_FN(int ID) {
	this->Scenariu_poveste->Get_Fir_Narativ().push_back(ID);
}
void Scenarist::Fisier_Out() {
	std::fstream My_file;
	std::string file = "Scenarist_Out.txt";

	My_file.open(file, std::ios::out);
	if (My_file.is_open()) {
		My_file << "\n\t\tScenaristul realizeaza urmatoarele functionalitati: " << "\n\n";
		My_file << "\tCitirea datelor din fisier si selectarea atat a scenelor cat si a personajelor impreuna cu dialogurile acestora: \n\n\n";
		My_file << "\tTitlul acestei Povesti este: " << this->Scenariu_poveste->Get_nume_scenariu().erase(0, 3) << "\n\n\n";
		My_file << "\n\n\t\tPersonajele ce participante la aceasta poveste sunt: \n\n";
		for (auto personaj : this->Scenariu_poveste->Get_lista_personaj()) {
			My_file << "\t" << personaj->Get_nume_personaj() << " (";
			if (personaj->Get_personaj_type() == 0) {
				My_file << "Principal)\n\n\n";
			}
			else {
			My_file << "Secundar)\n\n\n";
				}
		}
		My_file << "Firul Narativ la scenelor este urmatorul : ";
		for (auto ID_scena : this->Scenariu_poveste->Get_Fir_Narativ()) {
			My_file << ID_scena << "  ";
		}
		My_file <<"\n\n";
		My_file << "\nDesfasurarea scenelor conform firului narativ : " << "\n\n";
			for (auto scene : this->Scenariu_poveste->Get_lista_scene()) {
				My_file << "\t\nContinutul scenei "<<scene->Get_ID()<<" : \n\n";
				My_file << "\t" << scene->Get_Script() << "\n\n\n";
				My_file << "Cadrul specific al scenei este urmatorul: ";
			
				
				My_file << "\n\n\n";
				if (!scene->verify_singularity_characters()) {
					My_file << "\t\tPersonajele care sunt in scena:\t\tTipul de persoanj: \n\n";
					for (auto personaj : scene->Get_lista_personaje_scena()) {

						My_file << "\t\t\t" << personaj->Get_nume_personaj()<<"\n";
					}
					My_file << "\n\n";
				}
				else { My_file << "\t\t!!!Nu exista personaje in aceasta scena...!!!\n\n"; }
			}My_file << "\n\n\n";
			My_file << "\t\tPersonajele din intreaga poveste au urmatoarele replici:\n\n\n";
			for (auto personaj : this->Scenariu_poveste->Get_lista_personaj()) {
				My_file << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n";
				My_file << personaj->Get_nume_personaj() << " are urmatoarele replici: \n";
				for (auto replica : personaj->Get_actiuni_personaj()) {
					My_file << "     -" << replica.second << "  (in scena " << replica.first << ")\n\n";
				}
			}
			My_file.close();
    }
	

}
void Scenarist::citire_poveste(const char* nume_poveste) {
	this->Scenariu_poveste = new Scenariu();
	std::string file = nume_poveste;
	std::fstream My_file;
	std::string word;
	std::string buffer_line;
	
	//OBSERVATOR DESIGN PATTERN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	My_file.open(file, std::ios::in);
	if (My_file.is_open()) {
		std::getline(My_file, buffer_line,'\n');

		this->Scenariu_poveste->Set_nume_scenariu(buffer_line);//nume poveste 

		while (!My_file.eof()) {
			
			std::getline(My_file, buffer_line,'/');
			if (buffer_line == "") { break; }
			Scena* new_scena = new Scena(buffer_line);
			
			if (verify_Dinamical_scene(buffer_line)) {
				new_scena->Set_tip_scena(DINAMICA);
				int counter = 0;
				add_dialoguri(buffer_line,new_scena,counter);

			}else{ new_scena->Set_tip_scena(STATICA);
			       add_characters(buffer_line,new_scena);
			}

			this->add_scena(new_scena);
			this->add_order_in_FN(new_scena->Get_ID());
			
		}
		 Set_characters_type();
		My_file.close();
	}
}

void Scenarist::Set_characters_type()
{
	for (auto personaj : this->Scenariu_poveste->Get_lista_personaj()) {
		int count = 0;
		for (auto  scena: this->Scenariu_poveste->Get_lista_scene()) {
			for (auto personaj_scena : scena->Get_lista_personaje_scena()) {
				if (personaj == personaj_scena) {
					count++;
				 }
			}
		}
			if (count > 4) {
				personaj->Get_personaj_type(PRINCIPAL);
			}
			else { personaj->Get_personaj_type(FIGURANT); }
	}
}
Scenariu* Scenarist::Give_scenariu()const { return this->Scenariu_poveste; }
