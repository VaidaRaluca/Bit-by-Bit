module bmode;
using namespace eter;
import <random>;

void BMode::applyModeRules()
{

}

void eter::BMode::assignCardsForPlayers()
{
}

void eter::BMode::generateMage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_mages.size() - 1);

    int index1 = dist(gen);
    int index2 = dist(gen);
    while (index1 == index2) {
        index2 = dist(gen);
    }
     
    m_magePlayer1 = m_mages[index1];
    m_magePlayer2 = m_mages[index2];
    
}
