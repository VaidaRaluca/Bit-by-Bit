module card;
import <string>;
using eter::Card;
import <format>;
import <iostream>;
Card::Card(uint8_t value, const std::string& color, bool position) :
	m_value{ value }, m_color{ color }, m_position{ position }
{}

Card::Card(const Card& other)
	: m_value{ other.m_value }, m_color{ other.m_color }, m_position{ other.m_position }
{}

Card& Card::operator=(const Card& other)
{
	if (this == &other) return *this;
	m_value = other.m_value;
	m_color = other.m_color;
	m_position = other.m_position;
	return *this;
}

Card::Card(Card&& other) noexcept
	: m_value{ other.m_value }, m_color{ std::move(other.m_color) }, m_position{ other.m_position }
{
	other.m_value = 0;
	other.m_position = true;
}

Card& Card::operator=(Card&& other) noexcept
{
	if (this == &other) return *this;
	m_value = other.m_value;
	m_color = std::move(other.m_color);
	m_position = other.m_position;

	other.m_value = 0;
	other.m_position = true;
	return *this;
}

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

void Card::SetColor(const std::string& color)
{
	m_color = color;
}

void Card::SetPosition(bool position)
{
	m_position = position;
}


bool eter::Card::operator==(const Card& other) const
{
	return m_value == other.m_value && m_color == other.m_color && m_position == other.m_position;
}

void eter::Card::swap(Card& other) noexcept
{
	using std::swap;
	swap(m_value, other.m_value);
	swap(m_color, other.m_color);
	swap(m_position, other.m_position);
}


std::ostream& eter::operator<<(std::ostream& os, const Card& card)
{
	// Map colors to text color (foreground) and background color codes
	std::string textColor, backgroundColor;

	if (card.GetColor() == "red") {
		textColor = "\033[38;5;9m";  // Red text
		backgroundColor = "\033[48;5;0m";  // Black background
	}
	else if (card.GetColor() == "blue") {
		textColor = "\033[38;5;12m";  // Blue text
		backgroundColor = "\033[48;5;0m";  // Black background
	}
	std::string resetColor = "\033[0m";
	if (!card.GetPosition()) os << backgroundColor << textColor << '\"';
	else 
		if (card.GetValue() == '/')
		std::cout << "/";
	else
		os << backgroundColor << textColor
		<< static_cast<int>(card.GetValue());


	os << resetColor;
	return os;
}

void eter::swap(Card& first, Card& second) noexcept
{
	first.swap(second);
}