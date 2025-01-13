#include "GameManager.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <regex>
//import player;
//import game;
using namespace eter;

GameManager::GameManager(const Game& game) :
    m_game{ game }
{
}

const Game& GameManager::GetGame() const
{
    return m_game;
}

void GameManager::SetGame(Game game)
{
    m_game = Game(game);
}

void GameManager::startNewGame(Player player1, Player player2, const std::string& gameMode)
{
    m_game = Game(player1, player2, gameMode);
    m_game.printPlayers();
    if (gameMode == "AMode")
    {
        m_amode = std::make_unique<AMode>(&m_game);
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

void GameManager::loadGame() {
    const std::string saveDirectory = "saves/";

    while (true) {
        std::string fileName = promptFileName();

        if (fileName.empty()) {
            std::cout << "No file name provided. Please try again.\n";
            continue;
        }

        if (handleSpecialCommands(fileName, saveDirectory)) {
            continue;
        }

        if (!confirmAction("Player, do you want to load the save file '" + fileName + "'")) {
            std::cout << "File load canceled. You can choose another file or quit.\n";
            continue;
        }

        const std::string filePath = saveDirectory + fileName;
        if (!loadGameFromFile(filePath)) {
            continue;
        }
        return;
    }
}

void GameManager::saveGame() {
    const std::string saveDirectory = "saves/";

    while (true) {
        std::string fileName = promptFileNameForSave();

        if (fileName.empty()) {
            std::cout << "No file name provided. Please try again.\n";
            continue;
        }

        if (!confirmationForSave(fileName)) {
            std::cout << "Save operation canceled. You can choose another file or quit.\n";
            continue;
        }

        const std::string filePath = saveDirectory + fileName;
        if (saveGameToFile(filePath)) {
            displaySaveFileSize(filePath);
            return;
        }
    }
}

void GameManager::autoSave(const std::string& autosaveFile) {
    backupAutosave();

    try {
        const std::string saveDirectory = autosaveFile.substr(0, autosaveFile.find_last_of("/\\"));
        if (!std::filesystem::exists(saveDirectory)) {
            std::filesystem::create_directories(saveDirectory);
            std::cout << "Directory '" << saveDirectory << "' created for autosave.\n";
        }

        std::ofstream outFile(autosaveFile, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file '" << autosaveFile << "' for autosaving.\n";
            return;
        }

        savePlayer(outFile, m_game.GetPlayer1(), "# Player 1");
        savePlayer(outFile, m_game.GetPlayer2(), "# Player 2");
        saveBoard(outFile, m_game.GetBoard());

        outFile.close();
        if (outFile.fail()) {
            throw std::runtime_error("Failed to write game data to the autosave file.");
        }

        std::cout << "Autosave completed successfully to '" << autosaveFile << "'.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error during autosaving: " << e.what() << "\n";
    }
}

void GameManager::loadAutoSave() {
    const std::string autosaveFile = "saves/autosave.dat";

    std::ifstream inFile(autosaveFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Autosave file not found.\n";
        return;
    }

    try {
        Player player1 = loadPlayer(inFile);
        Player player2 = loadPlayer(inFile);
        Board board = loadBoard(inFile);

        inFile.close();

        startNewGame(player1, player2, "LoadedMode");
        std::cout << "Game successfully loaded from autosave.\n";
    }
    catch (const std::exception& e) {
        inFile.close();
        std::cerr << "Error during loading autosave: " << e.what() << "\n";
    }
}

void GameManager::backupAutosave() {
    const std::string autosaveFile = "saves/autosave.dat";
    const std::string backupFile = "saves/autosave_backup.dat";

    std::ifstream src(autosaveFile, std::ios::binary);
    std::ofstream dest(backupFile, std::ios::binary);

    if (!src.is_open() || !dest.is_open()) {
        std::cerr << "Error creating backup of autosave.\n";
        return;
    }

    dest << src.rdbuf();
    src.close();
    dest.close();

    std::cout << "Backup of autosave created successfully.\n";
}

void GameManager::displaySaveFileSize(const std::string& filePath) const {
    try {
        std::uintmax_t fileSize = std::filesystem::file_size(filePath);
        std::cout << "The save file '" << filePath << "' occupies "
            << fileSize / 1024.0 << " KB.\n"; 
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error retrieving file size: " << e.what() << '\n';
    }
}

void GameManager::deleteSaveInteractive() {
    std::cout << "Enter the name of the save file to delete, or press 'Q' to quit: ";
    std::string saveFileName;
    std::getline(std::cin, saveFileName);

    if (saveFileName == "Q" || saveFileName == "q") {
        std::cout << "Exiting delete save operation.\n";
        return;
    }

    deleteSave(saveFileName);
}

void GameManager::deleteSave(const std::string& saveFileName) {
    const std::string saveDirectory = "saves/";
    const std::string filePath = saveDirectory + saveFileName;

    try {
        if (std::filesystem::exists(filePath)) {
            std::filesystem::remove(filePath); 
            std::cout << "Save file '" << filePath << "' has been deleted successfully.\n";
        }
        else {
            std::cerr << "Error: Save file '" << filePath << "' does not exist.\n";
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting file '" << filePath << "': " << e.what() << '\n';
    }
}

void GameManager::resetGame() {
    std::cout << "Resetting the game to its initial state...\n";

    // Resetăm tabla de joc
    m_game.GetBoardRef().clear();

    m_game.GetPlayer1Ref().SetScore(0);
    m_game.GetPlayer2Ref().SetScore(0);

    m_game.GetPlayer1Ref().GetCardsInHand().clear();
    m_game.GetPlayer1Ref().GetPlayedCards().clear();
    m_game.GetPlayer1Ref().GetEliminatedCards().clear();

    m_game.GetPlayer2Ref().GetCardsInHand().clear();
    m_game.GetPlayer2Ref().GetPlayedCards().clear();
    m_game.GetPlayer2Ref().GetEliminatedCards().clear();

    m_game.SetIsUsedExplosion(false);
    m_game.SetCountTurnForReturnedCards(0);
    m_game.SetGameMods(""); 

    std::cout << "Game has been reset. You can start a new game.\n";
}

void GameManager::displayPlayerStats() const {
    const Player& player1 = m_game.GetPlayer1();
    const Player& player2 = m_game.GetPlayer2();

    // Calculare statistici suplimentare
    size_t player1TotalCardsPlayed = player1.GetPlayedCards().size();
    size_t player2TotalCardsPlayed = player2.GetPlayedCards().size();

    size_t player1TotalCardsEliminated = player1.GetEliminatedCards().size();
    size_t player2TotalCardsEliminated = player2.GetEliminatedCards().size();

    uint8_t player1RoundsWon = m_game.GetPlayer1Wins();
    uint8_t player2RoundsWon = m_game.GetPlayer2Wins();

    size_t totalRounds = player1RoundsWon + player2RoundsWon;
    float player1WinPercentage = totalRounds > 0 ? (player1RoundsWon * 100.0f / totalRounds) : 0.0f;
    float player2WinPercentage = totalRounds > 0 ? (player2RoundsWon * 100.0f / totalRounds) : 0.0f;

    // Determinare cel mai bun jucator
    const std::string& bestPlayer = (player1RoundsWon > player2RoundsWon) ? player1.GetName() : player2.GetName();

    // Afisare statistici
    std::cout << "\n===== Player Statistics =====\n";

    // Player 1
    std::cout << "Player 1: " << player1.GetName() << "\n";
    std::cout << std::setw(20) << "Cards Played: " << player1TotalCardsPlayed << "\n";
    std::cout << std::setw(20) << "Cards Eliminated: " << player1TotalCardsEliminated << "\n";
    std::cout << std::setw(20) << "Rounds Won: " << static_cast<int>(player1RoundsWon)
        << " (" << player1WinPercentage << "%)\n";
    std::cout << "-----------------------------\n";

    // Player 2
    std::cout << "Player 2: " << player2.GetName() << "\n";
    std::cout << std::setw(20) << "Cards Played: " << player2TotalCardsPlayed << "\n";
    std::cout << std::setw(20) << "Cards Eliminated: " << player2TotalCardsEliminated << "\n";
    std::cout << std::setw(20) << "Rounds Won: " << static_cast<int>(player2RoundsWon)
        << " (" << player2WinPercentage << "%)\n";
    std::cout << "=============================\n";

    // Evidentierea castigator
    if (player1RoundsWon != player2RoundsWon) {
        std::cout << "Best Player: " << bestPlayer << "\n";
    }
    else {
        std::cout << "It's a tie! Both players performed equally well!\n";
    }
}

void GameManager::updateLeaderboard() {
    const Player& player1 = m_game.GetPlayer1();
    const Player& player2 = m_game.GetPlayer2();

    uint8_t player1RoundsWon = m_game.GetPlayer1Wins();
    uint8_t player2RoundsWon = m_game.GetPlayer2Wins();

    // Actualizează runde castigate
    m_player1TotalRounds += player1RoundsWon;
    m_player2TotalRounds += player2RoundsWon;

    // Actualizeaza scorurile totale
    m_player1TotalScore += player1.GetScore();
    m_player2TotalScore += player2.GetScore();

    // Determina castigatorul si victoriile totale
    if (player1RoundsWon > player2RoundsWon) {
        ++m_player1TotalWins;
    }
    else if (player2RoundsWon > player1RoundsWon) {
        ++m_player2TotalWins;
    }
}

void GameManager::displayLeaderboard() const {
    std::cout << "\n===== Leaderboard =====\n";
    std::cout << "Player 1: " << m_game.GetPlayer1().GetName() << "\n";
    std::cout << "  Total Wins: " << m_player1TotalWins << "\n";
    std::cout << "  Total Rounds Won: " << m_player1TotalRounds << "\n";
    std::cout << "  Total Score: " << m_player1TotalScore << "\n";

    std::cout << "\nPlayer 2: " << m_game.GetPlayer2().GetName() << "\n";
    std::cout << "  Total Wins: " << m_player2TotalWins << "\n";
    std::cout << "  Total Rounds Won: " << m_player2TotalRounds << "\n";
    std::cout << "  Total Score: " << m_player2TotalScore << "\n";

    if (m_player1TotalWins > m_player2TotalWins) {
        std::cout << "\nBest Player: " << m_game.GetPlayer1().GetName() << "\n";
    }
    else if (m_player2TotalWins > m_player1TotalWins) {
        std::cout << "\nBest Player: " << m_game.GetPlayer2().GetName() << "\n";
    }
    else {
        std::cout << "\nIt's a tie between the two players!\n";
    }
    std::cout << "=======================\n";
}

void GameManager::saveLeaderboard(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving leaderboard.\n";
        return;
    }

    outFile << m_player1TotalWins << " " << m_player1TotalRounds << " " << m_player1TotalScore << "\n";
    outFile << m_player2TotalWins << " " << m_player2TotalRounds << " " << m_player2TotalScore << "\n";

    outFile.close();
    std::cout << "Leaderboard saved to " << filename << ".\n";
}

void GameManager::loadLeaderboard(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for loading leaderboard.\n";
        return;
    }

    inFile >> m_player1TotalWins >> m_player1TotalRounds >> m_player1TotalScore;
    inFile >> m_player2TotalWins >> m_player2TotalRounds >> m_player2TotalScore;

    inFile.close();
    std::cout << "Leaderboard loaded from " << filename << ".\n";
}

void GameManager::analyzeGameResults() {
    namespace fs = std::filesystem;

    // Analiza jocului curent
    const Player& player1 = m_game.GetPlayer1();
    const Player& player2 = m_game.GetPlayer2();

    uint8_t player1RoundsWon = m_game.GetPlayer1Wins();
    uint8_t player2RoundsWon = m_game.GetPlayer2Wins();

    if (player1RoundsWon > player2RoundsWon) {
        ++m_player1TotalWins;
        std::cout << "Game Winner: " << player1.GetName() << "\n";
    }
    else if (player2RoundsWon > player1RoundsWon) {
        ++m_player2TotalWins;
        std::cout << "Game Winner: " << player2.GetName() << "\n";
    }
    else {
        ++m_draws;
        std::cout << "The game ended in a tie!\n";
    }

    std::cout << "\n===== Current Game Analysis =====\n";
    std::cout << "Player 1: " << player1.GetName() << "\n";
    std::cout << std::setw(25) << "Rounds Won: " << static_cast<int>(player1RoundsWon) << "\n";
    std::cout << std::setw(25) << "Total Score: " << player1.GetScore() << "\n";
    std::cout << std::setw(25) << "Cards Played: " << player1.GetPlayedCards().size() << "\n";
    std::cout << std::setw(25) << "Cards Eliminated: " << player1.GetEliminatedCards().size() << "\n";

    std::cout << "-----------------------------\n";

    std::cout << "Player 2: " << player2.GetName() << "\n";
    std::cout << std::setw(25) << "Rounds Won: " << static_cast<int>(player2RoundsWon) << "\n";
    std::cout << std::setw(25) << "Total Score: " << player2.GetScore() << "\n";
    std::cout << std::setw(25) << "Cards Played: " << player2.GetPlayedCards().size() << "\n";
    std::cout << std::setw(25) << "Cards Eliminated: " << player2.GetEliminatedCards().size() << "\n";

    std::cout << "=============================\n";

    // Analiza salvarilor
    std::string saveDirectory = "saves/";
    int totalPlayer1Wins = 0;
    int totalPlayer2Wins = 0;
    int totalDraws = 0;

    for (const auto& entry : fs::directory_iterator(saveDirectory)) {
        std::ifstream inFile(entry.path());
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open file " << entry.path() << "\n";
            continue;
        }

        int savedPlayer1RoundsWon = 0, savedPlayer2RoundsWon = 0;
        inFile >> savedPlayer1RoundsWon >> savedPlayer2RoundsWon;

        if (savedPlayer1RoundsWon > savedPlayer2RoundsWon) {
            ++totalPlayer1Wins;
        }
        else if (savedPlayer2RoundsWon > savedPlayer1RoundsWon) {
            ++totalPlayer2Wins;
        }
        else {
            ++totalDraws;
        }

        inFile.close();
    }

    std::cout << "\n===== Analysis of All Saves =====\n";
    std::cout << "Total Games Won by Player 1: " << totalPlayer1Wins << "\n";
    std::cout << "Total Games Won by Player 2: " << totalPlayer2Wins << "\n";
    std::cout << "Total Draws: " << totalDraws << "\n";

    if (totalPlayer1Wins > totalPlayer2Wins) {
        std::cout << "Overall Winner: Player 1\n";
    }
    else if (totalPlayer2Wins > totalPlayer1Wins) {
        std::cout << "Overall Winner: Player 2\n";
    }
    else {
        std::cout << "It's a tie in overall games!\n";
    }
    std::cout << "=============================\n";
}

