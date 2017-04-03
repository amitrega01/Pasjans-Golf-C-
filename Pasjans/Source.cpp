#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <algorithm>
#include "Karta.h"
#include "ScoreHan.h"
#include "Stos.h"

using namespace std;

HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);

const int rozmiarTalii = 52;
const int kartyGracza = 12;
const int kartyStol = rozmiarTalii - kartyGracza;
bool b = false; //wlacza dzwieki
int aktywnaKolumna;

Karta* karta[rozmiarTalii];
Stos talia;
Stos gracza;
Stos graczaZ;
Stos kol[7];

ScoreHan scoreHan;

bool koniec = false;
char key;
//naglowki
void gotoXY(int x, int y);
void getCursorXY(int &x, int&y);
void checkInput();
void create();
void render();
void menu();
void gameover();
void dispose();
void checkWin();
int main();

void checkWin() {
	if (scoreHan.score == 4400) gameover();
}

void dispose() { //usuwa wszystkie elementy zeby nie powodowalo wyciekow pamieci itp
	talia.czysc();
	gracza.czysc();
	graczaZ.czysc();
	scoreHan.~ScoreHan();
	for (int i = 0; i < 7; i++) {
		kol[i].czysc();
	}
}

void checkInput() { //sprawdza klawisze wprowadzane przez gracza
	while (1) {
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case'A': {
				if (aktywnaKolumna > 0) {
					aktywnaKolumna--;
				}
				render();
				break;
			}
			case 'D': {
				if (aktywnaKolumna < 7) {
					aktywnaKolumna++;
				}
				render();
				break;
			}
			case'a': {
				if (aktywnaKolumna > 0) {
					aktywnaKolumna--;
				}
				render();
				break;
			}
			case 'd': {
				if (aktywnaKolumna < 7) {
					aktywnaKolumna++;
				}
				render();
				break;
			}
			case 's': { //sprawdza czy kolumna na ktorej jest gracz ma wierzcholek o 1 mniejszy lub wiekszy od karty na kupce gracza
				if (kol[aktywnaKolumna].wierzcholek != nullptr)
					if (kol[aktywnaKolumna].getValue() + 1 == gracza.getValue() || kol[aktywnaKolumna].getValue() - 1 == gracza.getValue()) {
						scoreHan.score += 110; gracza.push(kol[aktywnaKolumna].pop()->karta); if (b)  Beep(800, 200);
					} else {
						if (b) Beep(500, 200);
					}
				render();
				break;
			}
			case 'q': {
				dispose();
				menu();
				break;
			}
			case ' ': {
				if (graczaZ.wierzcholek != nullptr) {
					gracza.push(graczaZ.pop()->karta);
				} else {
					gameover();
					break;
				}
				render();
				break;
			}
			default:
				break;
			}
		}
	}
}

void create() { //funkcja inicjiujaca, inicjuje zmienne, resetuje wyniki, twrzy i tasuje talie
	srand(time(0));
	scoreHan.score = 0;
	aktywnaKolumna = 0;
	//generowanie talii
	for (int i = 0; i < rozmiarTalii; i++) {
		karta[i] = new Karta(i % 4 + 1, i % 13 + 1, false); //definiowanie nowej karty
	}
	random_shuffle(&karta[0], &karta[rozmiarTalii]);
	for (int i = 0; i < rozmiarTalii; i++) {
		talia.push(karta[i]); // funkcja push dodaje karte na stos, tu z tabeli
	}
	//wykladanie kart graczowi
	for (int i = 0; i < kartyGracza; i++) {
		graczaZ.push(talia.pop()->karta); //odaje karty z talii do kupki gracza, funkcja pop kasuje karte ze stosu i zwraca ja, dzieki czemu mozna ja przelozyc na inny stos
	}
	graczaZ.odwrocKarty(); //odwaca kart zeby nie byly widoczne
	gracza.push(graczaZ.pop()->karta);
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j < 5; j++) {
			kol[i].push(talia.pop()->karta); //wydaje karty na stol do 8 stosow po 5 kart
		}
		cout << endl; 
	}
	render();
}

void render() { //funkcja rysujaca, rysuje nowy ekran po wprowadzeniu klawisza
	system("cls");
	cout << "########################################" << endl;
	cout << "              PASJANS GOLF" << endl;
	cout << "########################################" << endl;
	for (int i = 0; i <= 7; i++) {
		int wysokosc = kol[i].policz();
		if (aktywnaKolumna == i) {
			kol[i].wyswietlKolumna(wysokosc, i, true); //wysswietla stos w kolumnie, a nie tak jak zwykle od lewej do prawej
		} else kol[i].wyswietlKolumna(wysokosc, i, false);
	}

	gotoXY(0, 9); //funkcja przenosi kursor do innego miejsca na ekranie, tam sie potem pisze
	SetConsoleTextAttribute(con, 420); //zmiena kolor tekstu
	gracza.wyswietlWierzcholek();
	SetConsoleTextAttribute(con, 15);
	graczaZ.wyswietl();

	cout << endl << "########################################" << endl;
	cout << "              PUNKTY:" << scoreHan.score << endl;
	cout << "########################################" << endl;
	checkWin();
	checkInput();
}

