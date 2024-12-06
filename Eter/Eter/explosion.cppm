export module explosion;
import <iostream>;
import <vector>;
import <stack>;
import <random>;
import card;
import board;
namespace eter {

    enum class Effect {
        NONE,
        REMOVE_CARD,
        RETURN_CARD,
        CREATE_HOLE
    };
    export class Explosion {
    private:
        std::vector<std::vector<Effect>> m_effectMatrix;
        size_t m_size;
        Board m_board; 
        Board m_originalBoard; // copie a tablei originale pentru a putea testa pe ea daca efectele sunt acceptate
        std::vector<Card> m_returnedCards;
    public:
        Explosion(size_t size, Board board);
        void generateRandomEffects();
        void rotateClockwise(); // rotirea matricei de efecte la 90 de grade in sensul acelor de ceasornic
        void rotateCounterClockwise(); // rotirea matricei de efecte la 90 de grade in sens invers acelor de ceasornic
        void printeffectMatrix();
        bool areEffectsAdjacent();
        void verifyEffects();
        void handleApplyEffects();
        Board applyEffects();

    };
}
