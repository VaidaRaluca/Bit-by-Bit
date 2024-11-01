#include<cstdint>;
export module card;
import cardtype;
import <variant>;
import <vector>;
import <string>;
namespace eter {
	export class Card {
	public:
		CardType m_card;
		std::string m_color;
		bool m_position; //true = fata in sus

		Card() = default;
		Card(CardType, const std::string& color, bool position);
		~Card() = default;

	};

};