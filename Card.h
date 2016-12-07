#include <iostream>
#include <string>

class Card
{
public:
	Card(std::string n, char s, int card_ID); //prototype, sets number and suit when created. set both to 'e' when creating empty card
	std::string GetNumber();
	char GetSuit();
	void SetNumber(std::string x);
	void SetSuit(char x);
	int GetID();
private:
	std::string number;
	char suit;
	int id;
};