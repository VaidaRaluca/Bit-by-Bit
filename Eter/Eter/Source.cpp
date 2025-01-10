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

	Player player1("Mihai","red");
	Player player2("Alina", "blue");

	// Test AMode
	GameManager game;
    //game.StartNewGame(player1, player2, "AMode");


	// Test BMode

	//game.StartNewGame(player1, player2, "BMode");

	//Test CMode

	game.StartNewGame(player1, player2, "CMode");

    // game.StartNewGame(player1, player2, "BCMode");

	//try {
	//	game.SaveGame();
	//}
	//catch (const std::exception& e) {
	//	std::cerr << "Error saving game: " << e.what() << std::endl;
	//}

	return 0;
}