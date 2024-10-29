#include<cstdint>;
export module cards;
import <variant>;
import <vector>;
namespace eter {
export class Cards {
    private:
        enum class DigitCard :uint8_t {
            value 
        };

        enum class PowerCard {
            //TO ADD POWERS
        };

        using Card = std::variant<DigitCard, PowerCard>;
        std::vector<Card> m_deckCards;
        bool m_position; //true = fata in sus
public:
    Cards()=default;
    Cards(std::vector<Card> deckCards, bool position);
    ~Cards() = default;

};

};