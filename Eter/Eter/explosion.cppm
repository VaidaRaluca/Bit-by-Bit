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
        Board m_board;  // copie a tablei originale pentru a putea testa pe ea daca efectele sunt acceptate
        std::vector<Card> m_returnedCards;
    public:
        Explosion(size_t size, Board board);
        void generateRandomEffects();
        void printeffectMatrix();
        bool areEffectsAdjacent();
        void handleApplyEffects();
        Board applyEffects();

    };
}
