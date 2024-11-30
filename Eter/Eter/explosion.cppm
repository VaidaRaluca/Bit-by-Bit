export module explosion;

import board;
import <vector>;
import <utility>;
import <optional>;
import <stdexcept>;

namespace eter {

    enum class ExplosionEffect {
        RemoveCard,
        ReturnCard,
        CreatePit
    };

    class Explosion {
    private:
        bool m_hasBeenActivated;  // O singură explozie per joc
        Board& m_board;           // Referință către tablă
        uint8_t m_radius;
        std::vector<std::vector<ExplosionEffect>> m_effectMap;  // Harta efectelor exploziei
    public:
        Explosion(uint8_t radius, Board& board);
        void RotateEffectMap();  // Rotește harta cu 90°
       
    private:
        bool IsRowFull(size_t row) const;  // Verifică dacă un rând e complet
    };



}