#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include"game.h"
#include"player.h"
#include"amode.h"
#include"bmode.h"
#include"cmode.h"
#include"bcmode.h"

namespace eter {

class GameManager
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

};
}
#endif // GAMEMANAGER_H
