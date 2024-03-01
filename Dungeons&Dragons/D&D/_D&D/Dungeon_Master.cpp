#include "Dungeon_Master.h"

Dungeon_Master* Dungeon_Master::Get_Instance()
{
    if (master == nullptr) {
        return new Dungeon_Master();
    }
    return master;
}

Dungeon_Master::Dungeon_Master()
{
    Insert_all_the_Creatures("Creatures.txt");

    Insert_all_the_Classes("Classes.txt");
   
    Insert_all_the_Items("Dungeon.txt");
}

void Dungeon_Master::Insert_all_the_Items(const char*filename)
{
    //
    std::ifstream inputFile(filename);

    // Verifică dacă fișierul s-a deschis cu succes
    try {
        if (!inputFile.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului!");
            // cu cod de eroare
        }
        std::string item;
        while (inputFile >> item) {

            this->all_content.push_back(item);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        inputFile.close();
    }
    inputFile.close();

}

void Dungeon_Master::Insert_all_the_Creatures(const char* filename)
{
    std::ifstream inputFile(filename);

    // Verifică dacă fișierul s-a deschis cu succes
    try {
        if (!inputFile.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului!");
            // cu cod de eroare
        }
        std::string name;
        while (inputFile >> name) {

                this->list_creatures.push_back(name);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        inputFile.close();
    }
    inputFile.close();

}
   

void Dungeon_Master::Insert_all_the_Classes(const char* filename)
{
    //
    std::ifstream inputFile(filename);

    // Verifică dacă fișierul s-a deschis cu succes
    try {
        if (!inputFile.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului!");
            // cu cod de eroare
        }
        std::string name;
        while (inputFile >> name) {
            
                this->list_classes.push_back(name);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        inputFile.close();
    }
    inputFile.close();

}
std::string& Dungeon_Master::Generate_Item() {
    int index = Random::get(0, static_cast<int>(this->all_content.size())-1);
    return this->all_content[index];
}

void Display_Ability(const Ability& ability) {
    switch (ability) {
    case STRENGHT:
        std::cout << GREEN << "\tSTRENGHT" << RESET;
        break;
    case CHARISMA:
        std::cout << GREEN << "\tCHARISMA" << RESET;
        break;
    case INTELIGENCE:
        std::cout << GREEN << "\tINTELIGENCE" << RESET;
        break;
    case WISDOM:
        std::cout << GREEN << "\tWISDOM" << RESET;
        break;
    case DEXTERITY:
        std::cout << GREEN << "\tDEXTERITY" << RESET;
        break;
    case CONSTITUTION:
        std::cout << GREEN << "\tCONSTITUTION" << RESET;
        break;
    default:
        std::cout << " ";
    }
}
template <typename T>
T& getElementAtPosition(std::list<T>& myList, std::size_t position) {
    auto it = myList.begin();
    std::advance(it, position);
    return *it;
}

void Dungeon_Master::Generate_Room()
{
    int number_of_items = Random::get(2, 6);
    int nr = 0;
    rooms.push_back({ {} });
    auto& map = getElementAtPosition(this->rooms, current_location);
   
    while (number_of_items) {
        std::string item = Generate_Item();
        std::pair<int, std::string > NewPair = std::make_pair(nr, item);
        map.insert(NewPair);

        nr++;
        number_of_items--;
    }
    std::pair<int, std::string > NewPair = std::make_pair(nr, "Door");
    map.insert(NewPair);
}
void Dungeon_Master::Play()
{
        std::cout <<RED<< "THE GAME HAS STARTED...\n"<<RESET;
        CharacterCreator();
       
        this->player->Read_Value_of_Points("value_of_points.txt");
        try {   
            while (1) {
                Generate_Room();
                Choose_Actions();
                current_location++;
            }
        }
        catch (const std::exception e) {
            std::cerr << "Error: " << e.what()<< std::endl;
        }
        catch (const char* end) {
            std::cout<<RED<<end<<RESET<< std::endl;
            std::cout << "\n\n\n\t\tG A M E        O V E R . . . ";
        }
}

void Dungeon_Master::Print_All_Creatures()
{
    std::cout << "Creatures: \n";
    for (auto creature : this->list_creatures) {
        std::cout << creature << "  ";
    }
    std::cout<<std::endl;
}
void Dungeon_Master::Print_All_Items() {
    std::cout << "All Content: \n";
    for (auto content : this->all_content) {
        std::cout << content << "  ";
    }
    std::cout << std::endl;
}
void Dungeon_Master::Print_All_Classes()
{
    std::cout << "Classes: \n";

    for (auto creature : this->list_classes) {
        std::cout << creature << "  ";
    }
    std::cout << std::endl;
}

void Dungeon_Master::Print_Room()
{
    try {
        auto& map = getElementAtPosition(this->rooms, current_location);
        if (map.empty()) { throw("Room is empty..."); }
        for (auto item : map) {
            if (item.second == "Book") {
                std::cout << item.first << ".  " << item.second;
                std::cout << RED<<"->"<<RESET<<CYAN<<"Open 10 inteligence\n"<<RESET;
            }
            if (item.second == "Door") {
                std::cout << item.first << ".  " << item.second;
                std::cout <<RED<<"->"<<RESET<<CYAN<<"Open 10 dexterity\n" << RESET;
            }
            if (item.second == "Portal") {
                std::cout << item.first << ".  " << item.second;
                std::cout <<RED << "->" << RESET << CYAN << "Open 20 inteligence\n" << RESET;
            }
            if (item.second == "Enemy") {
                std::cout << item.first << ".  " << item.second;
                std::cout <<RED<<" ->Fight \n" << RESET;
            }
        }
    }
    catch (const char* error) { std::cout << error<<std::endl; }
}

void Dungeon_Master::InteractWithDoor(std::string_view type)
{
    Item* new_item = new Item(type);
    std::cout << "  " << new_item->Get_Description() << std::endl;
    delete new_item;
}

void Dungeon_Master::InteractWitchBook(std::string_view type)
{
    Item* new_item = new Item(type);
    std::cout <<new_item->Get_Denumire() << ":   " << std::endl;
    std::cout << new_item->Get_Description() << std::endl;
    Ability ability = new_item->Generate_Ability();
    int points = new_item->Generate_Point();
    std::cout << "  " << MAGENTA << points << RESET << "  points of " << GREEN;
    Display_Ability(ability); std::cout<< RESET << std::endl;
    this->player->Update_Ability(points, ability);
    delete new_item;
}

void Dungeon_Master::InteractWithEnemy(std::string_view type)
{
    this->player->Display();
    std::cout << type << std::endl;
    Character* enemy = Generate_Character();//random
    std::cout << RED<<"\n\nYOUR ENEMY:\n"<<RESET;
    enemy->Display();
    Kombat_mode(enemy);
}

void Dungeon_Master::InteractWitchPortal(std::string_view type)
{
    Item* new_item = new Item(type);
    std::cout << "  " << new_item->Get_Description() << std::endl;
    delete new_item;
}

void Dungeon_Master::Choose_Actions()
{
    auto& map = getElementAtPosition(this->rooms, current_location);
    while (1) {
        int choose;
        std::cout << "\n\n";
        Print_Room();
        std::cout << ITALIC<<"Alege obiectul/fiinta de interactiune:  " << "1->" << map.size()-1 << RESET<<std::endl;
        std::cin >> choose;
        if (Verify_Type(map[choose])) {
            map[choose].clear();
            break;
        }
        map.erase(choose);
    }
}
void Print_Dice_BOX( int result) {
    std::cout << RED<<"DICE RESULT IS: \n\n"<<RESET;
    
    std::cout << YELLOW<<"//";
    for (int i = 0; i < 15 - 2; ++i) {
        std::cout << "//";
    }
    std::cout << "//" << std::endl;

    std::cout << "////";
    for (int i = 0; i < 4; ++i) {
        std::cout << "<>";
    }
    std::cout << "  " <<RESET<<GREEN<< result << RESET<<YELLOW<<"  ";
    for (int i = 0; i < 4; ++i) {
        std::cout << "<>";
    }
    std::cout << " ////" << std::endl;

    std::cout << "//";
    for (int i = 0; i < 15 - 2; ++i) {
        std::cout << "//";
    }
    std::cout << "//\n\n"<<RESET<< std::endl;
}
bool Dungeon_Master::Verify_Type(std::string_view type)
{
    system("cls");

    if (type == "Book") {
        std::cout << type<<"\n";
        std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";

        int result = DiceRoll();
        Print_Dice_BOX(result);
        if ((result + this->player->Get_Necesarry_AbilityPNTs(INTELIGENCE)) >= 10) {
            InteractWitchBook(type);
        }
        else { std::cout << "Book couldn't be read...\n"; }
        return false;
    }
    else if (type == "Door") {
        std::cout << type << "\n";
        std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
        int result = DiceRoll();
        Print_Dice_BOX(result);
        if ((result + this->player->Get_Necesarry_AbilityPNTs(DEXTERITY)) >= 10) {
            {
                InteractWithDoor(type);
                return true;
            }
        }
        else { std::cout << "Door couldn't be open...\n"; }
        return false;
    }
    else if (type == "Portal") {
        std::cout << type << "\n";
        std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n";
        int result = DiceRoll();
        Print_Dice_BOX(result);
        if ((result + this->player->Get_Necesarry_AbilityPNTs(WISDOM)) >= 10) {
            {
                InteractWitchPortal(type);
                return true;
            }
            return false;
        }
    }
    else if (type == "Enemy") {
        try {
            InteractWithEnemy(type);
        }
        catch (int final) {
            std::cout << RED<<"!!!!---The enemy has been killed---!!!!\n" <<RESET<< std::endl;
        }
        return false;
    }
}

int Dungeon_Master::DiceRoll(){return Random::get(1, 20);}

Character* Dungeon_Master::Generate_Character()
{
    Creature creature;
    Class class_type;

    Character* character = new Character();
    int nr=Random::get(1, this->list_classes.size());
    creature = Creature_Creation(nr);

     nr = Random::get(1, this->list_classes.size());
     class_type = Class_Creation(nr);

     character->Set_Class(std::move(class_type));
     character->Set_Creature(std::move(creature));

    return character;
}

Class Dungeon_Master::Class_Creation(int index)
{
    Class_Builder_Director class_director;
    Class class_type;

    switch (index) {
    case 1:
    {
        Warrior_Builder warrior_builder;
        class_type = class_director.construct(warrior_builder);
        break;
    }
    case 2:
    {
        //putem adauga move constructor
        Wizard_Builder wizard_builder;
        class_type = class_director.construct(wizard_builder);
        break;
    }
    case 3: {
        Sorcerer_Builder sorcerer_builder;
        class_type = class_director.construct(sorcerer_builder);
    }
    }
    return class_type;//si apeleaza move semantics ... nu trebuie explicit
}

Creature Dungeon_Master::Creature_Creation(int index)
{
    Creature_Builder_Director director;
    Creature creature;

    switch (index) {
    case 1:
    {
        Human_Builder human_builder;
        creature = director.construct(human_builder);
        break;
    }
    case 2:
    {
        //adaugat  move constructor
        Elf_Builder elf_builder;
        creature = director.construct(elf_builder);
        break;
    }
    case 3: {
        Orc_Builder orc_builder;
        creature = director.construct(orc_builder);
    }
    }



    return creature;
}

void Dungeon_Master::Kombat_mode(Character* enemy)
{
    std::cout << "\n\n\n";
    int dice_value;
    int required_points;
    while (1) {

        required_points = this->player->Attack(true);
        dice_value=DiceRoll();
        Print_Dice_BOX(dice_value);

        std::cout <<ITALIC<<" Minimum points required: "
            <<required_points<<RESET<<std::endl;

        if (required_points <= dice_value) {
            std::cout << RED<<"--HIT--\n"<<RESET;
            enemy->Get_Hit(dice_value);
            std::cout<<"Remain Health of the enemy:  " << GREEN<<enemy->Get_Health() <<RESET<< std::endl;
        }
        else { std::cout << "--MISS--\n"; }

        if (enemy->Get_Health() <= 0) { throw(1); }

        required_points = enemy->Attack(false);
        dice_value = DiceRoll();
        if (required_points <= dice_value) {
            std::cout << "\n\nEnemy turn:"<<RED<< "--HIT----\n\n"<<RESET;
            std::cout << "Enemy hit damage was: " << dice_value<<std::endl;
            this->player->Get_Hit(dice_value);
            std::cout << GREEN<<"Your Remain Health: " <<RESET<<YELLOW<< this->player->Get_Health() <<RESET<< std::endl;
        }
        else { std::cout <<YELLOW<< "\n\nEnemy turn: --MISS--\n\n"<<RESET; }

        if (this->player->Get_Health() <= 0) { throw("You have been killed by the enemy!"); }

    }
}

void Dungeon_Master::CharacterCreator()
{
    std::cout << "THIS IS THE CHARACTER CREATOR: \n";
    Creature creature;
    Class class_type;
    std::cout << ITALIC<<"\t(selectia se va face prin introducerea unei cifre corespunzatoare ordinii elementelor)\n\n"<<RESET;
    int who;
    Print_All_Creatures();
    std::cout << YELLOW<<"Alege Creatura\n"<<RESET;
    std::cin >> who;
    creature=Creature_Creation(who);

    Print_All_Classes();
    std::cout << YELLOW<<"Alege Classa?\n"<<RESET;
    std::cin >> who;
    class_type=Class_Creation(who);

    this->player=new Character();
    std::string nume_propriu;
    std::cout << GREEN<<"Introduceti numele caracterului: \n"<<RESET;
    std::cin >> nume_propriu;
    player->Set_Name(nume_propriu);

    //Move constructor
    player->Set_Creature(std::move(creature));
    player->Set_Class(std::move(class_type));
    system("cls");
    player->Display();
   // player->Get_ClassType().Display_Class();
    //player->Get_CreatureType().Display_Creature();
}


