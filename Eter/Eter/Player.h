#pragma once
#include<cstdint>
#include <vector>
#include <optional>
#include <string>
#include <random>
#include <utility>
#include "Board.h"
#include "Card.h"

namespace eter {
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
		std::vector<std::pair<Card, std::pair<size_t, size_t>>> m_playedCardsP;//pentru puteri ca aveam nevoie sa stiu si pozitia
		//la care a pus ultima carte
	public:
		//Rule of 5
		Player() = default;
		Player(const std::string& name, const std::string& color);
		~Player() = default;
		Player(const Player& other);
		Player& operator=(const Player& rhs);
		Player(Player&& other) noexcept;
		Player& operator=(Player&& rhs) noexcept;

		//Getteri
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

		//Setteri
		void SetName(const std::string& name);
		void SetScore(uint32_t score);
		void SetColor(const std::string& color);
		void SetCardsInHand(const std::vector<Card>& cards);

		void PrintCardsInHand();
		void AddToEliminatedCards(const Card& card);//Adauga o carte in m_eliminatedCards
		void AddPlayedCard(const Card& card);
		void AddCardToHand(const Card& card);//Adauga o carte in m_cardsInHand
		void useIllusion(size_t x, size_t y, Board& board, Card& illusion);
		std::pair<uint8_t, uint8_t> findEmptyCell(Board& board);
		bool placeCard(size_t x, size_t y, const Card& card, Board& board);

		void RemovePlayedCard(const Card& card);
		void RemovePlayedCardForPower(const Card& card, size_t row, size_t col);
		void addPlayedCardForPower(const Card& card, size_t x, size_t y);
		std::vector<std::pair<Card, std::pair<size_t, size_t>>>& GetPlayedCardsForPower();//geterul pentru puteri care imi da vectorul cu ultima carte si cu pozitia sa


		void swap(Player& other) noexcept;
		friend void swap(Player& first, Player& second) noexcept;

	};


}