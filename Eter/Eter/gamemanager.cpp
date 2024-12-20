module gamemanager;

import <fstream>;
import <string>;
import <stdexcept>;
import <iostream>;
import <sstream>;
import player;
import game;
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

void GameManager::StartNewGame(Player player1, Player player2, const std::string& gameMode)
{
    m_game = Game(player1, player2, gameMode);
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

void GameManager::LoadGame() {
    const std::string saveDirectory = "saves/";

    while (true) {
        std::cout << "Enter the name of the save file to load, or press 'L' to list all save files, or 'Q' to quit: ";
        std::string fileName;
        std::getline(std::cin, fileName);

        if (fileName == "D" || fileName == "d") {
            std::cout << "Enter the name of the save file to delete: ";
            std::string deleteFileName;
            std::getline(std::cin, deleteFileName);
            DeleteSave(deleteFileName);
            continue;
        }

        if (fileName == "AUTO" || fileName == "auto") {
            LoadAutoSave();
            return;
        }

        if (fileName == "L" || fileName == "l") {
            DisplaySaveFiles();
            continue;
        }

        if (fileName == "Q" || fileName == "q") {
            std::cout << "Exiting LoadGame.\n";
            return;
        }

        if (fileName.empty()) {
            std::cout << "No file name provided. Please try again.\n";
            continue;
        }

        if (!ConfirmAction("Player, do you want to load the save file '" + fileName + "'")) {
            std::cout << "File load canceled. You can choose another file or quit.\n";
            continue;
        }

        const std::string filePath = saveDirectory + fileName;

        DisplaySaveFileSize(filePath);

        std::ifstream inFile(filePath, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "Error: File '" << filePath << "' could not be opened. Please try again.\n";
            continue;
        }

        try {
            Player player1 = LoadPlayer(inFile);
            Player player2 = LoadPlayer(inFile);
            Board board = LoadBoard(inFile);

            inFile.close();

            StartNewGame(player1, player2, "LoadedMode");
            std::cout << "Game successfully loaded from '" << filePath << "'!\n";
            return;
        }
        catch (const std::exception& e) {
            inFile.close();
            std::cerr << "Error during loading: " << e.what() << "\n";
            std::cout << "Please choose another file or quit.\n";
        }
    }
}

void GameManager::SaveGame() {
    const std::string saveDirectory = "saves/";

    while (true) {
        std::cout << "Enter the name of the save file, or press 'Q' to quit: ";
        std::string fileName;
        std::getline(std::cin, fileName);


        if (fileName == "Q" || fileName == "q") {
            std::cout << "Exiting SaveGame.\n";
            return;
        }

        if (fileName.empty()) {
            std::cout << "No file name provided. Please try again.\n";
            continue;
        }

        const std::string filePath = saveDirectory + fileName;

        if (!ConfirmationForSave(fileName)) {
            std::cout << "Save operation canceled. You can choose another file or quit.\n";
            continue;
        }


        std::ofstream outFile(filePath, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file '" << filePath << "' for saving. Please try again.\n";
            continue;
        }

        try {
            SavePlayer(outFile, m_game.GetPlayer1(), "# Player 1");
            SavePlayer(outFile, m_game.GetPlayer2(), "# Player 2");
            SaveBoard(outFile, m_game.GetBoard());

            outFile.close();
            if (outFile.fail()) {
                throw std::runtime_error("Failed to write game data to the file.");
            }

            std::cout << "Game successfully saved to '" << filePath << "'!\n";

            DisplaySaveFileSize(filePath);

            return;
        }
        catch (const std::exception& e) {
            outFile.close();
            std::cerr << "Error during saving: " << e.what() << "\n";
            std::cout << "Save operation failed. You can choose another file or quit.\n";
        }
    }
}

void GameManager::AutoSave(const std::string& autosaveFile) {
    BackupAutosave();

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

        SavePlayer(outFile, m_game.GetPlayer1(), "# Player 1");
        SavePlayer(outFile, m_game.GetPlayer2(), "# Player 2");
        SaveBoard(outFile, m_game.GetBoard());

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

void GameManager::LoadAutoSave() {
    const std::string autosaveFile = "saves/autosave.dat";

    std::ifstream inFile(autosaveFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Autosave file not found.\n";
        return;
    }

    try {
        Player player1 = LoadPlayer(inFile);
        Player player2 = LoadPlayer(inFile);
        Board board = LoadBoard(inFile);

        inFile.close();

        StartNewGame(player1, player2, "LoadedMode");
        std::cout << "Game successfully loaded from autosave.\n";
    }
    catch (const std::exception& e) {
        inFile.close();
        std::cerr << "Error during loading autosave: " << e.what() << "\n";
    }
}

void GameManager::BackupAutosave() {
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

void GameManager::DisplaySaveFileSize(const std::string& filePath) const {
    try {
        std::uintmax_t fileSize = std::filesystem::file_size(filePath);
        std::cout << "The save file '" << filePath << "' occupies "
            << fileSize / 1024.0 << " KB.\n"; 
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error retrieving file size: " << e.what() << '\n';
    }
}

void GameManager::DeleteSaveInteractive() {
    std::cout << "Enter the name of the save file to delete, or press 'Q' to quit: ";
    std::string saveFileName;
    std::getline(std::cin, saveFileName);

    if (saveFileName == "Q" || saveFileName == "q") {
        std::cout << "Exiting delete save operation.\n";
        return;
    }

    DeleteSave(saveFileName);
}

void GameManager::DeleteSave(const std::string& saveFileName) {
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

//Functii auxiliare

void GameManager::StartAutoSaveTimer() {
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(1));
            AutoSave();
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

void GameManager::DisplaySaveFiles() const {
    if (!ConfirmAction("Do you want to view the list of save files")) {
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

bool GameManager::ConfirmAction(const std::string& actionDescription) const {
    std::cout << actionDescription << " (Y/N): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    return (toupper(choice) == 'Y');
}

bool GameManager::ConfirmationForSave(const std::string& fileName) const {
    std::cout << "Do you want to save the game to '" << fileName << "'? (Y/N): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    return (toupper(choice) == 'Y');
}
