#pragma once
#include"Creature.h"

class Creature_Builder {
public:
    virtual Creature getResult() = 0;

    virtual void buildAbility() = 0;
    virtual void buildHealth() = 0;
    virtual void buildAttack() = 0;
    virtual void buildCategory() = 0;
    virtual void buildBackGround() = 0;
};


class Human_Builder : public Creature_Builder {
public:
    void buildCategory() override {
        creature.Set_Category("Human");
    }

    void buildAbility() override {
        creature.Set_Racial_Ability(CHARISMA,13);
        creature.Set_Racial_Ability(DEXTERITY,17);
        creature.Set_Racial_Ability(STRENGHT,12);
    }

    void buildHealth() {
        creature.Set_Health(100);
    }

    void buildAttack()override {

        Attack* new_attack = new Attack("punch",10,STRENGHT);
        creature.Set_Attack(new_attack);

        new_attack = new Attack("kick", 11, STRENGHT);
        creature.Set_Attack(new_attack);
    }

    void buildBackGround() override{
        std::string bg="Versatile and diverse, humans exhibit adaptability and ambition.\n In Middle-earth, they are warriors, craftsmen, and diplomats, forming the backbone of alliances and facing the challenges of an ever-changing world.";
        creature.Set_BackGround(bg);
    }

    Creature getResult() override {
        return std::move(creature);
    }

private:
    Creature creature;
};


class Orc_Builder : public Creature_Builder {
public:
    void buildCategory() override {
        creature.Set_Category("Orc");
    }

    void buildAbility() override {
        creature.Set_Racial_Ability(CONSTITUTION, 20);
        creature.Set_Racial_Ability(INTELIGENCE, 6);
        creature.Set_Racial_Ability(STRENGHT, 26);
    }

    void buildHealth() {
        creature.Set_Health(130);
    }

    void buildAttack()override {

        Attack* new_attack = new Attack("punch", 11, STRENGHT);
        creature.Set_Attack(new_attack);

        new_attack = new Attack("kick", 13, STRENGHT);
        creature.Set_Attack(new_attack);
    }

    virtual void buildBackGround() {
        std::string bg = "Born of darkness and chaos, orcs are brutish warriors in the service of dark overlords. \nWith coarse features and menacing demeanor, they thrive in cruelty and cunning, wielding destructive weapons in the vanguard of dark armies.";
        creature.Set_BackGround(bg);
    }

    Creature getResult()override {
        return std::move(creature);
    }

private:
    Creature creature;
};




class Elf_Builder : public Creature_Builder {
public:
    void buildCategory() override {
        creature.Set_Category("Elf");
    }

    void buildAbility() override {
        creature.Set_Racial_Ability(WISDOM, 14);
        creature.Set_Racial_Ability(INTELIGENCE, 19);
        creature.Set_Racial_Ability(STRENGHT, 6);
        creature.Set_Racial_Ability(CHARISMA, 13);
    }

    void buildHealth() {
        creature.Set_Health(80);
    }

    void buildAttack()override {

        Attack* new_attack = new Attack("punch", 8, STRENGHT);
        creature.Set_Attack(new_attack);

        new_attack = new Attack("kick", 11, STRENGHT);
        creature.Set_Attack(new_attack);
    }

    virtual void buildBackGround() {
        std::string bg = "Graceful and ageless beings, elves boast ethereal beauty and unmatched skill in archery and magic. Hidden in ancient forests, their cities radiate wisdom and enchantment.";
        creature.Set_BackGround(bg);
    }

    Creature getResult()override {
        return std::move(creature);
    }

private:
    Creature creature;
};









// Director care utilizează builder pentru a construi obiectul
class Creature_Builder_Director {
public:
    Creature construct(Creature_Builder& builder) {
        builder.buildAbility();
        builder.buildCategory();
        builder.buildAttack();
        builder.buildHealth();
        return std::move(builder.getResult());
    }



    /*CarBuildDirector carDirector;
    SportsCarBuilder sportsCarBuilder;

    Car sportsCar = carDirector.construct(sportsCarBuilder);
    sportsCar.display();*/

    //folosirea corecta a builderului

};


