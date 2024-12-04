module explosion;
using namespace eter;
import <iostream>;
import <vector>;
import <stack>;
import <random>;
import<numeric>;     // pt std::iota 
import<algorithm>;  // pt std::shuffle

    Explosion::Explosion(size_t size, Board board)
    {
        m_size = size;
        m_board = board;
    }


    void Explosion::generateRandomEffects()
    {
        int minEffects = (m_size == 3) ? 2 : 3;
        int maxEffects = (m_size == 3) ? 4 : 6;

  
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, m_size * m_size - 1); // Generam indicii matricei
        std::uniform_int_distribution<> effectDist(1, 3); // Tipuri de efecte (1 = REMOVE_CARD, 2 = RETURN_CARD, 3 = CREATE_HOLE)

        int effectCount = 0;

        
        do {
            // Inițializăm matricea cu NONE
            m_effectMatrix = std::vector<std::vector<Effect>>(m_size, std::vector<Effect>(m_size, Effect::NONE));
            effectCount = 0;

            // Generăm efectele
            std::vector<int> positions(m_size * m_size);
            std::iota(positions.begin(), positions.end(), 0); // populeaza vect cu valori consecutive -> toate pozitiile din matrice (0, ..., size*size-1)
            std::shuffle(positions.begin(), positions.end(), gen); // amesteca valorile din vect

            // Plasăm efectele pe poziții aleatorii
            for (int i = 0; i < maxEffects; ++i) {
                int pos = positions[i];
                int row = pos / m_size;
                int col = pos % m_size;

                Effect effect = static_cast<Effect>(effectDist(gen)); // Generăm efectul
                m_effectMatrix[row][col] = effect;
                ++effectCount;

                // Oprim generarea dacă atingem limita maximă
                if (effectCount >= maxEffects) {
                    break;
                }
            }

        } while (effectCount < minEffects); // Verificăm dacă avem suficiente efecte
   
       
    }

    void eter::Explosion::printeffectMatrix()
    {
        std::cout << "This is what the explosion card looks like. \n";
        std::cout << " \/ represents CREATE_HOLE. \n";
        std::cout << " X represents REMOVE_CARD. \n";
        std::cout << " R represents RETURN_CARD. \n";
        int size = static_cast<int>(m_effectMatrix.size());
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                switch (m_effectMatrix[i][j]) {
                case Effect::CREATE_HOLE:
                    std::cout << "/ ";
                    break;
                case Effect::REMOVE_CARD:
                    std::cout << "X ";
                    break;
                case Effect::RETURN_CARD:
                    std::cout << "R ";
                    break;
                case Effect::NONE:
                    std::cout << "  "; 
                    break;
                default:
                    break;
                }
            }
            std::cout << '\n'; 
        }
    }

    bool eter::Explosion::areEffectsAdjacent()
    {
        for(size_t line =m_board.GetIndexLineMin();line<=m_board.GetIndexLineMax();++line)
            for (size_t col = m_board.GetIndexColMin();col <= m_board.GetIndexColMax();++col)
            {
                if (!m_board.isAdjacentToOccupiedSpace(line, col))
                    return false;
            }
        return true;
    }

    void eter::Explosion::handleApplyEffects()
    {
        size_t lineMatrixEffect{ 0 };
        size_t colMatrixEffect{ 0 };
        size_t lineBoard{m_board.GetIndexLineMin()};
        size_t colBoard{ m_board.GetIndexColMin()};
        std::cout << static_cast<int>(lineBoard) << " " << static_cast<int>(colBoard) << " INDECSI \n";
        while (lineMatrixEffect < m_effectMatrix.size() && lineBoard <= m_board.GetIndexLineMax())
        {
            while (colMatrixEffect < m_effectMatrix.size() &&
                colBoard <= m_board.GetIndexColMax())
            {   
                auto cellMatrixEffect = m_effectMatrix[lineMatrixEffect][colMatrixEffect];
                auto& cellBoard = m_board.GetGrid()[lineBoard] [colBoard];
                std::cout << "Effect applied at (" << lineBoard << ", " << colBoard << "): "
                    << static_cast<int>(cellMatrixEffect) << "\n";

                if (cellMatrixEffect != Effect::NONE) {
                    switch (cellMatrixEffect) {
                    case Effect::REMOVE_CARD:
                        m_board.removeCard(lineBoard, colBoard);
                        break;

                    case Effect::RETURN_CARD:
                        if (cellBoard && !cellBoard->empty()) {
                            Card card = cellBoard->top();
                            m_board.removeCard(lineBoard, colBoard);
                            m_returnedCards.push_back(card);
                        }
                        break;

                    case Effect::CREATE_HOLE:
                    {
                        /*eter::Card card{ '/', "red", 1 };
                        auto& cellBoard2 = m_board[{lineBoard, colBoard}];
                        if (!cellBoard2.has_value()) {
                            std::stack<eter::Card> stack;
                            stack.push(card);
                            m_board[{lineBoard, colBoard}] = stack;
                        }
                        else {
                            auto& stackRef = cellBoard2.value();
                            stackRef.push(card);
                        }*/
                        break;
                    }
                    default:
                        break;
                    }
                }
                colBoard++;
                colMatrixEffect++;
            }
      
            colMatrixEffect=0 ;
            colBoard= m_board.GetIndexColMin();

            lineMatrixEffect++;
            lineBoard++;
        }

    }

    Board eter::Explosion::applyEffects()
    {
        do {
            generateRandomEffects();
            printeffectMatrix();
            handleApplyEffects();

        } while (areEffectsAdjacent());
        std::cout << m_board;
        return m_board;
    }

    