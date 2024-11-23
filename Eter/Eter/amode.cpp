module amode;
import player;
import board;
import explosion;
import <iostream>;
import <string>;
import <vector>;


namespace eter {
    
    AMode::AMode(Game* game) : m_game{ game } {}

	void AMode::assignCardsInHandModeA()
	{

        std::vector<Card>cardsForPlayer1A{
        Card(1,"red",true),
        Card(1,"red",true),
        Card(2,"red",true),
        Card(2,"red",true),
        Card(3,"red",true),
        Card(3,"red",true),
        Card(4,"red",true),
         };
        std::vector<Card>cardsForPlayer2A{
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
            m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1A);
            m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2A);
        }
	}

    void AMode::startMatchModeA()
    {
        size_t countRound = 1;
        std::cout << "The game in A mode has started \n";
        while (m_game->GetPlayer2Wins() < knrRoundsForWin && m_game->GetPlayer1Wins() < knrRoundsForWin)
        {
            std::cout << "Round " << countRound << " of 3 \n";
            startRoundModeA();
            countRound++;
            std::cout << "The round has ended. \n";
            std::cout << "Wins player 1: " << static_cast<int>(m_game->GetPlayer1Wins()) << "\n";
            std::cout << "Wins player 2: " << static_cast<int>(m_game->GetPlayer2Wins()) << "\n";

            // Reset the board and reassign cards
            m_game->resetBoard();
            m_game->ReassignCardsToPlayers();
        }
        std::cout << "GAME OVER \n";
    }
    void AMode::handleActivateIllusionModeA()
    {
        Player& currentPlayer = m_isPlayerTurn ? m_player1 : m_player2;
        std::cout << currentPlayer.GetName() << " activates an illusion.\n";
        Card illusion;
      //  currentPlayer.useIllusion(m_board, illusion);

    }

    void AMode::handleActivateExplosionModeA()
    {
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

    void AMode::handleOptionModeA()
    {
        enum  Option
        {
            OPTION_1 = 1,
            OPTION_2,
            OPTION_3,
         };

        std::cout << m_game->GetBoard();


        if (m_game->GetIsPlayerTurn())
            std::cout << "It's " << m_game->GetPlayer1().GetName() << "'s turn\n";
        else
            std::cout << "It's " << m_game->GetPlayer2().GetName() << "'s turn\n";

        int key;
        std::cout << "Choose an option: \n";
        std::cout << "Press 1 to place a card on the board \n";
        std::cout << "Press 2 to activate an illusion \n";
        std::cout << "Press 3 to activate an explosion \n";
         std::cin >> key;
        Option option = static_cast<Option>(key);

        switch (option) {
        case OPTION_1:
            m_game->playTurn();
            break;
        case OPTION_2:
            handleActivateIllusionModeA();
            break;
        case OPTION_3:
            handleActivateExplosionModeA();
            break;
        default:
            std::cout << "Invalid option.\n";
            break;
        }
    }

    void AMode::startRoundModeA()
    {
        char gameStatus = '0';
        while (gameStatus == '0')
        {
            handleOptionModeA();
            gameStatus = m_game->VerifyGameOver();
            std::cout << "Game status: " << gameStatus << "\n";
        }
        std::cout << gameStatus << "\n";
        if (gameStatus == '2' || gameStatus == '3')
        {
            std::string choice;
            std::cout << "Do you want to continue the game with a single move? (YES or NO) \n";
            std::cin >> choice;
            if (choice == "YES")
                handleOptionModeA();

            if (m_game->GetPlayer1().GetColor() == m_game->GetBoard().findWinnerByScore())
                std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this round!" << std::endl;
            else
                if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().findWinnerByScore())
                    std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this round!" << std::endl;
                else
                    std::cout << "DRAW \n";
        }
        std::cout << m_game->GetBoard();
    }

    void AMode::applyModeRulesModeA()
    {
        assignCardsInHandModeA();
        startMatchModeA();


    }
 
}
