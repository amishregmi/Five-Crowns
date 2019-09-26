#include "Deck.h"

vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine e(seed);


Deck::Deck()
{
	cout << "Inside deck constructor " << endl;
	drawPile.clear();
	discardPile.clear();
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

	shuffle(drawPile.begin(), drawPile.end(), e);
}


vector<Card> Deck::dealCards(int roundNumber) {
	//cout << "Dealing cards for roundNumber: " << roundNumber << endl;
	vector<Card> cardstodeal;
	int total_cards_per_player = (2 + roundNumber)*2;
	for (int i = 0; i < total_cards_per_player; i++) {
		if (!drawPile.empty()) {
			cardstodeal.push_back(drawPile.back());
			drawPile.pop_back();
		}
	}

	if (!drawPile.empty()) {
		discardPile.push_back(drawPile.back());
		drawPile.pop_back();
	}

	return cardstodeal;
}


void Deck::printDrawPile() {
	//cout << "Total number in Draw Pile is: " << drawPile.size() << endl;
	cout << "The draw Pile is: ";
	//vector<Card> ::iterator it;
	for (auto it = drawPile.rbegin(); it != drawPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
	cout << endl;
}

void Deck::printDiscardPile() {
	cout << "The discard Pile is: ";
	//vector<Card> ::iterator it;
	for (auto it = discardPile.rbegin(); it != discardPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
	cout << endl;
}

void Deck::showTopDiscardCard() {
	if (!discardPile.empty()) {
		cout << "Top discard card is: ";
		Card topDiscardCard = discardPile.back();
		topDiscardCard.printCard();
	}
	else {
		cout << "Discard pile empty" << endl;
	}
}

Card Deck::takeTopDiscardCard() {
	Card topDiscardCard;
	if (!discardPile.empty()) {
		topDiscardCard = discardPile.back();
		discardPile.pop_back();
	}
	return topDiscardCard;
}

void Deck::showTopDrawCard() {
	if (!drawPile.empty()) {
		Card topDrawCard = drawPile.back();
		cout << "Top draw card is: ";
		topDrawCard.printCard();
	}
	else {
		cout << "Draw Pile empty" << endl;
	}
}

Card Deck::takeTopDrawCard() {
	Card topDrawCard;
	if (!drawPile.empty()) {
		topDrawCard = drawPile.back();
		drawPile.pop_back();
	}
	return topDrawCard;
}

string Deck::getCurrentDrawPile() {
	
	string current_draw_pile;
	for (auto it = drawPile.rbegin(); it != drawPile.rend(); ++it) {
		string card_str = it->cardToString();
		current_draw_pile = current_draw_pile + card_str + " ";
	}
	return current_draw_pile;
}

string Deck::getCurrentDiscardPile() {
	string current_discard_pile;
	for (auto it = discardPile.rbegin(); it != discardPile.rend(); ++it) {
		string card_str = it->cardToString();
		current_discard_pile = current_discard_pile + card_str + " ";
	}
	return current_discard_pile;
}

void Deck::setDrawPile(vector<string> draw_Pile) {
	int size = drawPile.size();
	drawPile.erase(drawPile.begin(), drawPile.begin() + size);

	vector<string>::iterator it;
	char face, suit;
	//string s_face, s_suit;
	for (it = draw_Pile.begin(); it != draw_Pile.end(); ++it) {
		face = (*it)[0];
		suit = (*it)[1];
		string s_face(1, face);
		string s_suit(1, suit);
		Card current_card = Card(s_face, s_suit);
		drawPile.push_back(current_card);
	}
}

void Deck::setDiscardPile(vector<string> discard_Pile) {
	cout << "Inside setDiscardPile" << endl;
	cout << "Size is: " << discard_Pile.size() << endl;
	int size = discardPile.size();
	discardPile.erase(discardPile.begin(), discardPile.begin() + size);

	vector<string>::iterator it;
	char face, suit;
	//string s_face, s_suit;
	for (it = discard_Pile.begin(); it != discard_Pile.end(); ++it) {
		face = (*it)[0];
		suit = (*it)[1];
		string s_face(1, face);
		string s_suit(1, suit);
		Card current_card = Card(s_face, s_suit);
		discardPile.push_back(current_card);
	}
	printDiscardPile();
}

Deck::~Deck()
{
}
