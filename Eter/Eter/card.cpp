module card;
import <string>;
using eter::Card;
import <format>;
import <iostream>;
Card::Card(uint8_t value, const std::string& color, bool position) :
	m_value{value},m_color{color},m_position{position}
{}

uint8_t Card::GetValue() const
{
	return m_value;
}

const std::string& Card::GetColor() const
{
	return m_color;
}

bool Card::GetPosition() const
{
	return m_position;
}


void Card::SetValue(uint8_t value)
{
	m_value = value;
}

void Card::SetColor(std::string color)
{
	m_color = color;
}

void Card::SetPosition(bool position)
{
	m_position = position;
}


std::ostream& eter::operator<<(std::ostream& os, const Card& card)
{
	os << static_cast<int>(card.GetValue())<<" "<<card.GetColor()<<" " << static_cast<int>(card.GetPosition());
	return os;
}