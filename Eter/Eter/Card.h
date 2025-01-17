#pragma once
#include <cstdint>
#include <variant>
#include <vector>
#include <string>
#include <format>
#include <iostream>


namespace eter {
	 class Card {
	private:
		uint8_t m_value;
		std::string m_color;
		bool m_position;
 	public:
		//Rule of 5
		Card() = default;
		Card(uint8_t value, const std::string& color, bool position);
		Card(const Card& other);
		Card& operator=(const Card& other);
		Card(Card&& other) noexcept;
		Card& operator=(Card&& other) noexcept;
		~Card() = default;

		uint8_t GetValue() const;
		const std::string& GetColor() const;
		bool GetPosition() const;

		void SetValue(uint8_t value);
		void SetColor(const std::string& color); 
		void SetPosition(bool positon);

		 

		bool operator==(const Card& other) const;
		void swap(Card& other) noexcept;
		friend std::ostream& operator<<(std::ostream& os, const Card& card);
		friend void swap(Card& first, Card& second) noexcept;
	};

};