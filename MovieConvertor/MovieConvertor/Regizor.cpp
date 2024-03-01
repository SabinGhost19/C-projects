#include "Regizor.h"

void Regizor::creare_lista_actori()
{
    std::fstream My_file;
    std::string filename = "Actori.txt";
    std::string buffer;

    My_file.open(filename, std::ios::in);
    if (My_file.is_open()) {
        while (My_file >> buffer) {
            Actor* new_actor = new Actor(buffer);
            My_file >> buffer;
            int stare_integer = std::stoi(buffer);
            new_actor->set_stare_spirit(stare_integer);
            My_file >> buffer;
            if(buffer=="Principal"){ new_actor->set_type(PRINCIPAL); }
            else{ new_actor->set_type(FIGURANT); }
            this->lista_actori.push_back(new_actor);
        }
    }
}

void Regizor::Take_Scenariu(Scenariu*s)
{
    Scenariu_poveste = s;
}

void Regizor::create_Environement()
{
    for (auto index : Scenariu_poveste->Get_lista_scene()) {
        index->insert_environment_items(this->environment_creator.createEnv(Elemente_naturale));
        index->insert_environment_items(this->environment_creator.createEnv(Momentul_zilei));
        index->insert_environment_items(this->environment_creator.createEnv(Starea_vremii));
        std::cout << std::endl << std::endl;
    }
}
int Regizor::modify_state(character_type type1, character_type type2,int state) {

    if (type1 == type2) { return state * 2; }
    return state / 2;

}
void Regizor::Fisier_Out()
{
    std::fstream My_file;
    std::string file = "Regizor_Out.txt";

    My_file.open(file, std::ios::out);
    if (My_file.is_open()) {

        My_file << "\n\t\tRegizorul realizeaza urmatoarele functionalitati: " << "\n\n";
        My_file << "\n\tDeterminarea grdului de compatibilitate si creerea unui cadru specific\n\t\tDar si deteminarea si asignarea actorilor fiecarui personaj: " << "\n\n";
        
        for (auto personaj : this->Scenariu_poveste->Get_lista_personaj()) {
            My_file << "\t" << personaj->Get_nume_personaj() << " (";
            if (personaj->Get_personaj_type() == 0) {
                My_file << "Principal) ";
            }
            else {
                My_file << "Secundar) ";
            }
            
            My_file << ", jucat de ==> " << personaj->Get_actor().get_nume() << " (";
            if (personaj->Get_actor().get_type() == 0) {
                My_file << "Principal)\n\n\n";
            }
            else {
                My_file << "Secundar)\n\n\n";
            }
        }
        My_file << "\n\tFiecare Scena contine: " << "\n\n";

     
            for (auto scene : this->Scenariu_poveste->Get_lista_scene()) {
                if (!scene->Get_lista_personaje_scena().empty()) {
                    My_file << "\tGradul de compatibilitate al scenei " << scene->Get_ID() << " : " << scene->Get_gradul_compatibilitate()<<"\n";
                }
                else { My_file << "\tNu exista grad de compatibilitate deoarece nu sunt prezente persoanje in aceasta scena...\n"; }
                My_file << "\tCadrul specific al scenei este urmatorul: ";
                for (auto environment_items : scene->Get_environemnt_items()) {
                    My_file << "->" << environment_items << "  ";
                }
                My_file << "\n\n\n";
            }
        }
        My_file.close();
    
}
void Regizor::asignare_actori()
{
    if (this->Scenariu_poveste->Get_lista_personaj().size() > this->lista_actori.size()) { std::cout << "Nr dea actori prea putini..."; exit(-1); }
    for (auto personaj : this->Scenariu_poveste->Get_lista_personaj()) {
        Actor*actor_temp=this->lista_actori.front();
        actor_temp->set_stare_spirit(modify_state(personaj->Get_personaj_type(),actor_temp->get_type(),actor_temp->get_stare_spirit()));
        personaj->Set_actor(this->lista_actori.front());
        this->lista_actori.pop_front();
    }
}

void Regizor::compatibility_grade()
{
    int sum_stare_spirit = 0;
    for (auto scena : this->Scenariu_poveste->Get_lista_scene()) {
        if (!scena->verify_singularity_characters()) {
            for (auto personaj : scena->Get_lista_personaje_scena()) {
                sum_stare_spirit += personaj->Get_actor().get_stare_spirit();
            }
            scena->Set_grad_comp((sum_stare_spirit * 0.5) / static_cast<size_t>(scena->Get_lista_personaje_scena().size()));
        }
        else { scena->Set_grad_comp(0); }
    }
}

void Regizor::Call_Producator(Producator* Producer) {
    Producer->Take_Scenariu(this->Scenariu_poveste);
    Producer->Do_Job();
    Producer->Fisier_Out();
}

Scenariu* Regizor::Give_scenariu()const { return this->Scenariu_poveste; }
void Regizor::make_regizor_part()
{
    
    creare_lista_actori();
    create_Environement();
    asignare_actori();
    compatibility_grade();
}
