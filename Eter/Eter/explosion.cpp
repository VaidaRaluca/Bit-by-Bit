module explosion;
import <iostream>;
import <vector>;
import <optional>;
import <stack>;
import <random>;
import std;
namespace eter {
    Explosion::Explosion(int size) 
    {
        m_effectMatrix.resize(size, std::vector<Effect>(size, Effect::REMOVE_CARD)); //  efecte default
        generateRandomEffects(size);
    }
    void Explosion::generateRandomEffects(int size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 9);   
        int maxEffects = (size == 3) ? 4 : 6; 
        int effectCount = 0;
        while (effectCount < 2 || (size == 3 && effectCount > 4) || (size == 4 && effectCount < 3)) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    int randEffect = dist(gen);
                    if (randEffect < 3 && m_effectMatrix[i][j] == Effect::REMOVE_CARD) {
                        m_effectMatrix[i][j] = Effect::REMOVE_CARD;
                        ++effectCount;
                    }
                    /*else if (randEffect < 7 && m_effectMatrix[i][j] == Effect::REMOVE_CARD) {
                        m_effectMatrix[i][j] = Effect::FLIP_CARD;
                        ++effectCount;
                    }*/
                    else if (randEffect < 9 && m_effectMatrix[i][j] == Effect::REMOVE_CARD) {
                        m_effectMatrix[i][j] = Effect::CREATE_HOLE;
                        ++effectCount;
                    }
                }
            }
        }

         if (!areEffectsAdjacent(size)) {
             std::fill(m_effectMatrix.begin(), m_effectMatrix.end(), std::vector<Effect>(size, Effect::REMOVE_CARD));
            generateRandomEffects(size);  // Refacem aleator
        }
    }

    bool Explosion::areEffectsAdjacent(int size)
    {
        std::set<std::pair<int, int>> affectedPositions;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (m_effectMatrix[i][j] != Effect::REMOVE_CARD) {
                    affectedPositions.insert({ i, j });
                }
            }
        }

        if (affectedPositions.size() < 2) {
            return true; 
        }

         for (const auto& pos : affectedPositions) {
            int x = pos.first;
            int y = pos.second;
            bool isAdjacent = false;
            for (const auto& adj : affectedPositions) {
                if (adj != pos && (std::abs(x - adj.first) <= 1 && std::abs(y - adj.second) <= 1)) {
                    isAdjacent = true;
                    break;
                }
            }
            if (!isAdjacent) {
                return false; //  ignor efectul
            }
        }
        return true;
    }

    void Explosion::applyEffects(std::vector<std::vector<std::optional<std::stack<Card>>>>& board)
    {
        for (size_t i = 0; i < m_effectMatrix.size(); ++i) {
            for (size_t j = 0; j < m_effectMatrix[i].size(); ++j) {
                 if (board[i][j] && !board[i][j]->empty()) {
                    switch (m_effectMatrix[i][j]) {
                    case Effect::REMOVE_CARD:
                        board[i][j]->pop();  // Elimina ultima carte de pe pozitie
                        std::cout << "Removed card at (" << i << ", " << j << ")\n";
                        break;
                        //case Effect::FLIP_CARD:
                        //    board[i][j]->top().flip();  
                        //    std::cout << "Flipped card at (" << i << ", " << j << ")\n";
                        //    break;
                    case Effect::CREATE_HOLE:
                        board[i][j].reset();  // Creeaza o groapa 
                        std::cout << "Created a hole at (" << i << ", " << j << ")\n";
                        break;
                    }
                }
                else {
                    std::cout << "Positia (" << i << ", " << j << ") nu contine o carte.\n";
                }
            }
        }
    }
}
