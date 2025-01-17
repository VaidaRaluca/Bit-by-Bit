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

	GameManager game;

	const std::string& gameMode = GameManager::chooseGameMode();

	game.startNewGame(player1, player2, gameMode);


	//try {
	//	game.SaveGame();
	//}
	//catch (const std::exception& e) {
	//	std::cerr << "Error saving game: " << e.what() << std::endl;
	//}

	return 0;
}