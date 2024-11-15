module amode;
import player;
import board;
import explosion;
import <iostream>;
import <string>;


namespace eter {

    AMode::AMode(Player player1, Player player2, const Board& board) : m_player1{ player1 }, m_player2{ player2 }, m_board{ board }, m_player1Wins{ 0 }, m_player2Wins{ 0 }
    {}

    AMode::AMode(Game* game) :
        m_game{ game }
    {}
    void AMode::startMatch()
    {  
        m_isPlayerTurn = true;  // Player 1 starts first
        m_player1Wins = 0;
        m_player2Wins = 0;

        // Initialize the game object
        m_game = std::make_unique<Game>(m_player1, m_player2, m_board, "Mode A");

        // Display the initial setup
        std::cout << "Starting a new match in Mode A!" << std::endl;
        std::cout << "Player 1: " << m_player1.GetName() << " (" << m_player1.GetColor() << ")" << std::endl;
        std::cout << "Player 2: " << m_player2.GetName() << " (" << m_player2.GetColor() << ")" << std::endl;
        std::cout << "Game board: " << std::endl;
        std::cout << m_board << std::endl;

        applyModeRules();

        // Game loop
        while (true)
        {
            std::cout << "Round " << m_game->GetNrRound() << std::endl;

            Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
            std::cout << currentPlayer.GetName() << "'s turn!" << std::endl;

            // Prompt the player for an action
            Action action = promptPlayerAction();
            if (action == Action::Invalid)
            {
                continue;  // Reprompt on invalid input
            }
            Explosion* explosion = nullptr;
            int explosionSize = 0;

            // Hdl player action based on choice
            switch (action) {
            case Action::PlaceCard:
                std::cout << currentPlayer.GetName() << " places a card on the board." << std::endl;
                m_game->playTurn();
                break;
            case Action::ActivateIllusion:
                std::cout << currentPlayer.GetName() << " activates an illusion." << std::endl;
                // Implement illusion activation logic here
                break;
            case Action::ActivateExplosion:
                std::cout << currentPlayer.GetName() << " activates an explosion." << std::endl;

                // Prompt the player for the coordinates to place the explosion
                uint8_t x, y;
                std::cout << "Enter the X position for explosion (0-" << m_board.GetCols() - 1 << "): ";
                std::cin >> x;
                std::cout << "Enter the Y position for explosion (0-" << m_board.GetRows() - 1 << "): ";
                std::cin >> y;

                // Validate the coordinates
                if (!m_board.isValidPosition(x, y)) {
                    std::cout << "Invalid position. Please try again." << std::endl;
                    break; // Exit the case if invalid coordinates are entered
                }

                // Now initialize explosionSize and create Explosion object
                explosionSize = 3;  // You can change this size based on your needs
                explosion = new Explosion(explosionSize); // Initialize Explosion object dynamically

                // Apply explosion effects to the board at the selected position
                std::cout << "Explosion activated at position (" << (int)x << ", " << (int)y << ")." << std::endl;
                explosion->applyEffects(x, y, m_board);  // Apply explosion effects to the board

                break;
            default:
                std::cout << "Unexpected action. Try again." << std::endl;
                continue;
            }

            // Toggle player turn
            m_isPlayerTurn = !m_isPlayerTurn;

            // Check if the game is over
            uint8_t gameOverStatus = m_game->VerifyGameOver();
            if (gameOverStatus != 0) {
                std::cout << "Game Over!" << std::endl;
                if (gameOverStatus == 1) {
                    std::cout << m_player1.GetName() << " wins!" << std::endl;
                    m_player1Wins++;
                }
                else if (gameOverStatus == 2) {
                    std::cout << m_player2.GetName() << " wins!" << std::endl;
                    m_player2Wins++;
                }
                break;
            }

            // Check if the board is full
            if (m_board.isBoardFull()) {
                std::cout << "It's a tie!" << std::endl;
                break;
            }

            // Increment the round number
            m_game->IncrementNrRound();
        }

        // Display the total wins at the end of the match
        std::cout << "Total Wins - Player 1: " << m_player1Wins << ", Player 2: " << m_player2Wins << std::endl;

    
    }

    void AMode::applyModeRules()
    {
        std::cout << "Applying Mode A rules..." << std::endl;

        if (m_board.GetGrid().size() == 3 || m_board.GetGrid().size() == 4) 
        {
            std::cerr << "Valid board size!" << std::endl;
        }
        else 
        {
            std::cerr << "Invalid board size!" << std::endl;
            return;
        }

        std::vector<Player> players = { m_player1, m_player2 };
        for (auto& player : players) 
        {
            for (auto& card : player.GetCardsInHand()) 
            {
                if (isCardPlaceable(card)) {
                    std::cout << "Card " << card.GetValue() << " can be placed." << std::endl;
                }
                else 
                {
                    std::cerr << "Card " << card.GetValue() << " cannot be placed!" << std::endl;
                }
            }
        }

        if (checkWinningCondition())
        {
            std::cout << "We have a winner!" << std::endl;
        }
        else 
        {
            std::cout << "Game continues..." << std::endl;
        }

    }

    void AMode::AssignCardsInHandModeA()
    {
                std::vector<Card>cardsForPlayer1{
   Card(1,"red",true),
   Card(1,"red",true),
   Card(2,"red",true),
   Card(2,"red",true),
   Card(3,"red",true),
   Card(3,"red",true),
   Card(4,"red",true),
   
        };
        std::vector<Card>cardsForPlayer2
        {
        Card(1,"blue",true),
        Card(1,"blue",true),
        Card(2,"blue",true),
        Card(2,"blue",true),
        Card(3,"blue",true),
        Card(3,"blue",true),
        Card(4,"blue",true),
        
         };

        if (m_game)
        {
            m_game->GetPlayer1().SetCardsInHand(cardsForPlayer1);
            m_game->GetPlayer2().SetCardsInHand(cardsForPlayer2);
        }

    }

    bool AMode::isCardPlaceable(const Card& card)
    {
        if (card.GetValue() == 5) {
            std::cout << "Eter card";
            return false;
        }
        return card.GetValue() <= 10;
    }

    bool AMode::checkWinningCondition()
    {
        if (m_player1.GetScore() >= 100) {  // Player 1 wins
            return true;
        }
        if (m_player2.GetScore() >= 100) {  // Player 2 wins
            return true;
        }
        return false;  // No winner yet

    }
    Action AMode::promptPlayerAction()
    {
        uint8_t key;
        std::cout << "Alege o optiune: \n";
        std::cout << "1. Plaseaza o carte pe tabla\n";
        std::cout << "2. Activeaza o iluzie\n";
        std::cout << "3. Activeaza o explozie\n";
         std::cout << "Alege o optiune (1-4): ";
        std::cin >> key;

        if (std::cin.fail() || key < 1 || key > 4) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Optiune invalida. Va rugam sa incercati din nou.\n";
            return Action::Invalid;
        }

        return static_cast<Action>(key);
    }

}
    

	
