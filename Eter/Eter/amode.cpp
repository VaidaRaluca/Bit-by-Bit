module amode;
import player;
import board;
import explosion;
import <iostream>;
import <string>;


namespace eter {
	AMode::AMode(Game* game) : m_game(game), m_player1Wins(0), m_player2Wins(0) {
		if (!m_game) {
			std::cerr << "Game object is null in AMode constructor.\n";
		}
		m_player1 = m_game->GetPlayer1();
		m_player2 = m_game->GetPlayer2();
		m_board = m_game->GetBoard();
	}
	AMode::AMode(Player player1, Player player2, const Board& board) :
		m_player1{ player1 }, m_player2{ player2 }, m_board{ board }, m_player1Wins{ 0 }, m_player2Wins{ 0 } {}

	//AMode::AMode(Game* game) : m_game{ game } {}

	void AMode::startMatch() {
		m_isPlayerTurn = true;
		m_player1Wins = 0;
		m_player2Wins = 0;
		// m_game = std::make_unique<Game>(m_player1, m_player2, m_board, "Mode A");

		applyModeRules();

		// Bucla principala a jocului
		while (true) {
			std::cout << "Round " << m_game->GetNrRound() << "\n";

			Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
			std::cout << currentPlayer.GetName() << "'s turn!\n";

			// Solicita actiunea jucatorului
			Action action = promptPlayerAction();
			std::cout << "Action is "<<static_cast<int>(action)<<'\n';
			if (action == Action::PlaceCard) {
				handlePlaceCard();
			}
			else if (action == Action::ActivateIllusion) {
				handleActivateIllusion();
			}
			else if (action == Action::ActivateExplosion) {
				handleActivateExplosion();
			}
			else {
				std::cout << "Unexpected action. Try again.\n";
				continue;
			}

			// Verifica starea jocului si castigatorul
			handleGameOverCheck();
			if (m_board.isBoardFull()) {
				std::cout << "It's a tie!\n";
				break;
			}

			// Incrementare runda si schimbare jucator
			m_game->IncrementNrRound();
			m_isPlayerTurn = !m_isPlayerTurn;
		}
	}


	void AMode::applyModeRules() {
		std::cout << "Applying Mode A rules...\n";

		// Verificare dimensiune tabla
		if (m_board.GetGrid().size() != 3 && m_board.GetGrid().size() != 4) {
			std::cerr << "Invalid board size!\n";
			return;
		}

		std::vector<Player> players = { m_player1, m_player2 };
		for (auto& player : players) {
			for (auto& card : player.GetCardsInHand()) {
				std::cout << "Card " << card.GetValue()
					<< (isCardPlaceable(card) ? " can be placed.\n" : " cannot be placed!\n");
			}
		}
		if (checkWinningCondition()) {
			std::cout << "We have a winner!\n";
		}
	}


	void AMode::AssignCardsInHandModeA() {
		std::vector<Card> cardsForPlayer1{
			  {1, "red", true}, {1, "red", true},
	          {2, "red", true}, {2, "red", true},
	          {3, "red", true}, {3, "red", true},
	          {4, "red", true}
		};

		std::vector<Card> cardsForPlayer2{
			 {1, "blue", true}, {1, "blue", true},
	         {2, "blue", true}, {2, "blue", true},
	         {3, "blue", true}, {3, "blue", true},
	         {4, "blue", true}
		};

		if (m_game) {
			m_game->GetPlayer1().SetCardsInHand(cardsForPlayer1);
			m_game->GetPlayer2().SetCardsInHand(cardsForPlayer2);
		}
	}


	bool AMode::isCardPlaceable(const Card& card) {
		return card.GetValue() <= 10 && card.GetValue() != 5;  // Cartea "Eter" nu poate fi plasata
	}


	bool AMode::checkWinningCondition() {
		if (m_player1.GetScore() >= 100) {
			std::cout << "Player 1 wins!\n";
			return true;
		}
		if (m_player2.GetScore() >= 100) {
			std::cout << "Player 2 wins!\n";
			return true;
		}
		return false;
	}


	Action AMode::promptPlayerAction() {
		uint8_t key;
		std::cout << "Choose an option:\n";
		std::cout << "1. Place a new card\n";
		std::cout << "2. Activate illusion\n";
		std::cout << "3. Activate explosion\n";
		std::cin >> key;

		if (std::cin.fail() || key < 1 || key > 3) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return Action::Invalid;
		}
		return static_cast<Action>(key);
	}

	//Functii ajutatoare

	//Gestionare plasare carte catre jucatorul curent
	void AMode::handlePlaceCard() {
		Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
		std::cout << currentPlayer.GetName() << " places a card on the board.\n";
		m_game->playTurn();
	}

	//Activeaza iluzia pentru jucatorul al carui rand este
	void AMode::handleActivateIllusion() {
		Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
		std::cout << currentPlayer.GetName() << " activates an illusion.\n";
		Card illusion;
		currentPlayer.useIllusion(m_board, illusion);
	}

	//Activeaza explozia
	void AMode::handleActivateExplosion() {
		Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
		std::cout << currentPlayer.GetName() << " activates an explosion.\n";

		uint8_t x, y;
		std::cout << "Enter X position: "; std::cin >> x;
		std::cout << "Enter Y position: "; std::cin >> y;

		if (m_board.isValidPosition(x, y)) {
			Explosion explosion(3);
			explosion.applyEffects(x, y, m_board);
		}
		else {
			std::cout << "Invalid position!\n";
		}
	}

	//Verifica daca jcoul s-a terminat dupa o mutare respectiva
	void AMode::handleGameOverCheck() {
		uint8_t gameOverStatus = m_game->VerifyGameOver();
		if (gameOverStatus == 1) {
			std::cout << (m_isPlayerTurn ? m_player2.GetName() : m_player1.GetName()) << " wins!\n";
		}
		if (m_board.isBoardFull()) {
			std::cout << "It's a tie!\n";
		}
	}
}
