

#pragma once

#include "ElStosu.h"
class Stos
{
private:


public:
	Stos();
	~Stos();
	ElStosu* wierzcholek;
	void push(Karta *karta);
	ElStosu* pop();
	int getValue();
	int policz();
	void wyswietlKolumna(int w, int k, bool a);
	void wyswietl();
	void wyswietlWierzcholek();
	void czysc();
	void odwrocKarty();

};

