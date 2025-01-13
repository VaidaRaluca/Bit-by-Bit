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
		void StartNewGame(Player player1, Player player2, const std::string& gameMode);
		void SaveGame();   // Metoda pentru salvarea unui joc
		void LoadGame();   // Metoda pentru incarcarea unui joc

		void AutoSave(const std::string& autosaveFile = "saves/autosave.dat");
		void LoadAutoSave();
		void BackupAutosave();
		void DisplaySaveFileSize(const std::string& filePath) const;
		void DeleteSave(const std::string& saveFileName);
		void DeleteSaveInteractive();
		void ResetGame();
		void DisplayPlayerStats() const;
		//ChooseGame
		static const std::string& chooseGameMode();
	private:
		//Analiza post joc
		void AnalyzeGameResults();                           
		void DisplayGlobalStats() const;                     
		void SaveGlobalStats(const std::string& filename) const; 
		void LoadGlobalStats(const std::string& filename);   

		//Leader board
		void UpdateLeaderboard();  
		void DisplayLeaderboard() const;                        
		void SaveLeaderboard(const std::string& filename) const; 
		void LoadLeaderboard(const std::string& filename);       

		void AnalyzeGameResults() const;

		void StartAutoSaveTimer();

		std::string GetFileName() const;
		void SavePlayer(std::ofstream& outFile, const Player& player, const std::string& header) const;
		void SaveBoard(std::ofstream& outFile, const Board& board) const;
		void SaveCell(std::ofstream& outFile, const std::optional<std::stack<Card>>& cell) const;

		std::string GetFileNameToLoad() const;
		Player LoadPlayer(std::ifstream& inFile) const;
		Board LoadBoard(std::ifstream& inFile) const;

		std::string HandleFileNameOverwrite() const;
		bool ConfirmOverwrite(const std::string& fileName) const;
		void DisplaySaveFiles() const;
		bool ConfirmAction(const std::string& actionDescription) const;
		bool ConfirmationForSave(const std::string& fileName) const;

		//LoadGame
		std::string PromptFileName();
		bool HandleSpecialCommands(const std::string& fileName, const std::string& saveDirectory);
		bool LoadGameFromFile(const std::string& filePath);

		//SaveGame
		std::string PromptFileNameForSave();
		bool SaveGameToFile(const std::string& filePath);
	};
}
