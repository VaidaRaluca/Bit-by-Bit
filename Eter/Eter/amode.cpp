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
    
}
    

	
