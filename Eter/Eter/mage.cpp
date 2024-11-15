//mage.cpp
module mage;
import board;
import player;
import <iostream>;
import <stdexcept>;
import <unordered_map>;
import <functional>;
import <optional>;

namespace eter {
    Mage::Mage(MagicAbility ability) : m_ability(ability), m_used(false) {}

    bool Mage::isUsed() {
        return m_used;
    }

    Mage::MagicAbility Mage::GetAbility() const {
        return m_ability;
    }

    // Gasirea pozi?iei unei carti pe tabla
    std::optional<std::pair<size_t, size_t>> Mage::findCardPosition(const Card& card, Board& board) {
        for (size_t i = 0; i < board.GetRows(); ++i) {
            for (size_t j = 0; j < board.GetCols(); ++j) {
                if (auto& cellOpt = board[{i, j}]; cellOpt.has_value() && !cellOpt->empty()) {
                    if (cellOpt->top() == card) {
                        return std::make_pair(i, j);
                    }
                }
            }
        }
        return std::nullopt;
    }

    // Eliminare carte dintr-o celula a tablei
    void Mage::removeCardFromBoard(std::optional<std::stack<Card>>& stack) {
        if (stack.has_value() && !stack->empty()) {
            stack->pop();
            std::cout << "Card removed.\n";
        }
    }

    // Mutare teanc intre doua pozitii
    void Mage::moveStack(const std::pair<int, int>& from, const std::pair<int, int>& to, Board& board) {
        if (from != to && board.isValidPosition(to.first, to.second)) {
            board[to] = board[from];
            board[from].reset();
            std::cout << "Stack moved from (" << from.first << ", " << from.second << ") to (" << to.first << ", " << to.second << ").\n";
        }
    }

    // Activare abilitate
    void Mage::activate(Player& player, Player& oponnent, Board& board) {
        if (m_used) {
            throw std::runtime_error("The ability has already been used!");
        }

        static const std::unordered_map<MagicAbility, std::function<void()>> abilityMap = {
            { MagicAbility::removeOponnentCard, [&]() { removeOponnentCard(player, oponnent, board); } },
            { MagicAbility::removeEntireRow,    [&]() { removeEntireRow(player, board); } },
            { MagicAbility::coverOponnetCard,   [&]() { coverOponnentCard(player, oponnent, board); } },
            { MagicAbility::createPit,          [&]() { createPit(board); } },
            { MagicAbility::moveOwnStack,       [&]() { moveOwnStack(player, board); } },
            { MagicAbility::extraEterCard,      [&]() { addExtraEterCard(player); } },
            { MagicAbility::moveOponnentStack,  [&]() { moveOponnentStack(oponnent, board); } },
            { MagicAbility::shiftRowToEdge,     [&]() { shiftRowToEdge(board); } }
        };

        if (auto it = abilityMap.find(m_ability); it != abilityMap.end()) {
            it->second();
        }
        else {
            throw std::invalid_argument("Unknown ability!");
        }

        m_used = true;
    }

    // Eliminare carte a oponentului
    void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {
        if (oponnent.GetPlayedCards().empty()) {
            std::cout << "Opponent has no cards played.\n";
            return;
        }

        const Card& lastCard = oponnent.GetPlayedCards().back();
        if (auto position = findCardPosition(lastCard, board); position) {
            auto& [row, col] = *position;
            removeCardFromBoard(board[{row, col}]);
            std::cout << "Removed opponent's card from (" << row << ", " << col << ").\n";
        }
        else {
            std::cout << "Card not found on the board.\n";
        }
    }

    // Eliminare rand intreg
    void Mage::removeEntireRow(Player& player, Board& board) {
        for (size_t col = 0; col < board.GetCols(); ++col) {
            removeCardFromBoard(board[{0, col}]);
        }
        std::cout << "Entire row has been removed!\n";
    }

    // Acoperire carte adversar
    void Mage::coverOponnentCard(Player& player, Player& oponnent, Board& board) {
        if (auto position = player.findEmptyCell(board); position != std::make_pair(255, 255)) {
            const Card& card = player.GetCardsInHand().back();
            player.placeCard(position.first, position.second, card, board);
            std::cout << "Opponent's card has been covered.\n";
        }
    }

    // Creare groapa
    void Mage::createPit(Board& board) {
        int row = rand() % board.GetRows();
        int col = rand() % board.GetCols();
        if (board.isValidPosition(row, col)) {
            board[{row, col}].reset();
            std::cout << "Pit created at (" << row << ", " << col << ").\n";
        }
    }

    // Adaugare carte Eter
    void Mage::addExtraEterCard(Player& player) {
        player.AddCardToHand({ 1, "eter", true });
        std::cout << "Extra Ether card added to player's hand.\n";
    }

    // Mutare teanc propriu
    void Mage::moveOwnStack(Player& player, Board& board) {
        auto from = player.findEmptyCell(board);
        auto to = player.findEmptyCell(board);
        moveStack(from, to, board);
    }

    // Mutare teanc adversar
    void Mage::moveOponnentStack(Player& oponnent, Board& board) {
        auto from = oponnent.findEmptyCell(board);
        auto to = oponnent.findEmptyCell(board);
        moveStack(from, to, board);
    }

    // Mutare rand la marginea tablei
    void Mage::shiftRowToEdge(Board& board) {
        for (size_t col = 0; col < board.GetCols(); ++col) {
            if (auto& stack = board[{board.GetRows() - 1, col}]; stack.has_value()) {
                board[{0, col}] = stack;
                stack.reset();
            }
        }
        std::cout << "Row moved to the edge.\n";
    }
}
