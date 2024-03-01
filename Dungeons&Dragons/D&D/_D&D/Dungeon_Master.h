#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<map>
#include<unordered_map>
#include <fstream>
#include <string>
#include"Creatue_Builder.h"
#include"Class_Builder.h"
#include"Character.h"
#include"Item.h"

//singleton






class Dungeon_Master
{
	
	
	//list of all creatures builted
	// list of all classes builted
	//
	// 
	// din astea 2 o sa se compuna si o sa se realizeze un character : Character(enemies)
	// 
	//std::vector<enemies>list_of_enemies;
	// enemies easy enemies medium enemies hard
	// 
	//std::vector<items>list_of_items;
	// opening and go throught
	// read or just open 

	//o lista de playeri, de Charactere personalizate de jucatori 
	// 
	// FOLOSIND ACEST TEMPLATE: 
	// 
	//template <typename ClassType1, typename ClassType2>
	//class CustomCharacter : public ClassType1, public ClassType2 {
	//public:
	//	CustomCharacter(const typename ClassType1::ParameterType1& param1, const typename ClassType2::ParameterType2& param2)
	//		: ClassType1(param1), ClassType2(param2) {}

	//	// Pute?i adãuga metode suplimentare specifice clasei combinate, dacã este necesar
	//};
private:
	int current_location = 0;
	std::list<std::string>list_creatures;
	std::list<std::string>list_classes;
	std::vector<std::string>all_content;
	std::list<std::unordered_map<int,std::string>>rooms;

	static inline Dungeon_Master* master = nullptr;
	Character* player = nullptr;
public:
	static Dungeon_Master* Get_Instance();

	//Constructors:
	Dungeon_Master(const Dungeon_Master& obj) = delete;
	Dungeon_Master(Dungeon_Master&& obj) = delete;
	void operator=(const Dungeon_Master& obj) = delete;
    Dungeon_Master();

	void Insert_all_the_Items(const char* filename);
	void Insert_all_the_Creatures(const char* filename);
	void Insert_all_the_Classes(const char* filename);

	
	void Play();
	

	void Print_All_Creatures();
	void Print_All_Classes();
	void Print_Room();
	void Print_All_Items();

	void InteractWithDoor(std::string_view type);
	void InteractWitchBook(std::string_view type);
	void InteractWithEnemy(std::string_view type);
	void InteractWitchPortal(std::string_view type);

	std::string& Generate_Item();
	void Generate_Room();
	void Choose_Actions();
	bool Verify_Type(std::string_view type);
	int DiceRoll();
	Character* Generate_Character();
	Class Class_Creation(int index);
	Creature Creature_Creation(int index);
	void Kombat_mode(Character*enemy);
	void CharacterCreator();
	 
	
	//friend std::ostream& operator<<(std::ostream& out, const Ability& ability);
};

