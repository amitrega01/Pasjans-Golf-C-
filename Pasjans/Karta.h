#pragma once
class Karta
{
public:
	Karta(int k, int f, bool z);
	~Karta();
	int kolor, figura;
	bool zakryta;
	void wyswietlKarte();
};

