module card;
import cardtype;
import <string>;
using namespace eter;

Card::Card(CardType type, const std::string& color, bool position, bool isEter) :
	m_type{type},m_color{color},m_position{position},m_isEter(isEter)
{
}

CardType Card::GetType()
{
	return m_type;
}

std::string Card::GetColor()
{
	return m_color;
}

bool Card::GetPosition()
{
	return m_position;
}

bool Card::GetIsEter()
{
	return m_isEter;
}

void Card::SetType(CardType type)
{
	m_type = type;
}

void Card::SetColor(std::string color)
{
	m_color = color;
}

void Card::SetPosition(bool positon)
{
	m_position = positon;
}

void Card::SetIsEter(bool isEter)
{
	m_isEter = isEter;
}

