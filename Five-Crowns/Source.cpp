#include<iostream>
#include "Deck.h"

using namespace std;

int main() {

	cout << "Inside main() method in Source.cpp" << endl;

	Deck drawPile;

	drawPile.printDrawPile();

	system("pause");
	return 0;
}