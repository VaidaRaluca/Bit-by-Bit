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
    std::cout << "Starting a new match in Mode A!" << std::endl;
    
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
    

	