void GameManager::displayGlobalStats() const {
    std::cout << "\n===== Global Statistics =====\n";
    std::cout << "Total Games Won by " << m_game.GetPlayer1().GetName() << ": " << m_player1TotalWins << "\n";
    std::cout << "Total Games Won by " << m_game.GetPlayer2().GetName() << ": " << m_player2TotalWins << "\n";
    std::cout << "Total Draws: " << m_draws << "\n";

    // Determina cine este castigatorul general
    if (m_player1TotalWins > m_player2TotalWins) {
        std::cout << "Overall Winner: " << m_game.GetPlayer1().GetName() << "\n";
    }
    else if (m_player2TotalWins > m_player1TotalWins) {
        std::cout << "Overall Winner: " << m_game.GetPlayer2().GetName() << "\n";
    }
    else {
        std::cout << "It's a tie in overall games!\n";
    }
    std::cout << "=============================\n";
}

void GameManager::saveGlobalStats(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not save global statistics.\n";
        return;
    }
    outFile << m_player1TotalWins << " " << m_player2TotalWins << " " << m_draws << "\n";
    outFile.close();
    std::cout << "Global statistics saved to " << filename << ".\n";
}

void GameManager::loadGlobalStats(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not load global statistics.\n";
        return;
    }
    inFile >> m_player1TotalWins >> m_player2TotalWins >> m_draws;
    inFile.close();
    std::cout << "Global statistics loaded from " << filename << ".\n";
}

