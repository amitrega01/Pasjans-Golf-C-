/*
Created by Adam Mitrêga @ date
*/
#include "Karta.h"
#include "Stos.h"
#include "Coords.h"

Stos::Stos() {
	wierzcholek = nullptr;
}

void Stos::push(Karta* karta) { //dodaje element na stos
	ElStosu *bufor;
	bufor = new ElStosu(karta);
	bufor->zmienNast(wierzcholek);
	wierzcholek = bufor;
	bufor = nullptr;
}

void Stos::wyswietlKolumna(int w, int k, bool a) { //wyswietla elementy stosu od dolu do gory
	w += 3;
	ElStosu *bufor = wierzcholek;
	if (bufor != nullptr) {
		gotoXY(k * 5, w);
		if (a) {
			SetConsoleTextAttribute(console, 240);
		}
		wyswietlWierzcholek();
		SetConsoleTextAttribute(console, 15);
		bufor = bufor->pobierzNast();

		while (bufor != nullptr) {
			gotoXY(k * 5, w - 1);
			bufor->wyswietl();
			bufor = bufor->pobierzNast();
			w--;
		}
	} else if (a) {
		gotoXY(k * 5, 3);
		SetConsoleTextAttribute(console, 240);
		std::cout << "     ";

		SetConsoleTextAttribute(console, 15);
	}
}

void Stos::wyswietl() { //wyswielta elementy stsu od lewej do prawej
	ElStosu *bufor = wierzcholek;
	while (bufor != nullptr) {
		bufor->wyswietl();
		bufor = bufor->pobierzNast();
	}
}

ElStosu* Stos::pop() { //usuwa element ze stosu i zwraca go 
	ElStosu *bufor = wierzcholek;
	if (wierzcholek != nullptr)
	{
		wierzcholek = wierzcholek->pobierzNast();
	}
	bufor->karta->zakryta = false;
	return bufor;
}

int Stos::getValue() { //zwraca figure karty na stosie

	return wierzcholek->karta->figura;
}

int Stos::policz() {  //liczy ile jest kart na stosie, przydatne do wyswietlania jako kolumna
	ElStosu *bufor = wierzcholek;
	int a = -1;
	while (bufor != nullptr) {
		bufor = bufor->pobierzNast();
		a++;
	}
	return a;
}

void Stos::odwrocKarty() {
	ElStosu *bufor = wierzcholek;
	int a = 2;
	while (bufor != nullptr) {
		bufor->karta->zakryta = !bufor->karta->zakryta;
		bufor = bufor->pobierzNast();
	}
}

void Stos::wyswietlWierzcholek() { //wyswietla karte na wierzcholku stosu
	wierzcholek->wyswietl();
}

void Stos::czysc() { //czysci stos
	ElStosu *bufor;
	while (wierzcholek != nullptr) {
		bufor = wierzcholek;
		wierzcholek = wierzcholek->pobierzNast();
		delete bufor;
	}
}

Stos::~Stos() {
	czysc();
}