export module explosion;
import board;
#include<vector>
#include<random>
namespace eter 
{
	enum class Effect : uint8_t
	{
		None,
		Eliminate,
		Return,
		Pit
	};
	export class Explosion : public Board
	{
	private:
		std::vector<std::vector<Effect>>EffectsMatrix;//matricea de efecte
		uint8_t m_SizeEffectsMatrix;
		void generateEffects();
	public:
		Explosion() = default;
		Explosion(int dim);
		void rorate90();
		void applyEffects();
		void display()const;
		int GetSize()const;
		void SetSize(uint8_t newSize);
		~Explosion();
	};
}
