module cmode;
using namespace eter;
import player;
import <random>;

void CMode::applyModeRules()
{
    generatePower();
}
void eter::CMode::generatePower()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_power.size() - 1);

    int indexPower1Player1 = dist(gen);
    int indexPower2Player1;
    do {
        indexPower2Player1 = dist(gen);
    } while (indexPower2Player1 == indexPower1Player1);

    int indexPower1Player2;
    int indexPower2Player2;
    do {
        indexPower1Player2 = dist(gen);
    } while (indexPower1Player2 == indexPower1Player1 || indexPower1Player2 == indexPower2Player1);

    do {
        indexPower2Player2 = dist(gen);
    } while (indexPower2Player2 == indexPower1Player2 || indexPower2Player2 == indexPower1Player1 || indexPower2Player2 == indexPower2Player1);

    m_power1Player1 = m_power[indexPower1Player1];
    m_power2Player1 = m_power[indexPower2Player1];
    m_power1Player2 = m_power[indexPower1Player2];
    m_power2Player2 = m_power[indexPower2Player2];
}