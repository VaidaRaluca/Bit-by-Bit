#include<cstdint>;
export module card;
import <variant>;
import <vector>;
import <string>;
import <format>;
import <iostream>;
namespace eter {
	export class Card {
	public:
		uint8_t m_value;
		std::string m_color; 
		bool m_position; //true = fata in sus
		Card() = default;
		Card(uint8_t value , const std::string& color, bool position);

		uint8_t GetValue() const;  
		const std::string& GetColor() const;
		bool GetPosition() const;

		void SetValue(uint8_t value);
		void SetColor(const std::string& color); //for later color could be an enum : red/blue => reduces memory overhead and increases efficiency
		void SetPosition(bool positon);

		bool operator==(const Card& other) const;
		~Card() = default;
	};
	export std::ostream& operator<<(std::ostream& os, const Card& card);

};