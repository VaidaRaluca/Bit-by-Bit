export module gamemods;
import <string>;
namespace eter {
	export class GameMods {
	private:
		std::string m_modeName;
		
	public:
		void applyModeRules(); //implementation in each game mode
	};
}