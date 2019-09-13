#include "Deck.h"



Deck::Deck()
{
	//S - spades, C - clubs, D - diamonds, H - hearts, T - tridents
	string suits[] = { "S", "C", "D", "H", "T" };

	string faces[] = { "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K"};

	string joker_face = "J";

	string joker_suits[] = { "1", "2", "3" };

	for (int i = 0; i < 2; i++) {
		//two piles in first draw pile
		
		//loop for every suit through all the faces then add jokers
		for (int j = 0; j < (sizeof(suits)/sizeof(suits[0])); j++) {
			for (int k = 0; k < (sizeof(faces) / sizeof(faces[0])); k++) {
				Card currentCard(faces[k], suits[j]);
				drawPile.push_back(currentCard);
			}
		}
		//Add jokers to the pile
		for (int i = 0; i < (sizeof(joker_suits) / sizeof(joker_suits[0])); i++) {
			Card currentCard(joker_face, joker_suits[i]);
			drawPile.push_back(currentCard);
		}
	}

	//auto range = default_random_engine{};
	//shuffle(begin(drawPile), end(drawPile), range);
}


vector<Card> Deck::dealCards(int roundNumber) {
	vector<Card> cardstodeal;
	int total_cards_per_player = (2 + roundNumber)*2;
	for (int i = 0; i < total_cards_per_player; i++) {
		cardstodeal.push_back(drawPile.back());
		drawPile.pop_back();
	}
	discardPile.push_back(drawPile.back());
	drawPile.pop_back();
	return cardstodeal;
}


void Deck::printDrawPile() {
	cout << "Total number in Draw Pile is: " << drawPile.size() << endl;
	cout << " ----------------------------- " << endl;
	cout << "The draw Pile is: " << endl;
	vector<Card> ::iterator it;
	for (it = drawPile.begin(); it != drawPile.end(); ++it) {
		it->printCard();
	}
}

void Deck::printDiscardPile() {
	cout << "Total number in Discard Pile is: " << discardPile.size() << endl;
	cout << " ----------------------------- " << endl;
	cout << "The discard Pile is: " << endl;
	vector<Card> ::iterator it;
	for (it = discardPile.begin(); it != discardPile.end(); ++it) {
		it->printCard();
	}
}

Deck::~Deck()
{
}
