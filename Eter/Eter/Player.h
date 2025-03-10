#pragma once
#include <cstdint>
#include <vector>
#include <optional>
#include <string>
#include <random>
#include <utility>
#include <regex>
#include "Board.h"
#include "Card.h"



namespace eter {
	template <typename T>
	T validateInput(const std::string& prompt, const std::regex& pattern, const std::string& errorMessage) {
		T input;
		std::cout << prompt;
		std::cin >> input;
		while (!std::regex_match(input, pattern)) {
			std::cout << errorMessage;
			std::cin >> input;
		}
		std::cout << "Input processed successfully!\n";
		return input;
	}
	 class Player
	{
	private:
		std::string m_name;
		uint32_t m_score;
		std::string m_color;
		std::vector<Card> m_cardsInHand;
		bool m_hasUsedIllusion;
		std::vector<Card> m_playedCards;
		std::vector<Card> m_eliminatedCards;
		std::vector<std::pair<Card, std::pair<size_t, size_t>>> m_playedCardsP;
	public:

		Player() = default;
		Player(const std::string& name, const std::string& color);
		~Player() = default;
		Player(const Player& other);
		Player& operator=(const Player& rhs);
		Player(Player&& other) noexcept;
		Player& operator=(Player&& rhs) noexcept;

		const std::string& GetName() const;
		uint32_t GetScore() const;
		const std::string& GetColor() const;
		std::vector<Card>& GetCardsInHand();
		bool GetHasUsedIllusion() const;
		std::vector<Card>& GetPlayedCards();
		std::vector<Card>& GetEliminatedCards();

		const std::vector<Card>& GetCardsInHand() const;

		const std::vector<Card>& GetPlayedCards() const;
		const std::vector<Card>& GetEliminatedCards() const;

		void SetName(const std::string& name);
		void SetScore(uint32_t score);
		void SetColor(const std::string& color);
		void SetCardsInHand(const std::vector<Card>& cards);

		void printCardsInHand();
		void addToEliminatedCards(const Card& card);
		void addPlayedCard(const Card& card);
		void addCardToHand(const Card& card);
		void useIllusion(size_t x, size_t y, Board& board, Card& illusion);
		bool placeCard(size_t x, size_t y, const Card& card, Board& board);

		void removePlayedCard(const Card& card);
		void removePlayedCardForPower(const Card& card, size_t row, size_t col);
		void addPlayedCardForPower(const Card& card, size_t x, size_t y);
		std::vector<std::pair<Card, std::pair<size_t, size_t>>>& GetPlayedCardsForPower();//geterul pentru puteri care imi da vectorul cu ultima carte si cu pozitia sa
		static std::string validateName();

		void swap(Player& other) noexcept;
		friend void swap(Player& first, Player& second) noexcept;

	};


}