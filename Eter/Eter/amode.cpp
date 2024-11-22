module amode;
import player;
import board;
import explosion;
import <iostream>;
import <string>;


namespace eter {
	 
	AMode::AMode(Game* game) : m_game{ game } {}

	void AMode::assignCardsInHandModeA()
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
        std::vector<Card>cardsForPlayer2{
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
            m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1);
            m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2);
        }
	}

    void AMode::startMatchModeA()
    {
        std::cout << "Am inceput in moduk A";
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
            //activare iluzie
            break;
        case OPTION_3:
            //activare explozie
            break;
        default:
            std::cout << "Invalid option.\n";
            break;
        }
    }
 
}
