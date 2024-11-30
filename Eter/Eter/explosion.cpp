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
 

bool Explosion::IsRowFull(size_t row) const {
    for (size_t col = 0; col < m_board.GetCols(); ++col) {
        if (!m_board[{row, col}].has_value() || m_board[{row, col}]->empty()) {
            return false;
        }
    }
    return true;
}

