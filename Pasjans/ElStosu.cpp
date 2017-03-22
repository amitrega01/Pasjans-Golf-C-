#include "Karta.h"
#include "ElStosu.h"

ElStosu::ElStosu(Karta* inKarta) {
	next = nullptr;
	karta = inKarta;
}
void ElStosu::dodaj(int k, int f, bool z) {
	karta = new Karta(k,f,z);
}


void ElStosu::wyswietl() {
	karta->wyswietlKarte();
}


void ElStosu::zmienNast(ElStosu *in) {
	next = in;
}

ElStosu* ElStosu::pobierzNast() {
	return next;
}


ElStosu::~ElStosu() {
	delete karta;
	karta = nullptr;
}