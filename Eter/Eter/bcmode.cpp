#include "BCMode.h"
using namespace eter;
#include <random>
#include "AMode.h"
uint8_t eter::BCMode::GetRoundsForWin() const
{
    return 3;
}

uint8_t eter::BCMode::GetRounds() const
{
    return 5;
}

BCMode::BCMode(Game* game): AMode(game){}

void eter::BCMode::assignCardsInHand()
{
	BMode::assignCardsInHand();
}

void eter::BCMode::generateMageAndPower()
{
	BMode::generateMage();
	CMode::generatePower();
}

void eter::BCMode::startMatch()
{
	BMode::startMatch();
}

void eter::BCMode::startRound()
{
	BMode::startRound();
}

void eter::BCMode::handleOption()
{
    enum  Option
    {
        OPTION_1 = 1,
        OPTION_2,
        OPTION_3,
        OPTION_4
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
    std::cout << "Press 3 to activate your mage \n";
    std::cout << "Press 4 to activate the elemental power \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        //activare iluzie
        m_game->playIllusion();
        break;
    case OPTION_3:
        if (m_game->GetIsPlayerTurn())
        {
            GetMageForPlayer1().activate(m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
            m_game->SetIsPlayerTurn();
        }
        else
        {
            GetMageForPlayer2().activate(m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
            m_game->SetIsPlayerTurn();
        }
        break;
    case OPTION_4: {
        // Selectarea unei puteri elementale
        std::cout << "Select an elemental power:\n";
        int abilityIndex = 0;
        for (int i = 0; i <= static_cast<int>(eter::elementalPowerCards::powerAbility::rock); ++i) {
            std::cout << i << " - " << static_cast<eter::elementalPowerCards::powerAbility>(i) << "\n";
        }
        std::cin >> abilityIndex;

        if (abilityIndex < 0 || abilityIndex > static_cast<int>(eter::elementalPowerCards::powerAbility::rock)) {
            std::cout << "Invalid ability selection.\n";
            break;
        }

        eter::elementalPowerCards::powerAbility selectedAbility =
            static_cast<eter::elementalPowerCards::powerAbility>(abilityIndex);

        eter::elementalPowerCards elementalPower(selectedAbility);

        // Verific?m dac? puterea a fost utilizat?
        if (elementalPower.GetUsed()) {
            std::cout << "This power has already been used.\n";
        }
        else {
            if (m_game->GetIsPlayerTurn()) {
                elementalPower.activate(m_game,m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
            }
            else {
                elementalPower.activate(m_game,m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
            }
            elementalPower.SetUsed(true);
            std::cout << "Power activated successfully!\n";
        }
        break;
    }
    default:
        std::cout << "Invalid option.\n";
        break;
    }

}

void eter::BCMode::applyModeRules()
{
    m_game->GetBoardRef().SetDimMax(4);
    generateMageAndPower();
    BMode::applyModeRules();
}
