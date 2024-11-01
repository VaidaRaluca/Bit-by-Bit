#include<cstdint>
export module player;
import card;
import <vector>;
import <string>;
namespace eter {
	export class Player 
	{
	private:
		std::string m_name;
		uint32_t m_score;
		std::string m_color;
		std::vector<Card> m_cardsInHand;
	public:
		Player() = default;
		Player(const std::string& name, uint32_t score, const std::string& color, const std::vector<Card>& cards);
		~Player() = default;

		//Getteri
		const std::string& GetName() const;
		uint32_t GetScore() const;
		const std::string& GetColor() const;
		const std::vector<Card>& GetCardsInHand() const;

		//Setteri
		void SetName(const std::string& name);
		void SetScore(uint32_t score);
		void SetColor(const std::string& color);
		void SetCardsInHand(const std::vector<Card>& cards);
	};
}