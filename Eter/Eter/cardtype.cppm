#include <cstdint>
export module cardtype;
import <string>;
namespace eter {
	export enum class CardType: uint8_t {
		DigitCard,
		PowerCard
	};
	CardType ParseCardType(const std::string& string);
}

