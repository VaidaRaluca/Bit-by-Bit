#include "GameManager.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include<vector>
#include <stack>
#include <optional>
#include <iostream>
int main()
{
	using namespace eter;
	std::string name1, name2;
	name1 = Player::validateName();
	name2 = Player::validateName();
	Player player1{ name1, "red" };
	Player player2{ name2, "blue" };

	// Test AMode
	GameManager game;
	//game.StartNewGame(player1, player2, "AMode");
	// Test BMode

	//game.StartNewGame(player1, player2, "BMode");

	//Test CMode
	const std::string& gameMode = GameManager::chooseGameMode();

	game.StartNewGame(player1, player2, gameMode);

	// game.StartNewGame(player1, player2, "BCMode");

	//try {
	//	game.SaveGame();
	//}
	//catch (const std::exception& e) {
	//	std::cerr << "Error saving game: " << e.what() << std::endl;
	//}

	return 0;
}