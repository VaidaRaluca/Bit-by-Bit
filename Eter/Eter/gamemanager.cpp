module gamemanager;

import <fstream>;
import <string>;
import <stdexcept>;
import player;
import game;
using namespace eter;

GameManager::GameManager(const Game& game):
	m_game{game}
{
}

const Game& GameManager::GetGame() const
{
	return m_game;
}

void GameManager::SetGame(Game game)
{
	m_game=Game( game) ;
}

void GameManager::StartNewGame(Player player1, Player player2, const std::string& gameMode)
{
		m_game = Game(player1, player2, gameMode);
		if (gameMode == "AMode")
		{
			m_amode= std::make_unique<AMode>(&m_game);
			std::cout << "Starting A mode game\n";
			m_amode->applyModeRulesModeA();
		}
		if (gameMode == "BMode")
		{
			m_bmode = std::make_unique<BMode>(&m_game); 
			m_bmode->applyModeRules(); 
		}
		if (gameMode == "CMode")
		{
			m_cmode = std::make_unique<CMode>(&m_game);
			m_cmode->applyModeRules();
		}
}

void GameManager::SaveGame() {
    std::string fileName;
    std::cout << "Enter the name of the save file (or press Enter for default 'saved_game.txt'): ";
    std::getline(std::cin, fileName);

    // Daca utilizatorul nu introduce nimic, folosim un nume implicit
    if (fileName.empty()) {
        fileName = "saved_game.txt";
    }

    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving the game.");
    }

    // Salvare informatii despre jucatorul 1
    const auto& player1 = m_game.GetPlayer1();
    outFile << player1.GetName() << "\n";
    outFile << player1.GetColor() << "\n";
    for (const auto& card : player1.GetCardsInHand()) {
        outFile << static_cast<int>(card.GetValue()) << " "
            << card.GetColor() << " "
            << card.GetPosition() << "\n";
    }

    // Marcare a sfarsitului datelor pentru jucatorul 1
    outFile << "---\n";

    // Salvam informatiile despre jucatorul 2
    const auto& player2 = m_game.GetPlayer2();
    outFile << player2.GetName() << "\n";
    outFile << player2.GetColor() << "\n";
    for (const auto& card : player2.GetCardsInHand()) {
        outFile << static_cast<int>(card.GetValue()) << " "
            << card.GetColor() << " "
            << card.GetPosition() << "\n";
    }

    // Marcare a sfarsitului datelor pentru jucatorul 2
    outFile << "---\n";

    // Salvare tabla de joc
    const auto& board = m_game.GetBoard();
    const auto& grid = board.GetGrid();
    for (size_t row = 0; row < board.GetRows(); ++row) {
        for (size_t col = 0; col < board.GetCols(); ++col) {
            if (grid[row][col].has_value()) {
                const auto& stack = grid[row][col].value();
                std::stack<Card> tempStack = stack;
                while (!tempStack.empty()) {
                    const Card& card = tempStack.top();
                    outFile << static_cast<int>(card.GetValue()) << " "
                        << card.GetColor() << " "
                        << card.GetPosition() << " ";
                    tempStack.pop();
                }
                outFile << "\n";
            }
            else {
                outFile << "empty\n";
            }
        }
    }

    outFile.close();
    if (outFile.fail()) {
        throw std::runtime_error("Failed to save game data to the file.");
    }

    std::cout << "Game successfully saved to '" << fileName << "'!\n";
}
