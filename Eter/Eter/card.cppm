#include<cstdint>
export module card;
import cardtype;
import <variant>;
import <vector>;
import <string>;
namespace eter {
	export class Card {
	public:
		// Unde retinem valoarea cartii (1-4) ??
		CardType m_type;
		std::string m_color;
		bool m_position; //true = fata in sus
		bool m_isEter;   //true = este carte eter
		Card() = default;
		Card(CardType type, const std::string& color, bool position,bool isEter);

		CardType GetType();  
		std::string GetColor();
		bool GetPosition();
		bool GetIsEter();

		void SetType(CardType type);
		void SetColor(std::string color);
		void SetPosition(bool positon);
		void SetIsEter(bool isEter);


		~Card() = default;
	};

};