#pragma once
#include <iostream>
#include  <vector>
#include  <stack>
#include  <random>
#include "Card.h"
#include "Board.h"
#include"Player.h"
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
        Board m_originalBoard; 
        std::vector<Card> m_returnedCards;
    public:
        Explosion(const size_t& size, Board board);
        const std::vector<Card>& GetReturnedCards();
        void generateRandomEffects();
        void rotateClockwise(); 
        void rotateCounterClockwise(); 
        void printeffectMatrix();
        bool areEffectsAdjacent();
        void verifyEffects();
        void handleApplyEffects(Player& player1, Player& player2);
        Board applyEffects(Player& player1, Player& player2);
        void rotateExplosion();

    };
}
