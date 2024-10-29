export module game;
import <vector>;
import cards;
namespace eter 
{
	export class Game: public eter::Cards
	{
	private:
		std::vector<std::vector<eter::Cards>> board;

	};

}

