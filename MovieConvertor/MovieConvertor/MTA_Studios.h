#pragma once
#include<iostream>
#include"Director.h"
//SINGLETON
class MTA_Studios
{   
	Director* director=nullptr; 
	Scenarist* scenarist=nullptr; 
	Regizor *regizor=nullptr; 
	Producator *producator=nullptr;

	std::string nume_poveste;
	~MTA_Studios(){}
protected:
	MTA_Studios(const std::string value_param ):nume_poveste(value_param){}
public:


	static Director* Get_Director();
	static Scenarist* Get_Scenarist();
	static Regizor* Get_Regizor();
	static Producator* Get_Producator();


	static std::string Get_name();
	static MTA_Studios* Get_Instance(const std::string value_param = "---");

	MTA_Studios(const MTA_Studios& other) = delete;  //delete copu constructor
	void operator=(const MTA_Studios& other) = delete;  // delete asgnament
	MTA_Studios() = delete;  //delete constructor

	
	



};

