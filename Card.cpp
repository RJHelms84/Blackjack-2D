#include "Card.h"

Card::Card(std::string n, char s, int card_ID)
{
	number = n;
	suit = s;
	id = card_ID;
}

std::string Card::GetNumber()
{
	return number;
}

char Card::GetSuit()
{
	return suit;
}

void Card::SetNumber(std::string x)
{
	number = x;
}

void Card::SetSuit(char x)
{
	suit = x;
}

int Card::GetID()
{
	return id;
}