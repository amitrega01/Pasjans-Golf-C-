/*
Created by Adam Mitrêga @ date
*/

#pragma once
#include "Karta.h"

class ElStosu
{
public:
	Karta* karta;
	ElStosu* next;

	ElStosu(Karta* inKarta);
	void dodaj(int k, int f, bool z);
	void wyswietl();
	void ElStosu::zmienNast(ElStosu *in);
	ElStosu* pobierzNast();
	ElStosu::~ElStosu();
};
