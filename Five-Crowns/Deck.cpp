#include "Deck.h"

//Initializing static members.

vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine e(seed);

//Constructor for Deck. Calls resetDeck() function.

Deck::Deck()
{
	resetDeck();
}

/* *********************************************************************
Function Name: resetDeck
Purpose: To clear draw and discard piles and add all cards to the draw pile in random order.
Local Variables:
	suits, an array of string containing all the available suit values used during loop
	faces, an array of string containing all available faces during loop
	joker_face, a string containing "J" used for creating joker cards 
	joker_suits, an array of string containing the values for second character in joker cards, used during loops.
Algorithm:
	1) Loop two times, for every element in suits, for every element in faces, create a card and push to draw_pile
	2) Add 6 jokers to the draw pile.
	3) Shuffle the draw pile
Assistance Received: Looked at stack overflow for the how to randomize elements of a vector.
********************************************************************* */

void Deck::resetDeck() {

	drawPile.clear();
	discardPile.clear();
	
	string suits[] = { "S", "C", "D", "H", "T" };
	string faces[] = { "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };
	string joker_face = "J";
	string joker_suits[] = { "1", "2", "3" };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < (sizeof(suits) / sizeof(suits[0])); j++) {
			for (int k = 0; k < (sizeof(faces) / sizeof(faces[0])); k++) {
				Card currentCard(faces[k], suits[j]);
				drawPile.push_back(currentCard);
			}
		}
		
		for (int i = 0; i < (sizeof(joker_suits) / sizeof(joker_suits[0])); i++) {
			Card currentCard(joker_face, joker_suits[i]);
			drawPile.push_back(currentCard);
		}
	}

	shuffle(drawPile.begin(), drawPile.end(), e);
}

/* *********************************************************************
Function Name: printDrawPile
Purpose: To print the current draw pile.
Assistance Received: none
********************************************************************* */

