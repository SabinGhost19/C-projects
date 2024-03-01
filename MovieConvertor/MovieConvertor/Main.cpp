#include"MTA_Studios.h"


int main(int argc,char*argv[]) {

	MTA_Studios::Get_Scenarist()->citire_poveste("Poveste.txt");
	MTA_Studios::Get_Scenarist()->Fisier_Out();

	MTA_Studios::Get_Regizor()->Take_Scenariu(MTA_Studios::Get_Scenarist()->Give_scenariu());
	MTA_Studios::Get_Regizor()->make_regizor_part();
	MTA_Studios::Get_Regizor()->Call_Producator(MTA_Studios::Get_Producator());
	MTA_Studios::Get_Regizor()->Fisier_Out();

	MTA_Studios::Get_Director()->Take_Scenariu(MTA_Studios::Get_Regizor()->Give_scenariu());

	MTA_Studios::Get_Director()->Print_Movie();

	return 0;
}