void gameover() {
	system("cls");
	cout << "########################################" << endl;
	cout << "              PASJANS GOLF" << endl;
	cout << "########################################" << endl;
	for (int i = 0; i <= 7; i++) {
		int wysokosc = kol[i].policz();
		if (aktywnaKolumna == i) {
			kol[i].wyswietlKolumna(wysokosc, i, true); //wypisuje obecny stan kart na stole
		} else kol[i].wyswietlKolumna(wysokosc, i, false);
	} 
	gotoXY(0, 9);
	cout << "########################################" << endl;
	cout << "              KONIEC GRY" << endl;
	cout << "########################################" << endl;
	cout << "Uzyskane punkty: " << scoreHan.score << endl;
	if (b)
		if (scoreHan.score != 4400) {  //profesjonalne efekty dzwiekowe
			Beep(400, 400);
			Beep(300, 400);
			Beep(200, 400);
			Beep(150, 1000);
		} else {
			Beep(400, 200);
			Beep(450, 200);
			Beep(500, 300);
			Beep(550, 1090);
		}
	char nazwa[25];
	cout << "Podaj imie: ";
	cin >> nazwa;
	scoreHan.wpiszWynik(nazwa); //zapisuje wynik do pliku
	cout << "Nacisnij, aby wr�ci� do menu...";
	system("pause> nul");
	menu();
}

void menu() {
	char w;
	dispose();
	system("cls");
	cout << "########################################" << endl;
	cout << "              PASJANS GOLF" << endl;
	cout << "########################################" << endl;
	cout << "1. Rozpocznij gr�" << endl;
	cout << "2. Zasady gry i sterowanie" << endl;
	cout << "3. Wl�cz dzwieki";
	if (b) SetConsoleTextAttribute(con, 44); else
		SetConsoleTextAttribute(con, 66);
	cout << "  " << endl;
	SetConsoleTextAttribute(con, 15);
	cout << "4. Highscores" << endl;
	cout << "5. Wyj�cie" << endl;
	cout << "Wybor: ";
	cin >> w;
	switch (w) {
	case '1': create();
		break;
	case '2': {
		system("cls");
		cout << "Prostota zasad gry w pasjansa czasami jest wr�cz pora�aj�ca i g��wnie ta cecha powoduje, �e z przyjemno�ci� po�wi�camy czas, aby roz�o�y� w spokoju karty i zagra�. Pasjans golf ma dwie pule kart: roz�o�on�, odkryt� na stole oraz zakryt� w kupce pod spodem. Pierwsza karta z kupki jest automatycznie odkrywana przy rozpocz�ciu gry i le�y obok kupki. Gracz ma za zadanie dobra� do niej kolejne karty z tych roz�o�onych (o jedno �oczko� mniejsz� lub wi�ksz�, kolor nie ma znaczenia), a je�li sko�cz� si� wszystkie mo�liwo�ci, musi zabra� kolejn� kart� z zakrytej kupki. Gra trwa a� do wyczerpania kart na kupce. Je�li w tym czasie znikn� wszystkie roz�o�one na stole katry � wygra�e�, je�li pozostanie cho�by jedna � c�, trudno, mo�e nast�pnym razem si� uda... ";
		cout << endl << "Sterowanie:";
		cout << endl << "\t\tA - przesu� kursor w lewo";
		cout << endl << "\t\tD - przesu� kursor w prawo";
		cout << endl << "\t\tS - sci�gnij karte ze sto�u (je�li to mo�liwe)";
		cout << endl << "\t\tSpacja - wyl� now� kart�";
		cout << endl << "\t\tQ - wyjd� do menu";
		cout << endl << endl << "ATH Bielsko-Bia�a @ Adam Mitr�ga, Maciej �lusarek";
		cout << endl << "Nacisnij, aby wrocic do menu...";
		system("pause > nul");
		menu();
		break;
	}
	case '3': {
		b = !b;
		if (b) Beep(500, 300);
		menu();
		break;
	}
	case '4': {
		scoreHan.wypiszWyniki();
		cout << "Nacisnij, aby wr�cic do menu...";
		system("pause > nul");
		menu();
		break;
	}
	case '5':
		exit(0);
		break;
	default:
		main();
		break;
	}
}

int main() {
	SetConsoleTextAttribute(con, 15);
	system("chcp 1250 > nul");
	menu();
	return 0;
}