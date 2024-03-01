#include"Dungeon_Master.h"

int main(int argc, char argv[]) {

	Dungeon_Master* d = Dungeon_Master::Get_Instance();

	d->Play();

	//toate creaturile sunt hardcodate si deja implemntate in builder 

	return 0;
}