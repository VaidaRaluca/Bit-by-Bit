// mage.cpp
module mage;
import board;
import player;
import<iostream>;
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
		m_used = true;
	}

	//Eliminare carte a oponentului
	void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {
		const auto& opponentCards = oponnent.GetPlayedCards();
		if (opponentCards.empty()) {
			std::cout << "Opponent has no cards played.\n";
			return;
		}

		Card lastCard = opponentCards.back();
		auto& grid = board.GetGrid();

		for (size_t i = 0; i < board.GetRows(); ++i) {
			for (size_t j = 0; j < board.GetCols(); ++j) {
				const auto& stackOpt = grid[i][j];
				if (stackOpt.has_value()) {
					auto& stack = const_cast<std::stack<Card>&>(stackOpt.value());
					if (stack.empty() && stack.top() == lastCard) {
						stack.pop();
						std::cout << "The opponent's card has been removed!\n";
						return;
					}
				}
			}
		}
		std::cout << "The book was not found on the board.\n";
	}

	//Eliminare rand intreg
	void  Mage::removeEntireRow(Player& player, Board& board) {
		for (size_t col = 0; col < board.GetCols(); ++col) {
			auto stack = board[{0, col}];
			if (stack.has_value()) {
				stack->pop();
			}
		}
		std::cout << "The row has been removed!\n";
	}

	//Acoperire carte a opnentului cu cartea proprie
	void Mage::coverOponnentCard(Player& player, Player& oponnent, Board& board) {
		auto position = player.findEmptyCell(board);
		if (position.first != -1 && position.second != -1) {
			Card card = player.GetCardsInHand().back();
			player.placeCard(position.first, position.second, card, board);
		}
		std::cout << "The opponent's card has been covered.\n";
	}

	//Creeaza o groapa
	void Mage::createPit(Board& board) {
		auto position = std::make_pair(rand() % board.GetRows(), rand() % board.GetCols());
		if (board.isValidPosition(position.first, position.second)) {
			auto& stack = board[position];
			if (stack.has_value()) {
				stack.reset();
				std::cout << "A pit was created at (" << position.first << ", " << position.second << ").\n";
			}
		}
	}

	//Adaugare carte in plus
	void  Mage::addExtraEterCard(Player& player) {
		Card eterCard{ 1, "eter", true };
		player.SetCardsInHand({ eterCard });
		std::cout << "The player received an extra Ether card! \n";
	}

	//Mutare teanc propriu pe alta pozitie
	void  Mage::moveOwnStack(Player& player, Board& board) {
		auto from = player.findEmptyCell(board);
		auto to = player.findEmptyCell(board);
		if (from != to && board.isValidPosition(to.first, to.second)) {
			board[to] = board[from];
			board[from].reset();
			std::cout << "Own stack has been moved from (" << from.first << ", " << from.second
				<<") to (" << to.first << ", " << to.second << ").\n";
		}
	}

	//Mutare teanc detinut de oponent
	void Mage::moveOponnentStack(Player& oponnent, Board& board) {
		auto from = oponnent.findEmptyCell(board);
		auto to = oponnent.findEmptyCell(board);
		if (from != to && board.isValidPosition(to.first, to.second)) {
			board[to] = board[from];
			board[from].reset();
			std::cout << "The opponent's stack has been moved.\n";
		}
	}

	//Mutare rand la marginea tablei
	void Mage::shiftRowToEdge(Board& board) {
		for (size_t col = 0; col < board.GetCols(); ++col) {
			auto& stack = board[{board.GetRows() - 1, col}];
			if (stack.has_value()) {
				board[{0, col}] = stack;
				stack.reset();
			}
		}
		std::cout << "The row has been moved to the edge!\n";
	}
}