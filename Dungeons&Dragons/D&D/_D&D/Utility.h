#pragma once
#include <chrono>
#include <random>
#include"stdexcept"
#define CYAN    "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"
#define ITALIC  "\x1b[3m"
#define MAGENTA "\x1b[35m"
typedef enum Ability {
	CHARISMA,// measuring force of personality
	STRENGHT,//measuring physical power
	INTELIGENCE,//measuring reasoning and memory
	WISDOM,//easuring perception and insight
	DEXTERITY,//measuring agility
	CONSTITUTION//measuring endurance
};


typedef enum Enemy_LVL {
	EASY,
	MEDIUM,
	HARD
};

typedef struct Attack {
	std::string description;
	int points;
	Ability bonus_ability;

	Attack(const std::string&description_p, int points_p,const Ability&ability_p)
		:description(description_p),points(points_p),bonus_ability(ability_p){}
}Attack;

namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	inline std::mt19937 mt{ generate() };


	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{ min, max }(mt);
	}
}