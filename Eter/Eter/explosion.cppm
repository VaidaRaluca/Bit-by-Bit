export module explosion;
import <iostream>;
import <vector>;
import <optional>;
import <stack>;
import <random>;
import card;
namespace eter {

    enum class Effect {
        REMOVE_CARD,
        //FLIP_CARD,
        CREATE_HOLE
    };
    export class Explosion {
    private:
        std::vector<std::vector<Effect>> m_effectMatrix;

    public:
        Explosion(int size);
        void generateRandomEffects(int size);
        bool areEffectsAdjacent(int size);
        void applyEffects( std::vector<std::vector<std::optional<std::stack<Card>>>>& board);




    };
}
