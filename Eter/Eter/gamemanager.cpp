module gamemanager;

import <fstream>;
import <string>;
import <stdexcept>;
import <iostream>;
import <sstream>;
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
			m_amode->applyModeRules();
		}
		if (gameMode == "BMode")
		{
			m_bmode = std::make_unique<BMode>(&m_game); 
            std::cout << "Starting B mode game\n";
			m_bmode->applyModeRules(); 
		}
		if (gameMode == "CMode")
		{
			m_cmode = std::make_unique<CMode>(&m_game);
            std::cout << "Starting C mode game\n";
			m_cmode->applyModeRules();
		}
        if (gameMode == "BCMode")
        {
            m_bcmode = std::make_unique<BCMode>(&m_game);
            std::cout << "Starting B+C mode game\n";
            m_bcmode->applyModeRules();
        }
}

void GameManager::LoadGame() {
    std::string fileName = GetFileNameToLoad();

    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file for loading the game.");
    }

    try {
        Player player1 = LoadPlayer(inFile);
        Player player2 = LoadPlayer(inFile);
        Board board = LoadBoard(inFile);

        inFile.close();

        StartNewGame(player1, player2, "LoadedMode");
        std::cout << "Game successfully loaded from '" << fileName << "'!\n";
    }
    catch (const std::exception& e) {
        inFile.close();
        throw std::runtime_error(std::string("Error during loading: ") + e.what());
    }
}

void GameManager::SaveGame() {
    
    std::string fileName = HandleFileNameOverwrite();

    
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving the game.");
    }

    try {
        
        SavePlayer(outFile, m_game.GetPlayer1(), "# Player 1");
        SavePlayer(outFile, m_game.GetPlayer2(), "# Player 2");
        SaveBoard(outFile, m_game.GetBoard());
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error during saving: ") + e.what());
    }

    outFile.close();
    if (outFile.fail()) {
        throw std::runtime_error("Failed to save game data to the file.");
    }

    std::cout << "Game successfully saved to '" << fileName << "'!\n";
}

//Functii auxiliare

std::string GameManager::GetFileName() const {
    std::string fileName;
    std::cout << "Enter the name of the save file (or press Enter for default 'saved_game.txt'): ";
    std::getline(std::cin, fileName);

    if (fileName.empty()) {
        fileName = "saved_game.txt";
    }

    return fileName;
}

void GameManager::SavePlayer(std::ofstream& outFile, const Player& player, const std::string& header) const {
    outFile << header << "\n";
    outFile << player.GetName() << "\n";
    outFile << player.GetColor() << "\n";

    for (const auto& card : player.GetCardsInHand()) {
        outFile << static_cast<int>(card.GetValue()) << " "
            << card.GetColor() << " "
            << card.GetPosition() << "\n";
    }

    outFile << "---\n";
}

void GameManager::SaveBoard(std::ofstream& outFile, const Board& board) const {
    outFile << "# Board\n";

    for (size_t row = 0; row < board.GetRows(); ++row) {
        for (size_t col = 0; col < board.GetCols(); ++col) {
            SaveCell(outFile, board.GetGrid()[row][col]);
        }
    }
}

void GameManager::SaveCell(std::ofstream& outFile, const std::optional<std::stack<Card>>& cell) const {
    if (cell.has_value()) {
        auto tempStack = cell.value();
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

std::string GameManager::GetFileNameToLoad() const {
    std::string fileName;
    std::cout << "Enter the name of the save file to load: ";
    std::getline(std::cin, fileName);

    if (fileName.empty()) {
        throw std::runtime_error("File name cannot be empty.");
    }

    return fileName;
}

Player GameManager::LoadPlayer(std::ifstream& inFile) const {
    std::string line;
    std::getline(inFile, line);
    std::string playerName = line;

    std::getline(inFile, line);
    std::string playerColor = line;

    std::vector<Card> cards;
    while (std::getline(inFile, line) && line != "---") {
        std::istringstream cardStream(line);
        int value;
        std::string color;
        bool position;
        cardStream >> value >> color >> position;
        cards.emplace_back(value, color, position);
    }

    Player player(playerName, playerColor);
    player.SetCardsInHand(cards);
    return player;
}

Board GameManager::LoadBoard(std::ifstream& inFile) const {
    std::string line;
    std::getline(inFile, line);

    int rows, cols;
    std::istringstream boardStream(line);
    boardStream >> rows >> cols;

    Board board;

    for (int row = 0; row < rows; ++row) {
        std::getline(inFile, line);
        std::istringstream rowStream(line);
        for (int col = 0; col < cols; ++col) {
            std::string cellContent;
            rowStream >> cellContent;

            if (cellContent != "empty") {
                std::istringstream cardStream(cellContent);
                int value;
                std::string color;
                bool position;
                cardStream >> value >> color >> position;
                board.placeCard(row, col, Card(value, color, position));
            }
        }
    }

    return board;
}

std::string GameManager::HandleFileNameOverwrite() const {
    std::string fileName = GetFileName(); 

    std::ifstream checkFile(fileName);
    if (checkFile.is_open()) {
        checkFile.close();
        std::cout << "File '" << fileName << "' already exists.\n";
        std::cout << "Do you want to overwrite it or change the file name? (O for overwrite / C for change): ";
        char choice;
        std::cin >> choice;

        if (toupper(choice) == 'C') {
            std::cout << "Enter a new file name: ";
            std::cin.ignore(); 
            std::getline(std::cin, fileName); 
        }
    }

    return fileName; 
}

bool GameManager::ConfirmOverwrite(const std::string& fileName) const {
    std::ifstream checkFile(fileName);
    if (checkFile.is_open()) {
        checkFile.close();
        std::cout << "File '" << fileName << "' already exists. Do you want to overwrite it? (Y/N): ";
        char choice;
        std::cin >> choice;
        return (toupper(choice) == 'Y');
    }
    return true; 
}
