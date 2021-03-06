
#include "Karta.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <Windows.h>

Karta::Karta(int k, int f, bool z)
{
	kolor = k;
	figura = f;
	zakryta = z;
}
Karta::~Karta()
{
}
void Karta::wyswietlKarte() { //funkcja rysujaca karte 
	char k;
	if (zakryta)
	{
		std::cout << std::setw(5) << "|###|";
	} else
	{
		std::cout << '|';
		if (figura < 10 && figura != 1) std::cout << " " << figura;
		else {
			switch (figura) {
			case 1: std::cout << "AS"; break;
			case 10: std::cout << "10"; break;
			case 11: std::cout << " J"; break;
			case 12: std::cout << " Q"; break;
			case 13: std::cout << " K"; break;
			default:
				break;
			}
		}
		switch (kolor)
		{
		case 1: k = 't'; break;
		case 2: k = 'c'; break; 
		case 3: k = 'k'; break;
		case 4: k = 'p'; break;
		default:
			break;
		}
		std::cout << k << "|";
	}
}