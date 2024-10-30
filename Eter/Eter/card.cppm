#include<cstdint>;
export module card;
import <variant>;
import <vector>;
namespace eter {
export class Card {
public:
        enum class DigitCard :uint8_t {
            value 
        };

        enum class PowerCard {
           
        };
        std::vector<Card> m_deckCards;
        bool m_position; //true = fata in sus
        Card()=default;
        Card(std::vector<Card> deckCards, bool position);
        ~Card() = default;

};

};