import gamemanager;
import game;
import board;
import player;
import<vector>;
import <stack>;
import <optional>;
import <iostream>;
int main()
{
	using namespace eter;
	Card card{ 4,"red",true };
	std::cout << card << "\n";
	std::vector<std::vector<std::optional<std::stack<Card>>>> grid(3, std::vector<std::optional<std::stack<Card>>>(3, std::nullopt));
	Board board(grid,3,3);
	std::cout << board;
	auto& stack = board[{0, 0}];  
	if (!stack) {
		stack = std::stack<Card>();
	}
	stack->push(card);
	std::cout << board;


	Player player1("Mihai","red");
	Player player2("Alina", "blue");
    
	GameManager gameManager;
	//gameManager.StartNewGame(player1, player2, board, "AMode");
	
	return 0;
}