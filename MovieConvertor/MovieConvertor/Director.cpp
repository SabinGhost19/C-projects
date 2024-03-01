#pragma once
#include"Director.h"

const char* enumToString_personaj(character_type value) {
    switch (value) {
    case PRINCIPAL: return "PRINCIPAL";
    case FIGURANT: return "FIGURANT";
    default: return "[Unknown personaj type]";
    }
}
const char* enumToString_scena(scena_type value) {
    switch (value) {
    case DINAMICA:return"Dinamica";
    case STATICA:return"Statica";
    default:return "[Unknown scena type]";
    }
}
std::ostream& operator<<(std::ostream& os, scena_type value) {
    os << enumToString_scena(value);
    return os;
}
std::ostream& operator<<(std::ostream& os, character_type value) {
    os << enumToString_personaj(value);
    return os;
}
void Director::Take_Scenariu(Scenariu* s) {
    this->Scenariu_Poveste= s;
}

void Director::Print_Movie() {
    std::cout << "\t\t\t\t\t=== " << this->Scenariu_Poveste->Get_nume_scenariu() << "===\n\n\n";
    std::cout << "\n\n\t\tPersonajele ce participante la aceasta poveste sunt: \n\n";
    for (auto personaj : this->Scenariu_Poveste->Get_lista_personaj()) {
        std::cout <<"\t"<< personaj->Get_nume_personaj() <<" ("<<personaj->Get_personaj_type() << ") , jucat de ==>  " << personaj->Get_actor().get_nume() <<" ("<<personaj->Get_actor().get_type()<<")\n\n";
    }
    std::cout << "Firul Narativ la scenelor este urmatorul : ";
    for (auto ID_scena:this->Scenariu_Poveste->Get_Fir_Narativ()) {
        std::cout << ID_scena<<"  ";
    }
    std::cout << std::endl;
    std::cout << "\nDesfasurarea scenelor: " <<"\n\n";
    for (auto scene : this->Scenariu_Poveste->Get_lista_scene()) {
            std::cout << "\n----------------------------------------------------------------------------------------------------------\n\n\n\n";
            std::cout << "\tGradul de compatibilitate al acesteia : " << scene->Get_gradul_compatibilitate() << std::endl;
            std::cout << "\t\nContinutul scenei este: \n\n";
            std::cout << "\t" << scene->Get_Script() << "\n\n\n";
            std::cout << "Cadrul specific al scenei este urmatorul: ";
            for (auto environment_items : scene->Get_environemnt_items()) {
                std::cout << "->" << environment_items << "  ";
            }
            std::cout << "\n\n\n";
            std::cout << "Efectele scenei sunt urmatoarele: \n\n";
            std::cout << "\t\t---Efecte sonore:  ";
            int count = 2;
            for (auto efecte : scene->Get_efecte()) {
                count--;
                std::cout << "\t" << efecte << "\n";
                if (count != 0) {
                    std::cout << "\t\t---Efecte vizuale: ";
                }
            }
            std::cout << "\n\n\n";
            if (!scene->verify_singularity_characters()) {
                std::cout << "\t\tPersonajele care sunt in scena:\t\tTipul de persoanj: \n\n";
                for (auto personaj : scene->Get_lista_personaje_scena()) {

                    std::cout << "\t\t\t" << personaj->Get_nume_personaj()
                        << "    ----------->>>   " << personaj->Get_personaj_type() << "\n";
                }
                std::cout << "\n\n";
            }
            else { std::cout << "\t\t!!!Nu exista personaje in aceasta scena...!!!\n\n"; }
        }
        for (auto personaj : this->Scenariu_Poveste->Get_lista_personaj()) {
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n";
            std::cout << personaj->Get_nume_personaj() << " are urmatoarele replici: \n";
            for (auto replica : personaj->Get_actiuni_personaj()) {
                std::cout << "     -" << replica.second << "  (in scena " << replica.first << ")\n\n";
            }
        }
}
