module explosion;
using namespace eter;
import <iostream>;
import <vector>;
import <stack>;
import <random>;
import<numeric>;     // pt std::iota 
import<algorithm>;  // pt std::shuffle

Explosion::Explosion(const size_t& size, Board board)
{
    m_size = size;
    m_originalBoard = board;
}

const std::vector<Card>& eter::Explosion::GetReturnedCards()
{
    return m_returnedCards;
}


void Explosion::generateRandomEffects()
{
    int minEffects = (m_size == 3) ? 2 : 3;
    int maxEffects = (m_size == 3) ? 4 : 6;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> effectDist({ 9, 9, 1 }); // Tipuri de efecte (1 = REMOVE_CARD, 2 = RETURN_CARD, 3 = CREATE_HOLE)

    int effectCount = 0;


    do {
        // Inițializăm matricea cu NONE
        m_effectMatrix = std::vector<std::vector<Effect>>(m_size, std::vector<Effect>(m_size, Effect::NONE));
        effectCount = 0;

        // Generăm efectele
        std::vector<size_t> positions(m_size * m_size);
        std::iota(positions.begin(), positions.end(), 0); // populeaza vect cu valori consecutive -> toate pozitiile din matrice (0, ..., size*size-1)
        std::shuffle(positions.begin(), positions.end(), gen); // amesteca valorile din vect

        // Plasăm efectele pe poziții aleatorii
        for (size_t i = 0; i < maxEffects; ++i) {
            if (effectCount >= maxEffects) {
                break;
            }
            size_t pos = positions[i];
            size_t row = pos / m_size;
            size_t col = pos % m_size;
            if (m_effectMatrix[row][col] != Effect::NONE) {
                continue;
            }

            Effect effect = static_cast<Effect>(effectDist(gen) + 1); // Generăm efectul
            m_effectMatrix[row][col] = effect;
            ++effectCount;

        }

    } while (effectCount < minEffects); 


}

void eter::Explosion::rotateClockwise()
{
    size_t n = m_effectMatrix.size();
    std::vector<std::vector<Effect>> rotated(n, std::vector<Effect>(n, Effect::NONE));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = m_effectMatrix[i][j];
        }
    }

    m_effectMatrix = std::move(rotated); 
}

void eter::Explosion::rotateCounterClockwise()
{
    size_t n = m_effectMatrix.size();
    std::vector<std::vector<Effect>> rotated(n, std::vector<Effect>(n, Effect::NONE));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            rotated[n - 1 - j][i] = m_effectMatrix[i][j];
        }
    }

    m_effectMatrix = std::move(rotated);
}

void eter::Explosion::printeffectMatrix()
{
    std::cout << "This is what the explosion card looks like. \n";
    std::cout << " \/ represents CREATE_HOLE. \n";
    std::cout << " X represents REMOVE_CARD. \n";
    std::cout << " R represents RETURN_CARD. \n";
    size_t size = m_effectMatrix.size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
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
    for (size_t line = m_board.GetIndexLineMin();line <= m_board.GetIndexLineMax();++line)
        for (size_t col = m_board.GetIndexColMin();col <= m_board.GetIndexColMax();++col)
        {
            if (m_board.GetGrid()[line][col].has_value() && !m_board.GetGrid()[line][col].value().empty())
                if (m_board.existNonAdjacentCards(line, col) == false)
                    return false;
        }
    return true;
}

