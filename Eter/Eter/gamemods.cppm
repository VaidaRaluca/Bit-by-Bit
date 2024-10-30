export module gamemods;
import <string>;
namespace eter {
	export class GameMods {
	private:
		std::string m_modeName;
		enum class rulesList {
			// listing all rules (common+uncommon)
		};
	public:
		void applyModeRules(); //implementation in each game mode
	};
}