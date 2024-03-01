#pragma once
#include"Class.h"
class Class_Builder
{
public:
    virtual Class getResult()= 0;

    virtual void buildAbility() = 0;
    virtual void buildAttack() = 0;
    virtual void buildDescription() = 0;
    virtual void buildName() = 0;
};

class Warrior_Builder : public Class_Builder {
public:
   
    void buildAbility() override {
        class_.Set_Racial_Ability(CONSTITUTION, 12);
        class_.Set_Racial_Ability(DEXTERITY, 15);
        class_.Set_Racial_Ability(STRENGHT, 12);
    }
    void buildName()override {
        class_.SetName("Warrior");
    }
    void buildAttack()override {

        Attack* new_attack = new Attack("sword", 14, DEXTERITY);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("axe", 15, STRENGHT);
        class_.Set_Attack(new_attack);
    }

    void buildDescription() override {
        std::string de = "Warriors are skilled and formidable fighters, known for their mastery of weapons and combat tactics. They excel in physical strength, endurance, and martial skills. \nOften found on the front lines of battles, warriors are essential protectors and defenders, relying on their training and courage.";
        class_.Set_Description(de);
    }

    Class getResult() override {
        return std::move(class_);
    }

private:
    Class class_;
};


class Wizard_Builder : public Class_Builder {
public:

    void buildAbility() override {
        class_.Set_Racial_Ability(WISDOM, 20);
        class_.Set_Racial_Ability(INTELIGENCE, 18);
        class_.Set_Racial_Ability(DEXTERITY, 15);
        class_.Set_Racial_Ability(STRENGHT, 8);
    }
    void buildName()override {
        class_.SetName("Wizard");
    }
    void buildAttack()override {

        Attack* new_attack = new Attack("Fire Ball", 10,STRENGHT);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("Water Blast", 13, WISDOM);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("Wind Storm", 15, DEXTERITY);
        class_.Set_Attack(new_attack);
    }

    void buildDescription() override {
        std::string de = "Wizards are scholars and practitioners of arcane knowledge. They dedicate their lives to the study of spells, magical theory, and ancient texts. \nWizards typically cast spells using grimoires or wands and often require extensive preparation and knowledge to perform complex magical feats.";
        class_.Set_Description(de);
    }

    Class getResult()override {
        return std::move(class_);
    }

private:
    Class class_;
};


class Sorcerer_Builder : public Class_Builder {
public:

    void buildAbility() override {
        class_.Set_Racial_Ability(STRENGHT, 6);
        class_.Set_Racial_Ability(INTELIGENCE, 15);
        class_.Set_Racial_Ability(DEXTERITY, 11);
        class_.Set_Racial_Ability(STRENGHT, 8);
        class_.Set_Racial_Ability(CHARISMA, 14);
    }
    void buildName()override {
        class_.SetName("Sorcerer");
    }
    void buildAttack()override {

        Attack* new_attack = new Attack("Nether Portal", 18, WISDOM);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("Forest Soul", 13, CONSTITUTION);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("Dark spell Aura", 10, CHARISMA);
        class_.Set_Attack(new_attack);

        new_attack = new Attack("Rocky Wall", 14, STRENGHT);
        class_.Set_Attack(new_attack);
    }

    void buildDescription() override {
        std::string de = "Sorcerers harness magical energies to cast spells and manipulate the forces of the arcane. They are born with innate magical abilities, drawing power from within themselves or from external sources. Sorcerers often specialize in certain types of magic, such as elemental, illusion, or healing magic.";
        class_.Set_Description(de);
    }

    Class getResult() override {
        return std::move(class_);
    }

private:
    Class class_;
};


// Director care utilizeazã builder pentru a construi obiectul
class Class_Builder_Director {
public:
    Class construct(Class_Builder& builder) {
        builder.buildAbility();
        builder.buildDescription();
        builder.buildAttack();
        builder.buildName();
        return std::move(builder.getResult());
    }

};