//Functii auxiliare

void GameManager::startAutoSaveTimer() {
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(1));
            autoSave();
        }
        }).detach();
}

std::string GameManager::GetFileName() const {
    std::string fileName;
    std::cout << "Enter the name of the save file (or press Enter for default 'saved_game.txt'): ";
    std::getline(std::cin, fileName);

    if (fileName.empty()) {
        fileName = "saved_game.txt";
    }

    return fileName;
}

void GameManager::savePlayer(std::ofstream& outFile, const Player& player, const std::string& header) const {
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

void GameManager::saveBoard(std::ofstream& outFile, const Board& board) const {
    outFile << "# Board\n";

    for (size_t row = 0; row < board.GetIndexMax(); ++row) {
        for (size_t col = 0; col < board.GetIndexMax(); ++col) {
            saveCell(outFile, board.GetGrid()[row][col]);
        }
    }
}

void GameManager::saveCell(std::ofstream& outFile, const std::optional<std::stack<Card>>& cell) const {
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

Player GameManager::loadPlayer(std::ifstream& inFile) const {
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

Board GameManager::loadBoard(std::ifstream& inFile) const {
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

std::string GameManager::handleFileNameOverwrite() const {
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

bool GameManager::confirmOverwrite(const std::string& fileName) const {
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

void GameManager::displaySaveFiles() const {
    if (!confirmAction("Do you want to view the list of save files")) {
        std::cout << "Action canceled.\n";
        return;
    }

    const std::string saveDirectory = "saves/";
    std::vector<std::string> saveFiles;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(saveDirectory)) {
            if (entry.is_regular_file()) {
                saveFiles.push_back(entry.path().filename().string());
            }
        }

        if (saveFiles.empty()) {
            std::cout << "No save files found in '" << saveDirectory << "'.\n";
        }
        else {
            std::cout << "Available save files:\n";
            for (const auto& file : saveFiles) {
                std::cout << " - " << file << '\n';
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing save directory: " << e.what() << '\n';
    }
}

bool GameManager::confirmAction(const std::string& actionDescription) const {
    std::cout << actionDescription << " (Y/N): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    return (toupper(choice) == 'Y');
}

bool GameManager::confirmationForSave(const std::string& fileName) const {
    std::cout << "Do you want to save the game to '" << fileName << "'? (Y/N): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    return (toupper(choice) == 'Y');
}

//LoadGame

std::string GameManager::promptFileName() {
    std::cout << "Enter the name of the save file to load, or press 'L' to list all save files, or 'Q' to quit: ";
    std::string fileName;
    std::getline(std::cin, fileName);
    return fileName;
}

bool GameManager::handleSpecialCommands(const std::string& fileName, const std::string& saveDirectory) {
    if (fileName == "D" || fileName == "d") {
        std::cout << "Enter the name of the save file to delete: ";
        std::string deleteFileName;
        std::getline(std::cin, deleteFileName);
        deleteSave(deleteFileName);
        return true;
    }

    if (fileName == "AUTO" || fileName == "auto") {
        loadAutoSave();
        return true;
    }

    if (fileName == "L" || fileName == "l") {
        displaySaveFiles();
        return true;
    }

    if (fileName == "Q" || fileName == "q") {
        std::cout << "Exiting LoadGame.\n";
        return true;
    }

    return false;
}

bool GameManager::loadGameFromFile(const std::string& filePath) {
    displaySaveFileSize(filePath);

    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: File '" << filePath << "' could not be opened. Please try again.\n";
        return false;
    }

    try {
        Player player1 = loadPlayer(inFile);
        Player player2 = loadPlayer(inFile);
        Board board = loadBoard(inFile);

        inFile.close();

        startNewGame(player1, player2, "LoadedMode");
        std::cout << "Game successfully loaded from '" << filePath << "'!\n";
        return true;
    }
    catch (const std::exception& e) {
        inFile.close();
        std::cerr << "Error during loading: " << e.what() << "\n";
        std::cout << "Please choose another file or quit.\n";
        return false;
    }
}

//SaveGame

std::string GameManager::promptFileNameForSave() {
    std::cout << "Enter the name of the save file, or press 'Q' to quit: ";
    std::string fileName;
    std::getline(std::cin, fileName);

    if (fileName == "Q" || fileName == "q") {
        std::cout << "Exiting SaveGame.\n";
        return "";
    }

    return fileName;
}

bool GameManager::saveGameToFile(const std::string& filePath) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filePath << "' for saving. Please try again.\n";
        return false;
    }

    try {
        savePlayer(outFile, m_game.GetPlayer1(), "# Player 1");
        savePlayer(outFile, m_game.GetPlayer2(), "# Player 2");
        saveBoard(outFile, m_game.GetBoard());

        outFile.close();
        if (outFile.fail()) {
            throw std::runtime_error("Failed to write game data to the file.");
        }

        std::cout << "Game successfully saved to '" << filePath << "'!\n";
        return true;
    }
    catch (const std::exception& e) {
        outFile.close();
        std::cerr << "Error during saving: " << e.what() << "\n";
        std::cout << "Save operation failed. You can choose another file or quit.\n";
        return false;
    }
}



const std::string& eter::GameManager::chooseGameMode()
{
    static std::string gameMode;
    const std::regex modeRegex("^A|B|C|(BC)$");
    std::cout << "Please choose the mode you want to play :\nA for AMode\nB for BMode \nC for CMode \nBC for BCMode\n";
    std::cin >> gameMode;
    if (std::regex_match(gameMode, modeRegex) == false)
    {
        while (std::regex_match(gameMode, modeRegex) == false)
        {
            std::cout << "Introduce a valid mode : ";
            std::cin >> gameMode;
        }
    }
    gameMode += "Mode";
    std::cout << gameMode << " was chosen successfully!\n";
    return gameMode;
}
