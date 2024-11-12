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

const std::string& eter::Card::GetOwnerName() const
{
	return m_ownerName;
}


void Card::SetValue(uint8_t value)
{
	m_value = value;
}

void Card::SetColor(const std::string& color)
{
	m_color = color;
}

void Card::SetPosition(bool position)
{
	m_position = position;
}

void Card::SetOwnerName(const std::string& ownerName)
{
	m_ownerName = ownerName;
}

bool eter::Card::operator==(const Card& other) const
{
	return m_value == other.m_value && m_color == other.m_color && m_position == other.m_position;
}


std::ostream& eter::operator<<(std::ostream& os, const Card& card)
{
	os << std::format("Value: {}, Color: {}, Face-Up: {}", static_cast<int>(card.GetValue()), card.GetColor(), card.GetPosition());
	return os;
}