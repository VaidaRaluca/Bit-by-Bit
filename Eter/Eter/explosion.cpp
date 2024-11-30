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
 

bool Explosion::IsRowFull(size_t row) const {
    for (size_t col = 0; col < m_board.GetCols(); ++col) {
        if (!m_board[{row, col}].has_value() || m_board[{row, col}]->empty()) {
            return false;
        }
    }
    return true;
}