void eter::Explosion::verifyEffects()
{
    m_board = m_originalBoard;
    size_t lineMatrixEffect{ 0 };
    size_t colMatrixEffect{ 0 };
    size_t lineBoard{ m_board.GetIndexLineMin() };
    size_t colBoard{ m_board.GetIndexColMin() };
    std::cout << static_cast<int>(lineBoard) << " " << static_cast<int>(colBoard) << " INDECSI \n";
    while (lineMatrixEffect < m_effectMatrix.size() && lineBoard <= m_board.GetIndexLineMax())
    {
        while (colMatrixEffect < m_effectMatrix.size() &&
            colBoard <= m_board.GetIndexColMax())
        {
            auto cellMatrixEffect = m_effectMatrix[lineMatrixEffect][colMatrixEffect];
            auto& cellBoard = m_board.GetGrid()[lineBoard][colBoard];
            std::cout << "Effect applied at (" << lineBoard << ", " << colBoard << "): "
                << static_cast<int>(cellMatrixEffect) << "\n";
            if (cellBoard.has_value() && cellBoard.value().top().GetValue() == 5)
            {
                m_effectMatrix[lineMatrixEffect][colMatrixEffect] = Effect::NONE;
            }
            else
            if (cellMatrixEffect != Effect::NONE) {
                switch (cellMatrixEffect) {
                case Effect::REMOVE_CARD:
                {
                    m_board.removeCard(lineBoard, colBoard);
                    if (areEffectsAdjacent() == false)
                    {
                        m_effectMatrix[lineMatrixEffect][colMatrixEffect] = Effect::NONE;
                        m_board = m_originalBoard;
                    }
                }
                break;

                case Effect::RETURN_CARD:
                {
                    if (cellBoard && !cellBoard->empty()) {
                        Card card = cellBoard->top();
                        m_board.removeCard(lineBoard, colBoard);
                    }
                    if (areEffectsAdjacent() == false)
                    {
                        m_effectMatrix[lineMatrixEffect][colMatrixEffect] = Effect::NONE;
                        m_board = m_originalBoard;
                    }

                    break;
                }
                case Effect::CREATE_HOLE:
                {
                    m_board.createHole(lineBoard, colBoard);
                    if (areEffectsAdjacent() == false)
                    {
                        m_effectMatrix[lineMatrixEffect][colMatrixEffect] = Effect::NONE;
                        m_board = m_originalBoard;
                    }
                    break;
                }
                default:
                    break;
                }
            }
            colBoard++;
            colMatrixEffect++;
        }

        colMatrixEffect = 0;
        colBoard = m_board.GetIndexColMin();

        lineMatrixEffect++;
        lineBoard++;
    }
}

void eter::Explosion::handleApplyEffects()
{
    m_board = m_originalBoard;
    size_t lineMatrixEffect{ 0 };
    size_t colMatrixEffect{ 0 };
    size_t lineBoard{ m_board.GetIndexLineMin() };
    size_t colBoard{ m_board.GetIndexColMin() };
    std::cout << static_cast<int>(lineBoard) << " " << static_cast<int>(colBoard) << " INDECSI \n";
    while (lineMatrixEffect < m_effectMatrix.size() && lineBoard <= m_board.GetIndexLineMax())
    {
        while (colMatrixEffect < m_effectMatrix.size() &&
            colBoard <= m_board.GetIndexColMax())
        {
            auto cellMatrixEffect = m_effectMatrix[lineMatrixEffect][colMatrixEffect];
            auto& cellBoard = m_board.GetGrid()[lineBoard][colBoard];
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
                    m_board.createHole(lineBoard, colBoard);
                    break;
                }
                default:
                    break;
                }
            }
            colBoard++;
            colMatrixEffect++;
        }

        colMatrixEffect = 0;
        colBoard = m_board.GetIndexColMin();

        lineMatrixEffect++;
        lineBoard++;
    }

}

Board eter::Explosion::applyEffects()
{
    verifyEffects();
    std::cout << "Explosion card after verify: \n";
    printeffectMatrix();
    handleApplyEffects();
    m_board.updateAfterRemoval();
    std::cout << m_board;
    std::cout << " Returned cards: \n";
    for (const auto& it : m_returnedCards)
        std::cout << it << "\n";

    return m_board;
}

void eter::Explosion::rotateExplosion()
{
    generateRandomEffects();
    printeffectMatrix();
    std::cout << "Do you want to rotate the explosion card?\n";
    std::cout << "Press l(for left rotation) r (for right rotation) or any key to end rotation.\n";
    char choice;
    std::cin >> choice;
    while (choice == 'l' || choice == 'r')
    {
        if (choice == 'l')
        {
            rotateCounterClockwise();
            printeffectMatrix();
        }
        else
        {
            rotateClockwise();
            printeffectMatrix();
        }
        std::cin >> choice;
    }
}
