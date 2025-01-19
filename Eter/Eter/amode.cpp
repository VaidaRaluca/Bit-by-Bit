#include "AMode.h"
using namespace eter;
#include <fstream>
#include <filesystem>

uint8_t eter::AMode::GetRoundsForWin() const
{
	return 2;
}

uint8_t eter::AMode::GetRounds() const
{
	return 3;
}

AMode::AMode(Game* game) : m_game{ game } {}

void AMode::assignCardsInHand()
{

	std::vector<Card>cardsForPlayer1A{
	Card{1,"red",true},
	Card{1,"red",true},
	Card{2,"red",true},
	Card{2,"red",true},
	Card{3,"red",true},
	Card{3,"red",true},
	Card{4,"red",true},
	};
	std::vector<Card>cardsForPlayer2A{
	Card{1,"blue",true},
	Card{1,"blue",true},
	Card{2,"blue",true},
	Card{2,"blue",true},
	Card{3,"blue",true},
	Card{3,"blue",true},
	Card{4,"blue",true},
	};

	if (m_game)
	{
		m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1A);
		m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2A);
	}
}

void AMode::startMatch()
{
	size_t countRound = 1;
	std::cout << "The game has started \n";
	while (m_game->GetPlayer2Wins() < GetRoundsForWin() && m_game->GetPlayer1Wins() < GetRoundsForWin())
	{
		std::cout << "Round " << countRound << " of " << static_cast<int>(GetRounds());
		startRound();
		countRound++;
		std::cout << "The round has ended. \n";
		std::cout << m_game->GetPlayer1().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer1Wins()) << "\n";
		std::cout << m_game->GetPlayer2().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer2Wins()) << "\n";

		assignCardsInHand();
		m_game->resetBoard();
		m_game->SetIsUsedExplosion(false);
	}

	if (m_game->GetPlayer1Wins() > m_game->GetPlayer2Wins())
		std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this game!" << std::endl;
	else
		std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this game!" << std::endl;

	std::cout << "GAME OVER \n";
}


void AMode::handleOption()
{
	enum  Option
	{
		OPTION_1 = 1,
		OPTION_2,
		OPTION_3
	};

	std::cout << m_game->GetBoard();


	if (m_game->GetIsPlayerTurn())
		std::cout << "It's " << m_game->GetPlayer1().GetName() << "'s turn\n";
	else
		std::cout << "It's " << m_game->GetPlayer2().GetName() << "'s turn\n";

	int key;
	std::cout << "Choose an option: \n";
	std::cout << "Press 1 to place a card on the board \n";
	std::cout << "Press 2 to activate an illusion \n";
	std::cout << "Press 3 to save the game \n";
	std::cin >> key;
	Option option = static_cast<Option>(key);

	switch (option) {
	case OPTION_1:
		m_game->playTurn();
		break;
	case OPTION_2:
		m_game->playIllusion();
		break;
	case OPTION_3: {
		std::string filename;
		std::cout << "Enter the file name to save the game: ";
		std::cin >> filename;
		saveGame(filename);
		break;
	}
	default:
		std::cout << "Invalid option.\n";
		break;
	}
}

void AMode::startRound()
{
	char gameStatus = '0';
	while (gameStatus == '0')
	{
		handleOption();
		gameStatus = m_game->verifyGameOver();
		std::cout << "Game status: " << gameStatus << "\n";
	}
	std::cout << gameStatus << "\n";
	if (gameStatus == '2' || gameStatus == '3')
	{
		std::string choice;
		std::cout << "Do you want to continue the game with a single move? (YES or NO) \n";
		std::cin >> choice;
		if (choice == "YES")
			handleOption();

		if (m_game->GetPlayer1().GetColor() == m_game->GetBoard().findWinnerByScore())
		{
			std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this round!" << std::endl;
			m_game->incrementPlayer1Wins();
		}
		else
			if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().findWinnerByScore())
			{
				std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this round!" << std::endl;
				m_game->incrementPlayer2Wins();
			}
			else
				std::cout << "DRAW \n";
	}
	std::cout << m_game->GetBoard();
}

void AMode::applyModeRules()
{
	assignCardsInHand();
	startMatch();
}

void AMode::saveGame(const std::string& filename) const {
	std::filesystem::path filePath(filename);

	if (std::filesystem::exists(filePath)) {
		std::cout << "File already exists: " << filename << "\n";
	}

	std::ofstream outFile(filename, std::ios::out | std::ios::trunc);

	if (!outFile.is_open()) {
		std::cerr << "Failed to open file " << filename << " for saving the game.\n";
		return;
	}

	outFile << "# Game Information\n";
	outFile << "Mode: AMode\n";
	outFile << "Rounds for Win: " << static_cast<int>(GetRoundsForWin()) << "\n";
	outFile << "Total Rounds: " << static_cast<int>(GetRounds()) << "\n";
	outFile << "Current Round: " << static_cast<int>(m_game->GetNrRound() + 1) << "\n\n";

	outFile << "# Player 1\n";
	outFile << "Name: " << m_game->GetPlayer1().GetName() << "\n";
	outFile << "Color: " << m_game->GetPlayer1().GetColor() << "\n";
	outFile << "Score: " << m_game->GetPlayer1().GetScore() << "\n";
	outFile << "Illusion Used: " << m_game->GetPlayer1().GetHasUsedIllusion() << "\n\n";

	outFile << "# Player 2\n";
	outFile << "Name: " << m_game->GetPlayer2().GetName() << "\n";
	outFile << "Color: " << m_game->GetPlayer2().GetColor() << "\n";
	outFile << "Score: " << m_game->GetPlayer2().GetScore() << "\n";
	outFile << "Illusion Used: " << m_game->GetPlayer2().GetHasUsedIllusion() << "\n\n";

	outFile << "# Board\n";
	const auto& board = m_game->GetBoardRef().GetGrid();
	for (size_t i = 0; i < board.size(); ++i) {
		for (size_t j = 0; j < board[i].size(); ++j) {
			if (board[i][j].has_value()) {
				outFile << "Cell(" << i << "," << j << "): ";
				auto tempStack = board[i][j].value();
				while (!tempStack.empty()) {
					const auto& card = tempStack.top();
					outFile << "[" << static_cast<int>(card.GetValue()) << " " << card.GetColor() << " " << card.GetPosition() << "] ";
					tempStack.pop();
				}
				outFile << "\n";
			}
		}
	}

	outFile << "# Additional Mode Data\n";
	outFile << "Illusions Saved\n";

	outFile.close();

	if (outFile.fail()) {
		std::cerr << "Error while writing to the file " << filename << ".\n";
	}
	else {
		std::cout << "Game saved successfully to " << filename << ".\n";
	}
}
