export module amode;
import gamemods;

namespace eter {
	export class AMode: public GameMods {
	private:
		enum class AModeRules {
			
		};
	public:
		AMode();
		void applyModeRules(); // override
	};
}