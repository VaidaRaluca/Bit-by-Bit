export module explosion;
import board;
import <vector>;
import <optional>;
import <stack>;

namespace eter {
	enum class Effect : uint8_t {
		None,
		Eliminate,
		Return,
		Pit
	};

	export class Explosion {
	private:
		std::vector<std::vector<Effect>> EffectsMatrix;
		uint8_t m_SizeEffectsMatrix;

		// Functii ajutatoare noi
		int calculatePosition(int coord, int offset) const;
		void applyEffectAtPosition(Effect effect, int x, int y, Board& grid);
		void eliminateCard(std::optional<std::stack<Card>>& cell);
		void returnCardToPlayer(std::optional<std::stack<Card>>& cell);
		void createPit(std::optional<std::stack<Card>>& cell);
		void assignRandomEffect(int i, int j, int randomNr, int& numEffects, int& numPits);
		char effectToChar(Effect effect) const;

	public:
		Explosion() = default;
		Explosion(int dim);

		void rorate90();
		void applyEffects(uint8_t x, uint8_t y, Board& grid);
		void display() const;
		void generateEffects();
		int GetSize() const;
		void SetSize(uint8_t newSize);
	};
}
