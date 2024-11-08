module explosion;
import <iostream>;

using namespace eter;

Explosion::Explosion(int dim) :m_SizeEffectsMatrix(dim), EffectsMatrix(dim, std::vector<Effect>(dim, Effect::None))
{
    generateEffects();
}
void eter::Explosion::rorate90()
{
    std::vector<std::vector<Effect>> rotated(m_SizeEffectsMatrix, std::vector<Effect>(m_SizeEffectsMatrix));
    for (int i = 0; i < m_SizeEffectsMatrix; ++i) {
        for (int j = 0; j < m_SizeEffectsMatrix; ++j) {
            rotated[j][m_SizeEffectsMatrix - 1 - i] = EffectsMatrix[i][j];
        }

    }
}

void eter::Explosion::applyEffects(uint8_t x, uint8_t y,Board &grid)
{ 
    for (int i = 0; i < m_SizeEffectsMatrix; ++i) {
        for (int j = 0; j <m_SizeEffectsMatrix; ++j) {
            int posX = x + i - m_SizeEffectsMatrix / 2; // ajustare fata de centrul exploziei
            int posY = y + j - m_SizeEffectsMatrix / 2;

            if (grid.isValidPosition(posX, posY)) {
                Effect effect = EffectsMatrix[i][j];
                // Aplic efectele în functie de tip
                switch (effect) {
                case Effect::Eliminate:
                    //  pentru eliminarea cartii la poz(posX, posY)
                    break;
                case Effect::Return:
                    //  pentru a întoarce cartea la proprietar la (posX, posY)
                    break;
                case Effect::Pit:
                    //  pentru a crea o groapa la (posX, posY)
                    break;
                case Effect::None:
                    // niciun efect
                    break;
                }
            }
        }
    }


}

void eter::Explosion::display() const
{
    for (const auto& row : EffectsMatrix) {
        for (const auto& effect : row) {
            switch (effect) {
            case Effect::None: std::cout << ". "; break;        // fara efect
            case Effect::Eliminate: std::cout << "E "; break;   // Eliminare
            case Effect::Return: std::cout << "R "; break;      // intoarcere
            case Effect::Pit: std::cout << "P "; break;         // Groapa
            }
        }
        std::cout << std::endl; 
    }
}

int eter::Explosion::GetSize() const
{
    return m_SizeEffectsMatrix;
}

void eter::Explosion::SetSize(uint8_t newSize)
{
    m_SizeEffectsMatrix= newSize;
}

void eter::Explosion::generateEffects()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    int numEffects = (GetSize() == 3) ? rand() % 3 + 2 : rand() % 4 + 3;
    int numPits = numEffects / 10;

    for (int i = 0; i < GetSize(); ++i) {
        for (int j = 0; j < GetSize(); ++j) {
            int randomNr = dist(gen);
            if (numPits > 0 && randomNr < 10) {
                EffectsMatrix[i][j] = Effect::Pit;
                numPits--;
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
            numEffects--;
            if (numEffects <= 0) break;
        }
        if (numEffects <= 0) break;
    }
}

