#include<cstdint>
export module player;
import card;
import board;
import <vector>;
import <optional>;
import <string>;
import <random>;
import <utility>;
namespace eter {
	export class Player
	{
	private:
		std::string m_name;
		uint32_t m_score;
		std::string m_color;
		std::vector<Card> m_cardsInHand;
		bool m_hasUsedIllusion;
		std::vector<Card> m_playedCards;
		std::vector<Card> m_eliminatedCards;
	public:
		Player() = default;
		Player(const std::string& name, const std::string& color);
		~Player() = default;

		//Getteri
		const std::string& GetName() const;
		uint32_t GetScore() const;
		const std::string& GetColor() const;
		std::vector<Card>& GetCardsInHand();
		bool GetHasUsedIllusion() const;
		std::vector<Card>& GetPlayedCards();
		std::vector<Card>& GetEliminatedCards();

		//Setteri
		void SetName(const std::string& name);
		void SetScore(uint32_t score);
		void SetColor(const std::string& color);
		void SetCardsInHand(const std::vector<Card>& cards);

		void PrintCardsInHand();
		void AddToEliminatedCards(const Card& card);//Adauga o carte in m_eliminatedCards
		void AddPlayedCard(const Card& card);
		void AddCardToHand(const Card& card);//Adauga o carte in m_cardsInHand
		void useIllusion(int x, int y, Board& board, Card& illusion);
		std::pair<uint8_t, uint8_t> findEmptyCell(Board& board);
		bool placeCard(int x, int y, const Card& card, Board& board);
	};
}