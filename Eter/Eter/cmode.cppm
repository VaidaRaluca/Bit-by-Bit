export module cmode;
import gamemods;

namespace eter {
	export class CMode : public GameMods {
	private:
		enum class CModeRules {
			//Rules for mode C
		};
	public:
		CMode();
		void applyModeRules();
		~CMode() = default;
	};
}