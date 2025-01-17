#pragma once
#include <memory>
#include <iomanip>
#include<filesystem>
#include<thread>
#include<chrono>
#include "Game.h"
#include "Board.h"
#include "AMode.h"
#include "BMode.h"
#include "CMode.h"
#include "BCMode.h"

namespace eter
{
	 class GameManager
	{
	private:
		Game m_game;
		std::unique_ptr<AMode> m_amode;
		std::unique_ptr<BMode> m_bmode;
		std::unique_ptr<CMode> m_cmode;
		std::unique_ptr<BCMode> m_bcmode;

		std::vector<std::pair<std::string, int>> m_leaderboard; 

		int m_player1TotalWins = 0;
		int m_player2TotalWins = 0;
		int m_player1TotalRounds = 0;
		int m_player2TotalRounds = 0;
		int m_player1TotalScore = 0;
		int m_player2TotalScore = 0;
		int m_draws = 0;            
	public:
		GameManager() = default;
		GameManager(const Game& game);

		const Game& GetGame()const;
		void SetGame(Game game);
		void startNewGame(Player player1, Player player2, const std::string& gameMode);
		void saveGame();  
		void loadGame();   

		void autoSave(const std::string& autosaveFile = "saves/autosave.dat");
		void loadAutoSave();
		void backupAutosave();
		void displaySaveFileSize(const std::string& filePath) const;
		void deleteSave(const std::string& saveFileName);
		void deleteSaveInteractive();
		void resetGame();
		void displayPlayerStats() const;

		static const std::string& chooseGameMode();
	private:

		void analyzeGameResults();                           
		void displayGlobalStats() const;                     
		void saveGlobalStats(const std::string& filename) const; 
		void loadGlobalStats(const std::string& filename);   


		void updateLeaderboard();  
		void displayLeaderboard() const;                        
		void saveLeaderboard(const std::string& filename) const; 
		void loadLeaderboard(const std::string& filename);       

		void analyzeGameResults() const;

		void startAutoSaveTimer();

		std::string GetFileName() const;
		void savePlayer(std::ofstream& outFile, const Player& player, const std::string& header) const;
		void saveBoard(std::ofstream& outFile, const Board& board) const;
		void saveCell(std::ofstream& outFile, const std::optional<std::stack<Card>>& cell) const;

		std::string GetFileNameToLoad() const;
		Player loadPlayer(std::ifstream& inFile) const;
		Board loadBoard(std::ifstream& inFile) const;

		std::string handleFileNameOverwrite() const;
		bool confirmOverwrite(const std::string& fileName) const;
		void displaySaveFiles() const;
		bool confirmAction(const std::string& actionDescription) const;
		bool confirmationForSave(const std::string& fileName) const;

		std::string promptFileName();
		bool handleSpecialCommands(const std::string& fileName, const std::string& saveDirectory);
		bool loadGameFromFile(const std::string& filePath);

		std::string promptFileNameForSave();
		bool saveGameToFile(const std::string& filePath);
	};
}