void Deck::printDrawPile() {
	cout << "The draw Pile is: ";
	for (auto it = drawPile.rbegin(); it != drawPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
	cout << endl;
}

/* *********************************************************************
Function Name: printDiscardPile
Purpose: To print the current discard pile.
Assistance Received: none
********************************************************************* */

void Deck::printDiscardPile() {
	cout << "The discard Pile is: ";
	for (auto it = discardPile.rbegin(); it != discardPile.rend(); ++it) {
		it->printCard();
	}
	cout << endl;
	cout << endl;
}


/* *********************************************************************
Function Name: dealCards
Purpose: To clear draw and discard piles and add all cards to the draw pile in random order.
Parameters:
	roundNumber, an integer containing the current round number.
Return Value: A vector of cards containing the cards to deal to the two players.
Local Variables:
	cardstodeal, a vector of Cards that contains the cards to distribute alternately to players for their hands.
Assistance Received: none
********************************************************************* */

vector<Card> Deck::dealCards(int roundNumber) {
	resetDeck();
	//vector of cards that is returned and contains the cards to deal to the players.
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


/* *********************************************************************
Function Name: showTopDiscardCard
Purpose: To print the card at the top of Discard pile.
Local Variables:
	topDiscardCard, Card contains the Card at the top of Discard pile
Assistance Received: none
********************************************************************* */

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

/* *********************************************************************
Function Name: takeTopDiscardCard
Purpose: To remove card from top of discard pile and return it
Return Value: The card at the top of the Disccard Pile
Local Variables:
	topDiscardCard, Card contains the Card at the top of Discard pile
Assistance Received: none
********************************************************************* */

Card Deck::takeTopDiscardCard() {
	Card topDiscardCard;
	if (!discardPile.empty()) {
		topDiscardCard = discardPile.back();
		discardPile.pop_back();
	}
	return topDiscardCard;
}

/* *********************************************************************
Function Name: showTopDrawCard
Purpose: Prints card at top of Draw Pile to the console
Local Variables:
	topDrawCard, a card that contains card at the top of Draw Pile
Assistance Received: none
********************************************************************* */

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

/* *********************************************************************
Function Name: takeTopDrawCard
Purpose: To remove card from top of draw pile and return it
Return Value: The card at the top of the Draw Pile
Local Variables:
	topDrawCard, Card contains the Card at the top of Draw pile
Assistance Received: none
********************************************************************* */

Card Deck::takeTopDrawCard() {
	Card topDrawCard;
	if (!drawPile.empty()) {
		topDrawCard = drawPile.back();
		drawPile.pop_back();
	}
	return topDrawCard;
}

/* *********************************************************************
Function Name: getCurrentDrawPile
Purpose: To get a space separated string representation of cards in the Draw Pile
Return Value: a string of space seprated representation of cards in the Draw Pile
Local Variables:
	current_draw_pile, a string containing space separated representation of cards in the Draw Pile
Assistance Received: none
********************************************************************* */

const string Deck::getCurrentDrawPile() {
	string current_draw_pile;
	for (auto it = drawPile.rbegin(); it != drawPile.rend(); ++it) {
		string card_str = it->cardToString();
		current_draw_pile = current_draw_pile + card_str + " ";
	}
	return current_draw_pile;
}

/* *********************************************************************
Function Name: getCurrentDiscardPile
Purpose: To get a space separated string representation of cards in the Discard Pile
Return Value: a string of space seprated representation of cards in the Discard Pile
Local Variables:
	current_discard_pile, a string containing space separated representation of cards in the Discard Pile
Assistance Received: none
********************************************************************* */

const string Deck::getCurrentDiscardPile() {
	string current_discard_pile;
	for (auto it = discardPile.rbegin(); it != discardPile.rend(); ++it) {
		string card_str = it->cardToString();
		current_discard_pile = current_discard_pile + card_str + " ";
	}
	return current_discard_pile;
}

/* *********************************************************************
Function Name: accessTopDiscardPileCard
Purpose: Get the card at the top of Discard Pile
Local Variables:
topDiscardCard, card at top of Discard Pile
Return Value: The card at top of Discard Pile
Assistance Received: none
********************************************************************* */

Card Deck::accessTopDiscardPileCard() {
	Card topDiscardCard;
	if (!discardPile.empty()) {
		topDiscardCard = discardPile.back();
	}
	return topDiscardCard;
}

/* *********************************************************************
Function Name: accessTopDrawPileCard
Purpose: Get the card at the top of Draw Pile
Local Variables:
topDrawCard, card at top of Discard Pile
Return Value: The card at top of Draw Pile
Assistance Received: none
********************************************************************* */

Card Deck::accessTopDrawPileCard() {
	Card topDrawCard;
	if (!drawPile.empty()) {
		topDrawCard = drawPile.back();
	}
	return topDrawCard;
}

/* *********************************************************************
Function Name: setDrawPile
Purpose: Set the current Draw Pile
Parameters:
	draw_Pile, a vector of strings containing the string representation of cards to set in the Draw Pile
Local Variables:
	face, a character that extracts the face of the card
	suit, a character that extracts the suit of the card
	s_face, conversion of face char to string
	s_suit, conversion of suit char to string
	current_card, conversion of string to card
	it, a vector string iterator.
Assistance Received: none
********************************************************************* */


void Deck::setDrawPile(vector<string> draw_Pile) {
	drawPile.clear();
	vector<string>::iterator it;
	char face, suit;
	for (it = draw_Pile.begin(); it != draw_Pile.end(); ++it) {
		face = (*it)[0];
		suit = (*it)[1];
		string s_face(1, face);
		string s_suit(1, suit);
		Card current_card = Card(s_face, s_suit);
		drawPile.push_back(current_card);
	}
}

/* *********************************************************************
Function Name: setDiscardPile
Purpose: Set the current Discard Pile
Parameters:
	discard_Pile, a vector of strings containing the string representation of cards to set in the Draw Pile
Local Variables:
	face, a character that extracts the face of the card
	suit, a character that extracts the suit of the card
	s_face, conversion of face char to string
	s_suit, conversion of suit char to string
	current_card, conversion of string to card
	it, a vector string iterator.
Assistance Received: none
********************************************************************* */

void Deck::setDiscardPile(vector<string> discard_Pile) {
	discardPile.clear();
	vector<string>::iterator it;
	char face, suit;
	for (it = discard_Pile.begin(); it != discard_Pile.end(); ++it) {
		face = (*it)[0];
		suit = (*it)[1];
		string s_face(1, face);
		string s_suit(1, suit);
		Card current_card = Card(s_face, s_suit);
		discardPile.push_back(current_card);
	}
}



/* *********************************************************************
Function Name: pushToDiscardPile
Purpose: Add a card to the end of Discard Pile
Parameters:
	card, the card to push to the end of Discard Pile
Assistance Received: none
********************************************************************* */

void Deck::pushToDiscardPile(Card card) {
	discardPile.push_back(card);
}

//Default Destructor

Deck::~Deck()
{
}
