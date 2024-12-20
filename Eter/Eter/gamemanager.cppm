export module gamemanager;

import <memory>;
import<filesystem>;
import<thread>;
import<chrono>;
import game;
import board;
import bmode;
import amode;
import cmode;
import bcmode;

namespace eter
{
	export class GameManager
	{
	private:
		Game m_game;
		std::unique_ptr<AMode> m_amode;
		std::unique_ptr<BMode> m_bmode;
		std::unique_ptr<CMode> m_cmode;
		std::unique_ptr<BCMode> m_bcmode;
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

	private:
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

	};
}
