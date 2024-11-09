// mage.cpp
module mage;
import board;
import player;
import<iostream>;
import<stdexcept>;
import<unordered_map>;
import<functional>;
import<optional>;

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

	//cautarea unei carti pe tabla
	std::optional<std::pair<size_t, size_t>> Mage::findCardPosition(const Card& card, Board& board) {
		auto& grid = board.GetGrid();
		for (size_t i = 0; i < board.GetRows(); ++i) {
			for (size_t j = 0; j < board.GetCols(); ++j) {
				const auto& cellOpt = grid[i][j];
				if (cellOpt.has_value()) {
					const auto& stack = cellOpt.value();
					if (!stack.empty() && stack.top() == card) {
						return std::make_pair(i, j);
					}
				}
			}
		}
		return std::nullopt;
	}

	// activeaza abilitatea daca nu a fost deja folosita
	void Mage::activate(Player& player, Player& oponnent, Board& board) {
		if (m_used) {
			throw std::runtime_error("The ability has already been used!");
		}

		static const std::unordered_map<MagicAbility, std::function<void()>> abilityMap = {
			{ MagicAbility::removeOponnentCard, [&]() { removeOponnentCard(player, oponnent, board); } },
			{ MagicAbility::removeEntireRow, [&]() { removeEntireRow(player, board); } },
			{ MagicAbility::coverOponnetCard, [&]() { coverOponnentCard(player, oponnent, board); } },
			{ MagicAbility::createPit, [&]() { createPit(board); } },
			{ MagicAbility::moveOwnStack, [&]() { moveOwnStack(player, board); } },
			{ MagicAbility::extraEterCard, [&]() { addExtraEterCard(player); } },
			{ MagicAbility::moveOponnentStack, [&]() { moveOponnentStack(oponnent, board); } },
			{ MagicAbility::shiftRowToEdge, [&]() { shiftRowToEdge(board); } }
		};

		//Cautarea abilitatii + executarea acesteia
		auto it = abilityMap.find(m_ability);
		if (it != abilityMap.end()) {
			it->second();
		}
		else {
			throw std::invalid_argument("Unknown ability!");
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

		const Card& lastCard = opponentCards.back();
		if (auto position = findCardPosition(lastCard, board); position) {
			auto& [row, col] = position.value();
			auto& stack = board[{row, col}];
			if (stack.has_value() && !stack->empty()) {
				stack->pop();
				std::cout << "The opponent's card has been removed from (" << row << ", " << col << ").\n";
			}
		}
		else {
			std::cout << "The card was not found on the board.\n";
		}
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
		if (auto position = player.findEmptyCell(board); position.first != -1) {
			const Card& card = player.GetCardsInHand().back();
			player.placeCard(position.first, position.second, card, board);
			std::cout << "The opponent's card has been covered.\n";
		}
	}

	//Creeaza o groapa
	void Mage::createPit(Board& board) {
		auto [rows, cols] = std::make_pair(rand() % board.GetRows(), rand() % board.GetCols());
		if (board.isValidPosition(rows, cols)) {
			if (auto& stack = board[{rows, cols}]; stack.has_value()) {
				stack.reset();
				std::cout << "A pit was created at (" << rows << ", " << cols << ").\n";
			}
		}
	}

	//Adaugare carte in plus
	void  Mage::addExtraEterCard(Player& player) {
		player.AddCardToHand({ 1, "eter", true });
		std::cout << "The player received an extra Ether card!\n";
	}

	//Mutare teanc propriu pe alta pozitie
	void  Mage::moveOwnStack(Player& player, Board& board) {
		auto from = player.findEmptyCell(board);
		auto to = player.findEmptyCell(board);
		if (from != to && board.isValidPosition(to.first, to.second)) {
			board[to] = board[from];
			board[from].reset();
			std::cout << "Own stack has been moved from (" << from.first << ", " << from.second
				<< ") to (" << to.first << ", " << to.second << ").\n";
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
			if (auto& stack = board[{board.GetRows() - 1, col}]; stack.has_value()) {
				board[{0, col}] = stack;
				stack.reset();
			}
		}
		std::cout << "The row has been moved to the edge!\n";
	}
}