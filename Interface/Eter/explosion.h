#ifndef EXPLOSION_H
#define EXPLOSION_H
#include"card.h"
#include"board.h"
#include<random>
#include<iostream>
#include<numeric>
#include<algorithm>

namespace eter {

enum class Effect {
    NONE,
    REMOVE_CARD,
    RETURN_CARD,
    CREATE_HOLE
};
class Explosion {
private:
    std::vector<std::vector<Effect>> m_effectMatrix;
    size_t m_size;
    Board m_board;
    Board m_originalBoard; // copie a tablei originale pentru a putea testa pe ea daca efectele sunt acceptate
    std::vector<Card> m_returnedCards;
public:
    Explosion(const size_t& size, Board board);
    const std::vector<Card>& GetReturnedCards();
    void generateRandomEffects();
    void rotateClockwise(); // rotirea matricei de efecte la 90 de grade in sensul acelor de ceasornic
    void rotateCounterClockwise(); // rotirea matricei de efecte la 90 de grade in sens invers acelor de ceasornic
    void printeffectMatrix();
    bool areEffectsAdjacent();
    void verifyEffects();
    void handleApplyEffects();
    Board applyEffects();
    void rotateExplosion();

};
}


#endif // EXPLOSION_H
