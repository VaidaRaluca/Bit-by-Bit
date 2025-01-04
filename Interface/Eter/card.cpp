#include "card.h"
using namespace eter;

Card::Card(const uint8_t& value, const std::string& color, const bool& position) :
    m_value{ value }, m_color{ color }, m_position{ position }
{
}

Card::Card(const Card& other)
    : m_value{ other.m_value }, m_color{ other.m_color }, m_position{ other.m_position }
{
}

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
    other.m_color="";
    other.m_position = true;
}

Card& Card::operator=(Card&& other) noexcept
{
    if (this == &other) return *this;
    m_value = other.m_value;
    m_color = std::move(other.m_color);
    m_position = other.m_position;

    other.m_value = 0;
    other.m_color="";
    other.m_position = true;
    return *this;
}

const uint8_t & Card::GetValue() const
{
    return m_value;
}

const std::string& Card::GetColor() const
{
    return m_color;
}

const bool& Card::GetPosition() const
{
    return m_position;
}


void Card::SetValue(const uint8_t& value)
{
    m_value = value;
}

void Card::SetColor(const std::string& color)
{
    m_color = color;
}

void Card::SetPosition(const bool& position)
{
    m_position = position;
}


bool eter::Card::operator==(const Card& other) const
{
    return this->m_value == other.m_value && this->m_color == other.m_color && other.m_position==this->m_position;
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
            os << "/";
        else if (card.GetValue() == 5)
            os << backgroundColor << textColor << 'E';
        else
            os << backgroundColor << textColor
               << static_cast<int>(card.GetValue());

    os << resetColor;
    return os;
}

QDebug operator<<(QDebug debug, const Card& card)
{
    // Utilizăm culori pentru afișare doar în text normal
    QString textColor, backgroundColor;

    if (QString::fromStdString(card.GetColor()) == "red") {
        textColor = "Red";
        backgroundColor = "Black";
    } else if (QString::fromStdString(card.GetColor()) == "blue") {
        textColor = "Blue";
        backgroundColor = "Black";
    } else {
        textColor = "Default";
        backgroundColor = "Default";
    }

    QString cardRepresentation;

    if (!card.GetPosition()) {
        cardRepresentation = QString("\"");
    } else if (card.GetValue() == '/') {
        cardRepresentation = "/";
    } else if (card.GetValue() == 5) {
        cardRepresentation = "E";
    } else {
        cardRepresentation = QString::number(card.GetValue());
    }

    debug.nospace() << "Card(Value: " << cardRepresentation
                    << ", Color: " << textColor
                    << ", Position: " << (card.GetPosition() ? "True" : "False") << ")";

    return debug;
}

void eter::swap(Card& first, Card& second) noexcept
{
    first.swap(second);
}
