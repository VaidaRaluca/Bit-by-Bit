// mage.cpp
module mage;
import board;
import player;
import<stdexcept>;

namespace eter {
	// seteaza abilitatea specificata
	Mage::Mage(MagicAbility ability) : m_ability(ability), m_used(false) {}

	// verifica daca a fost utilizata
	bool Mage::isUsed() {
		return m_used;
	}

	// face return la abilitatea respectiva
	Mage::MagicAbility Mage::GetAbility() const {
		return m_ability;
	}

	// activeaza abilitatea daca nu a fost deja folosita
	void Mage::activate(Player& player, Player& oponnent, Board& board) {
		if (m_used) {
			throw std::runtime_error("The ability has already been used!");
		}

		switch (m_ability) {
		case MagicAbility::removeOponnentCard:
			break;
		case MagicAbility::removeEntireRow:
			break;
		case MagicAbility::coverOponnetCard:
			break;
		case MagicAbility::createPit:
			break;
		case MagicAbility::moveOwnStack:
			break;
		case MagicAbility::extraEterCard:
			break;
		case MagicAbility::moveOponnentStack:
			break;
		case MagicAbility::shiftRowToEdge:
			break;
		default:
			break;
		}
	}

	void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {

	}

	void  Mage::removeEntireRow(Player& player, Board& board) {

	}

	void Mage::coverOponnentCard(Player& player, Player& oponnent, Board& board) {

	}

	void Mage::createPit(Board& board) {

	}

	void  Mage::addExtraEterCard(Player& player) {

	}

	void  Mage::moveOwnStack(Player& player, Board& board) {

	}

	void Mage::moveOponnentStack(Player& oponnent, Board& board) {

	}

	void Mage::shiftRowToEdge(Board& board) {

	}
}