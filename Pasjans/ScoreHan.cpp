#include "ScoreHan.h"
#include <fstream>
#include <iostream>	

std::ofstream file;
std::ifstream out;
ScoreHan::ScoreHan() {


}

ScoreHan::~ScoreHan()
{
}

void ScoreHan::wpiszWynik(char *n) {
	file.open(".scores.txt", std::ios_base::app);
	file << std::endl << n << "#" << score;
	file.close();
}
void ScoreHan::wypiszWyniki() {
	out.open(".scores.txt");
	char a[35];
	int k = 0;
	if (out.is_open())
	{
		while (!out.eof())
		{

			out >> a;
			for (int i = 0; i < 35; i++)
			{
				if (a[i] == '#') {
					a[i] = '-';
					k++;
				}

			}
			if (k > 0) std::cout << k << ". " << a << std::endl;

		}
	}

	out.close();

}