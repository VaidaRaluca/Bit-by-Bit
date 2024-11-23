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

    //Constructor de copiere
    Mage::Mage(const Mage& other)
        : m_ability(other.m_ability), m_used(other.m_used) {
        std::cout << "Mage copied.\n";
    }

    //Operator de atribuire prin copiere
    Mage& Mage::operator=(const Mage& other) {
        if (this != &other) {
            m_ability = other.m_ability;
            m_used = other.m_used;
        }
        std::cout << "Mage assigned via copy.\n";
        return *this;
    }

    // Constructor de mutare
    Mage::Mage(Mage&& other) noexcept
        : m_ability(std::move(other.m_ability)), m_used(other.m_used) {
        other.m_used = false; // Resetez starea obiectului mutat
        std::cout << "Mage moved.\n";
    }

    // Operator de atribuire prin mutare
    Mage& Mage::operator=(Mage&& other) noexcept {
        if (this != &other) {
            m_ability = std::move(other.m_ability);
            m_used = other.m_used;
            other.m_used = false; // Resetez starea obiectului mutat
        }
        std::cout << "Mage assigned via move.\n";
        return *this;
    }

    // Destructor
    Mage::~Mage() {
        std::cout << "Mage destroyed.\n";
    }

    //descriere abilitati
    const std::unordered_map<Mage::MagicAbility, std::string> abilityDescriptions = {
        { Mage::MagicAbility::removeOponnentCard, "Remove the last card played by your opponent from the board." },
        { Mage::MagicAbility::removeEntireRow, "Remove all cards from a specific row on the board." },
        { Mage::MagicAbility::coverOponnetCard, "Cover one of your opponent's cards with your own card." },
        { Mage::MagicAbility::createPit, "Create a pit on the board that removes all cards from that position." },
        { Mage::MagicAbility::moveOwnStack, "Move one of your own stacks to another position on the board." },
        { Mage::MagicAbility::extraEterCard, "Add an extra Ether card to your hand." },
        { Mage::MagicAbility::moveOponnentStack, "Move one of your opponent's stacks to a different position." },
        { Mage::MagicAbility::shiftRowToEdge, "Shift a row of cards to the edge of the board." }
    };

    // Gasirea pozitiei unei carti pe tabla
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

        // Afiseaza descrierea abilitatii
        auto it = abilityDescriptions.find(m_ability);
        if (it != abilityDescriptions.end()) {
            std::cout << "You are about to activate the following ability:\n";
            std::cout << it->second << "\n";
        }
        else {
            std::cout << "Unknown ability. Proceeding with activation.\n";
        }

        // Confirmarea utilizatorului
        char confirmation;
        std::cout << "Do you want to proceed with this ability? (Y/N): ";
        std::cin >> confirmation;
        if (std::toupper(confirmation) != 'Y') {
            std::cout << "Ability activation canceled.\n";
            return;
        }

        // Activeaza abilitatea folosind harta de functii
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

        auto abilityIt = abilityMap.find(m_ability);
        if (abilityIt != abilityMap.end()) {
            abilityIt->second();
        }
        else {
            throw std::invalid_argument("Unknown ability!");
        }

        // Incrementarea abilitatii
        ++abilityUsage[m_ability];
        m_used = true;

        std::cout << "Ability successfully activated.\n";

        // Afideaza statisticile utilizarii abilitatilor
        displayAbilityUsage();
    }

    // Eliminare carte a oponentului
    void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {
        std::cout << "Activating ability: Remove Opponent Card\n";
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
        std::cout << "Activating ability: Remove Entire Row\n";
        for (size_t col = 0; col < board.GetCols(); ++col) {
            removeCardFromBoard(board[{0, col}]);
        }
        std::cout << "Entire row has been removed!\n";
    }

    // Acoperire carte adversar
    void Mage::coverOponnentCard(Player& player, Player& oponnent, Board& board) {
        std::cout << "Activating ability: Cover Opponent Card\n";
        if (auto position = player.findEmptyCell(board); position != std::make_pair(255, 255)) {
            const Card& card = player.GetCardsInHand().back();
            player.placeCard(position.first, position.second, card, board);
            std::cout << "Opponent's card has been covered.\n";
        }
    }

    // Creare groapa
    void Mage::createPit(Board& board) {
        std::cout << "Activating ability: Create Pit\n";
        int row = rand() % board.GetRows();
        int col = rand() % board.GetCols();
        if (board.isValidPosition(row, col)) {
            board[{row, col}].reset();
            std::cout << "Pit created at (" << row << ", " << col << ").\n";
        }
    }

    // Adaugare carte Eter
    void Mage::addExtraEterCard(Player& player) {
        std::cout << "Activating ability: Add Extra Ether Card\n";
        player.AddCardToHand({ 1, "eter", true });
        std::cout << "Extra Ether card added to player's hand.\n";
    }

    // Mutare teanc propriu
    void Mage::moveOwnStack(Player& player, Board& board) {
        std::cout << "Activating ability: Move Own Stack\n";
        auto from = player.findEmptyCell(board);
        auto to = player.findEmptyCell(board);
        moveStack(from, to, board);
    }

    // Mutare teanc adversar
    void Mage::moveOponnentStack(Player& oponnent, Board& board) {
        std::cout << "Activating ability: Move Opponent Stack\n";
        auto from = oponnent.findEmptyCell(board);
        auto to = oponnent.findEmptyCell(board);
        moveStack(from, to, board);
    }

    // Mutare rand la marginea tablei
    void Mage::shiftRowToEdge(Board& board) {
        std::cout << "Activating ability: Shift Row to Edge\n";
        for (size_t col = 0; col < board.GetCols(); ++col) {
            if (auto& stack = board[{board.GetRows() - 1, col}]; stack.has_value()) {
                board[{0, col}] = stack;
                stack.reset();
            }
        }
        std::cout << "Row moved to the edge.\n";
    }

    std::unordered_map<Mage::MagicAbility, int> Mage::abilityUsage = {};

    std::string Mage::abilityToString(MagicAbility ability) {
        switch (ability) {
        case MagicAbility::removeOponnentCard: return "Remove Opponent Card";
        case MagicAbility::removeEntireRow: return "Remove Entire Row";
        case MagicAbility::coverOponnetCard: return "Cover Opponent Card";
        case MagicAbility::createPit: return "Create Pit";
        case MagicAbility::moveOwnStack: return "Move Own Stack";
        case MagicAbility::extraEterCard: return "Add Extra Ether Card";
        case MagicAbility::moveOponnentStack: return "Move Opponent Stack";
        case MagicAbility::shiftRowToEdge: return "Shift Row to Edge";
        default: return "Unknown Ability";
        }
    }

    void Mage::displayAbilityUsage() {
        std::cout << "Abilities usage statistics:\n";
        for (const auto& [ability, count] : abilityUsage) {
            std::cout << "- " << abilityToString(ability) << ": " << count << " times\n";
        }
    }

}
