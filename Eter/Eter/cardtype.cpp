module cardtype;
using namespace eter;
using namespace std::literals;
CardType ParseCardType(const std::string& string)
{
	if (string == "DigitCard")
		return CardType::DigitCard; //tbc
	else if (string == "PowerCard")
		return CardType::PowerCard; //tbc
	else
		throw std::exception{ "Unknown Type" };
}
