#include "Deck.h"

vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;



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

	
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);

	shuffle(drawPile.begin(), drawPile.end(), e);
}


vector<Card> Deck::dealCards(int roundNumber) {
	cout << "Dealing cards for roundNumber: " << roundNumber << endl;
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
	//vector<Card> ::iterator it;
	for (auto it = drawPile.rbegin(); it != drawPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
}

void Deck::printDiscardPile() {
	cout << "Total number in Discard Pile is: " << discardPile.size() << endl;
	cout << " ----------------------------- " << endl;
	cout << "The discard Pile is: " << endl;
	//vector<Card> ::iterator it;
	for (auto it = discardPile.rbegin(); it != discardPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
}

void Deck::showTopDiscardCard() {
	cout << "Top discard card is: ";
	Card topDiscardCard = discardPile.back();
	topDiscardCard.printCard();
}

Card Deck::takeTopDiscardCard() {
	Card topDiscardCard = discardPile.back();
	discardPile.pop_back();
	return topDiscardCard;
}

void Deck::showTopDrawCard() {
	Card topDrawCard = drawPile.back();
	cout << "Top draw card is: ";
	topDrawCard.printCard();
}

Card Deck::takeTopDrawCard() {
	Card topDrawCard = drawPile.back();
	drawPile.pop_back();
	return topDrawCard;
}


Deck::~Deck()
{
}
