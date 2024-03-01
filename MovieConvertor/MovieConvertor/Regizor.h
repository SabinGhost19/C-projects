#pragma once
#include "Entity.h"
#include"Scenarist.h"
#include"Actor.h"
#include"Environment.h"
#include"Producator.h"
#include<list>

class Regizor :  public Entity
{
    Scenariu* Scenariu_poveste = nullptr;
    std::list<Actor*>lista_actori;
    Environment environment_creator;

public:
    Regizor(std::string nume) :Entity(nume) { }
    Scenariu* Give_scenariu()const;
    void creare_lista_actori();
    void Take_Scenariu(Scenariu*s);
    void create_Environement();
    void asignare_actori();
    void compatibility_grade();
    void make_regizor_part();
    void Call_Producator(Producator* Producer);
    int modify_state(character_type type1, character_type type2,int state);

    virtual void Fisier_Out()override;
};

