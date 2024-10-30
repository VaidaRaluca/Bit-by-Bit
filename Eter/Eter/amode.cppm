export module amode;
import gamemods;

namespace eter {
	export class AMode: public GameMods {
	private:
		enum class AModeRules {
			// Rules for mode A
		};
	public:
		AMode();
		void applyModeRules(); // override
	};
}