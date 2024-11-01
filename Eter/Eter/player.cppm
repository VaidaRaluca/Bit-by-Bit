#include<cstdint>
export module player;
import <string>;
namespace eter {
	export class Player 
	{
	private:
		std::string m_name;
		uint32_t m_score;
		uint16_t m_nrCardsLeft;
		std::string m_color;
	public:
		Player();
		Player(const std::string &name, uint32_t score, uint16_t nrCardsLeft, const std::string& color);
		~Player() = default;
	};
}