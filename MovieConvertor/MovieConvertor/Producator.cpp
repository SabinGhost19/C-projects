#include "Producator.h"
void Producator::Do_Job() {
	for (auto scene : this->Scenariu_poveste->Get_lista_scene()) {
			scene->Set_efect(this->Builder.efecte_Sonore(scene->Get_gradul_compatibilitate()));
			scene->Set_efect(this->Builder.efecte_Vizuale(scene->Get_gradul_compatibilitate()));
	}
}

void Producator::Fisier_Out()
{
    std::fstream My_file;
    std::string file = "Producator_Out.txt";

    My_file.open(file, std::ios::out);
    if (My_file.is_open()) {

        My_file << "\n\t\tProducatorul realizeaza urmatoarele functionalitati:  " << "\n\n";
        for (auto scene : this->Scenariu_poveste->Get_lista_scene()) {
                My_file << "\n\tIn SCENA: "<< scene->Get_ID()<<"\n\n";
                My_file << "Efectele scenei sunt urmatoarele: \n\n";
                My_file << "\t\t---Efecte sonore:  ";
                int count = 2;
                for (auto efecte : scene->Get_efecte()) {
                    count--;
                    My_file << "\t" << efecte << "\n";
                    if (count != 0) {
                        My_file << "\t\t---Efecte vizuale: ";
                    }
                }
                My_file << "\n\n\n";
        }
        My_file.close();
    }
}

void Producator::Take_Scenariu(Scenariu*s) {this->Scenariu_poveste = s;}
//Scenariu* Producator::Give_Scenariu()const { return this->Scenariu_poveste;}
