module explosion;
import <iostream>;
import <random>;
import <vector>;

using namespace eter;

Explosion::Explosion(int dim)
    : m_SizeEffectsMatrix(dim), EffectsMatrix(dim, std::vector<Effect>(dim, Effect::None))
{
    generateEffects();
}

// Functie pentru rotirea matricei cu 90 de grade
void eter::Explosion::rorate90() {
    std::vector<std::vector<Effect>> rotated(m_SizeEffectsMatrix, std::vector<Effect>(m_SizeEffectsMatrix));

    for (int i = 0; i < m_SizeEffectsMatrix; ++i) {
        for (int j = 0; j < m_SizeEffectsMatrix; ++j) {
            rotated[j][m_SizeEffectsMatrix - 1 - i] = EffectsMatrix[i][j];
        }
    }
    EffectsMatrix = std::move(rotated); // Actualizeaz? matricea originala
}

// Functie principala pentru aplicarea efectelor incepand de la pozi?ia (x, y)
void eter::Explosion::applyEffects(uint8_t x, uint8_t y, Board& grid) {
    for (int i = 0; i < m_SizeEffectsMatrix; ++i) {
        for (int j = 0; j < m_SizeEffectsMatrix; ++j) {
            int posX = calculatePosition(x, i);
            int posY = calculatePosition(y, j);

            if (grid.isValidPosition(posX, posY)) {
                applyEffectAtPosition(EffectsMatrix[i][j], posX, posY, grid);
            }
        }
    }
}

// Calculeaza pozi?ia ajustata in functie de centrul exploziei
int eter::Explosion::calculatePosition(int coord, int offset) const {
    return coord + offset - m_SizeEffectsMatrix / 2;
}

// Aplic? efectul specific la pozi?ia (x, y) pe tabla
void eter::Explosion::applyEffectAtPosition(Effect effect, int x, int y, Board& grid) {
    auto& cell = grid[{x, y}];
    switch (effect) {
    case Effect::Eliminate:
        eliminateCard(cell);
        break;
    case Effect::Return:
        returnCardToPlayer(cell);
        break;
    case Effect::Pit:
        createPit(cell);
        break;
    case Effect::None:
        break;
    }
}

// Elimin? cartea din stiva daca exista
void eter::Explosion::eliminateCard(std::optional<std::stack<Card>>& cell) {
    if (cell.has_value() && !cell->empty()) {
        cell->pop();
        std::cout << "Card eliminated.\n";
    }
}

// Intoarce cartea 
void eter::Explosion::returnCardToPlayer(std::optional<std::stack<Card>>& cell) {
    if (cell.has_value() && !cell->empty()) {
        cell.reset();
        std::cout << "Card returned to player.\n";
    }
}

// Creeaza o groapa la pozitia data
void eter::Explosion::createPit(std::optional<std::stack<Card>>& cell) {
    if (cell.has_value()) {
        cell.reset();
        std::cout << "Pit created.\n";
    }
}

// Afiseaza matricea de efecte pentru debug
void eter::Explosion::display() const {
    for (const auto& row : EffectsMatrix) {
        for (const auto& effect : row) {
            std::cout << effectToChar(effect) << " ";
        }
        std::cout << '\n';
    }
}

// Conversie efect in caracter pentru afisare
char eter::Explosion::effectToChar(Effect effect) const {
    switch (effect) {
    case Effect::None: return '.';
    case Effect::Eliminate: return 'E';
    case Effect::Return: return 'R';
    case Effect::Pit: return 'P';
    default: return '?';
    }
}

// Genereaza efectele aleatorii in matrice
void eter::Explosion::generateEffects() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    int numEffects = (GetSize() == 3) ? rand() % 3 + 2 : rand() % 4 + 3;
    int numPits = numEffects / 10;

    for (int i = 0; i < GetSize() && numEffects > 0; ++i) {
        for (int j = 0; j < GetSize() && numEffects > 0; ++j) {
            assignRandomEffect(i, j, dist(gen), numEffects, numPits);
        }
    }
}

// Atribuie un efect aleatoriu unei celule
void eter::Explosion::assignRandomEffect(int i, int j, int randomNr, int& numEffects, int& numPits) {
    if (numPits > 0 && randomNr < 10) {
        EffectsMatrix[i][j] = Effect::Pit;
        --numPits;
    }
    else if (randomNr < 50) {
        EffectsMatrix[i][j] = Effect::Eliminate;
    }
    else if (randomNr < 100) {
        EffectsMatrix[i][j] = Effect::Return;
    }
    else {
        EffectsMatrix[i][j] = Effect::None;
    }
    --numEffects;
}

// Obtine dimensiunea matricei de efecte
int eter::Explosion::GetSize() const {
    return m_SizeEffectsMatrix;
}

void eter::Explosion::SetSize(uint8_t newSize) {
    m_SizeEffectsMatrix = newSize;
}
