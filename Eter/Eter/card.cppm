#include<cstdint>;
export module card;
import <variant>;
import <vector>;
import <string>;
import <format>;
import <iostream>;
namespace eter {
	export class Card {
	private:
		uint8_t m_value;
		std::string m_color; 
		bool m_position; //true = fata in sus
	public:
		//Rule of 5
		Card() = default;
		Card(uint8_t value , const std::string& color, bool position);
		Card(const Card& other);
		Card& operator=(const Card& other);
		Card(Card&& other) noexcept;
		Card& operator=(Card&& other) noexcept;
		~Card() = default;

		uint8_t GetValue() const;  
		const std::string& GetColor() const;
		bool GetPosition() const;

		void SetValue(uint8_t value);
		void SetColor(const std::string& color); //for later color could be an enum : red/blue => reduces memory overhead and increases efficiency
		void SetPosition(bool positon);

		bool operator==(const Card& other) const;
		void swap(Card& other) noexcept;
	};
	export std::ostream& operator<<(std::ostream& os, const Card& card);
	export void swap(Card& first, Card& second) noexcept;
};