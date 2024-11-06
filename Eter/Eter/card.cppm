#include<cstdint>;
#include <iostream>;
export module card;
import <variant>;
import <vector>;
import <string>;
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
		void SetColor(std::string color);
		void SetPosition(bool positon);

		~Card() = default;
	};
	export std::ostream& operator<<(std::ostream& os, const Card& card);


};