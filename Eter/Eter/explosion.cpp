module explosion;
import <iostream>;
import <random>;
import <vector>;

using namespace eter;


Explosion::Explosion(uint8_t radius, Board& board) : m_radius(radius), m_hasBeenActivated(false), m_board(board) {
    m_effectMap = {
        {ExplosionEffect::RemoveCard, ExplosionEffect::CreatePit, ExplosionEffect::ReturnCard},
        {ExplosionEffect::ReturnCard, ExplosionEffect::RemoveCard, ExplosionEffect::CreatePit},
        {ExplosionEffect::CreatePit, ExplosionEffect::ReturnCard, ExplosionEffect::RemoveCard}
    };
}

void Explosion::RotateEffectMap() {
    size_t n = m_effectMap.size();
    std::vector<std::vector<ExplosionEffect>> rotated(n, std::vector<ExplosionEffect>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = m_effectMap[i][j];
        }
    }
    m_effectMap = std::move(rotated);
}

bool eter::Explosion::CanActivateExplosion() const
{
    if (m_hasBeenActivated) {
        return false;
    }

    size_t fullRows = 0;
    for (size_t row = 0; row < m_board.GetRows(); ++row) {
        if (IsRowFull(row)) {
            ++fullRows;
        }
        if (fullRows >= 2) {
            return true;
        }
    }
    return false;
}

void eter::Explosion::ApplyExplosion(size_t x, size_t y)
{
    void ApplyExplosion(size_t x, size_t y);
}

void eter::Explosion::ApplyEffect(size_t x, size_t y, ExplosionEffect effect)
{
    if (!CanActivateExplosion()) {
        std::cerr << "Explosion cannot be activated: conditions not met or already activated.\n";
        return;
    }

    m_hasBeenActivated = true;
    auto grid = m_board.GetGrid();

    // Aplica efectele pe baza m_effectMap
    for (size_t i = 0; i < m_effectMap.size(); ++i) {
        for (size_t j = 0; j < m_effectMap[i].size(); ++j) {
            size_t boardX = i + m_board.GetDimMax() / 2 - m_effectMap.size() / 2;
            size_t boardY = j + m_board.GetDimMax() / 2 - m_effectMap[0].size() / 2;

            if (boardX < m_board.GetRows() && boardY < m_board.GetCols()) {
                ApplyEffect(boardX, boardY, m_effectMap[i][j]);
            }
        }
    }

    // Afectează pozițiile din jurul (x, y) în funcție de raza exploziei
    for (int dx = -m_radius; dx <= m_radius; ++dx) {
        for (int dy = -m_radius; dy <= m_radius; ++dy) {
            size_t nx = x + dx, ny = y + dy;
            if (m_board.isValidPosition(nx, ny)) {
                ApplyEffect(nx, ny, ExplosionEffect::RemoveCard);  // De exemplu, elimină cartea
                std::cout << "Explosion cleared at (" << nx << ", " << ny << ").\n";
            }
        }
    }

    std::cout << "Explosion applied successfully!\n";
}
 

bool Explosion::IsRowFull(size_t row) const {
    for (size_t col = 0; col < m_board.GetCols(); ++col) {
        if (!m_board[{row, col}].has_value() || m_board[{row, col}]->empty()) {
            return false;
        }
    }
    return true;
}

