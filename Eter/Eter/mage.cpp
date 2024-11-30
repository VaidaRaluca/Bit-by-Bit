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
        if (isAbilityUsed()) {
            throw std::runtime_error("The ability has already been used!");
        }

        displayAbilityDescription();  // Afiseaza descrierea abilitatii

        if (!confirmAbilityActivation()) {  // Confirmarea utilizatorului
            cancelAbilityActivation();
            return;
        }

        bool success = false;  // Indicator pentru activarea cu succes a abilitatii

        try {
            success = executeAbility(player, oponnent, board);  // Incearca activarea abilitatii
        }
        catch (const std::exception& e) {
            std::cout << "Ability activation failed: " << e.what() << "\n";
        }

        if (success) {
            updateAbilityUsage();  // Actualizeaza contorul utilizarii
            notifyAbilityActivated();  // Notificare de succes
        }
        else {
            std::cout << "The ability was not activated successfully. Please try again.\n";
        }
    }

    // Eliminare carte a oponentului
    void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {
        std::cout << "Activating ability: Remove Opponent Card\n";

        int row, col;
        std::cout << "Enter the position (row, column) of the opponent's card to remove: ";
        std::cin >> row >> col;

        if (!board.isValidPosition(row, col)) {
            std::cout << "Invalid position (" << row << ", " << col << ").\n";
            return;
        }

        auto& cell = board[{row, col}];
        if (!cell.has_value() || cell->empty()) {
            std::cout << "No card found at position (" << row << ", " << col << ").\n";
            return;
        }

        cell->pop(); // Elimina cartea de sus din stiva
        if (cell->empty()) {
            cell.reset(); // Reseteaza celula daca stiva devine goala
        }

        std::cout << "Opponent's card removed from (" << row << ", " << col << ").\n";
    }

    // Eliminare rand intreg
    void Mage::removeEntireRow(Player& player, Board& board) {
        std::cout << "Activating ability: Remove Entire Row\n";

        // Solicita utilizatorului randul pe care doreste sa-l elimine
        int row;
        std::cout << "Enter the row number to remove: ";
        std::cin >> row;

        // Valideaza daca randul este valid
        if (row < 0 || row >= board.GetRows()) {
            std::cout << "Invalid row number. The board has rows from 0 to " << board.GetRows() - 1 << ".\n";
            return;
        }

        // Elimina toate cartile de pe randul specificat
        for (size_t col = 0; col < board.GetCols(); ++col) {
            removeCardFromBoard(board[{row, col}]);
        }

        std::cout << "Row " << row << " has been removed!\n";
    }


    // Acoperire carte adversar
    void Mage::coverOponnentCard(Player& player, Player& oponnent, Board& board) {
        std::cout << "Activating ability: Cover Opponent Card\n";

        int row, col;
        std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
        std::cin >> row >> col;

        // Valideaza pozitia introdusa
        if (!board.isValidPosition(row, col)) {
            std::cout << "Invalid position (" << row << ", " << col << ") on the board.\n";
            return;
        }

        auto& cell = board[{row, col}];
        if (!cell.has_value() || cell->empty()) {
            std::cout << "No card found at position (" << row << ", " << col << ").\n";
            return;
        }

        const Card& opponentCard = cell->top();

        if (player.GetCardsInHand().empty()) {
            std::cout << "You have no cards in hand to cover the opponent's card.\n";
            return;
        }

        // Afiseaza cartile din mana jucatorului
        player.PrintCardsInHand();

        int choice;
        while (true) {
            std::cout << "Select a card to play (1-" << player.GetCardsInHand().size() << "): ";
            std::cin >> choice;

            if (choice < 1 || static_cast<size_t>(choice) > player.GetCardsInHand().size()) {
                std::cout << "Invalid choice. Try again.\n";
                continue;
            }

            const Card& playerCard = player.GetCardsInHand()[choice - 1];

            if (playerCard.GetValue() >= opponentCard.GetValue()) {
                std::cout << "The selected card (" << playerCard.GetValue()
                    << ") must have a lower value than the opponent's card ("
                    << opponentCard.GetValue() << "). Try again.\n";
                continue;
            }

            // Adauga cartea jucatorului peste cartea oponentului
            cell->push(playerCard); // Pune cartea in stiva

            // Elimina cartea din mana jucatorului
            auto& hand = player.GetCardsInHand();
            hand.erase(hand.begin() + (choice - 1));
            player.AddPlayedCard(playerCard); // Adauga cartea la cele jucate

            std::cout << "Card placed successfully at (" << row << ", " << col << ").\n";
            break;
        }
    }

    // Creare groapa
    void Mage::createPit(Board& board) {
        std::cout << "Activating ability: Create Pit\n";

        int row, col;
        std::cout << "Enter the position (row, column) where you want to create a pit: ";
        std::cin >> row >> col;

        if (!board.isValidPosition(row, col)) {
            std::cout << "Invalid position (" << row << ", " << col << ").\n";
            return;
        }

        auto& cell = board[{row, col}];
        if (cell.has_value() && !cell->empty()) {
            std::cout << "Cannot create a pit at (" << row << ", " << col << ") because it is occupied.\n";
            return;
        }

        cell.reset(); // Creeaza groapa prin golirea celulei
        std::cout << "Pit created at (" << row << ", " << col << ").\n";
    }


    // Adaugare carte Eter
    void Mage::addExtraEterCard(Player& player, Board& board) {
        std::cout << "Activating ability: Add Extra Ether Card\n";

        int row, col;

        // Solicita utilizatorului sa introduca pozitia unde va fi plasata cartea
        while (true) {
            std::cout << "Enter the position (row, column) to place the Ether card: ";
            std::cin >> row >> col;

            // Verifica daca pozitia este valida
            if (!board.isValidPosition(row, col)) {
                std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
                continue;
            }

            // Verifica daca pozitia este goala
            if (board[{row, col}].has_value()) {
                std::cout << "The position (" << row << ", " << col << ") is not empty. Try again.\n";
                continue;
            }

            // Daca pozitia este valida si goala, iesi din bucla
            break;
        }

        // Creeaza o carte Eter si o plaseaza pe tabla
        Card etherCard(1, "eter", true);
        board.placeCard(row, col, etherCard);

        std::cout << "Extra Ether card placed at (" << row << ", " << col << ").\n";
    }


    // Mutare teanc propriu
    void Mage::moveOwnStack(Player& player, Board& board) {
        std::cout << "Activating ability: Move Own Stack\n";

        int fromRow, fromCol, toRow, toCol;
        std::cout << "Enter the source position (row, column) of the stack: ";
        std::cin >> fromRow >> fromCol;
        std::cout << "Enter the destination position (row, column): ";
        std::cin >> toRow >> toCol;

        if (!board.isValidPosition(fromRow, fromCol) || !board.isValidPosition(toRow, toCol)) {
            std::cout << "Invalid source or destination position.\n";
            return;
        }

        auto& fromCell = board[{fromRow, fromCol}];
        auto& toCell = board[{toRow, toCol}];

        if (!fromCell.has_value() || fromCell->empty()) {
            std::cout << "No stack found at the source position.\n";
            return;
        }

        if (toCell.has_value()) {
            std::cout << "Destination position is not empty.\n";
            return;
        }

        toCell = std::move(fromCell); // Muta teancul
        fromCell.reset();             // Goleste pozitia sursa
        std::cout << "Stack moved from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
    }

    // Mutare teanc adversar
    void Mage::moveOponnentStack(Player& oponnent, Board& board) {
        std::cout << "Activating ability: Move Opponent Stack\n";

        int fromRow, fromCol, toRow, toCol;

        // Solicita pozitia de plecare
        while (true) {
            std::cout << "Enter the position (row, column) of the opponent's stack to move: ";
            std::cin >> fromRow >> fromCol;

            // Valideaza pozitia de plecare
            if (!board.isValidPosition(fromRow, fromCol)) {
                std::cout << "Invalid position (" << fromRow << ", " << fromCol << ") on the board. Try again.\n";
                continue;
            }

            auto& fromCell = board[{fromRow, fromCol}];
            if (!fromCell.has_value() || fromCell->empty()) {
                std::cout << "The position (" << fromRow << ", " << fromCol << ") does not contain a valid stack. Try again.\n";
                continue;
            }

            break;
        }

        // Solicita pozitia de destinatie
        while (true) {
            std::cout << "Enter the destination position (row, column): ";
            std::cin >> toRow >> toCol;

            // Valideaza pozitia de destinatie
            if (!board.isValidPosition(toRow, toCol)) {
                std::cout << "Invalid position (" << toRow << ", " << toCol << ") on the board. Try again.\n";
                continue;
            }

            if (board[{toRow, toCol}].has_value()) {
                std::cout << "The destination position (" << toRow << ", " << toCol << ") is not empty. Try again.\n";
                continue;
            }

            break;
        }

        // Muta teancul
        moveStack({ fromRow, fromCol }, { toRow, toCol }, board);

        std::cout << "Stack moved from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
    }


    // Mutare rand la marginea tablei
    void Mage::shiftRowToEdge(Board& board) {
        std::cout << "Activating ability: Shift Row to Edge\n";

        int fromRow, toRow;

        // Solicita utilizatorului randul de plecare
        while (true) {
            std::cout << "Enter the row number to move (must be on the edge): ";
            std::cin >> fromRow;

            // Verifica daca randul este la margine
            if (fromRow != 0 && fromRow != board.GetRows() - 1) {
                std::cout << "Invalid row. You can only move rows on the edges (0 or "
                    << board.GetRows() - 1 << "). Try again.\n";
                continue;
            }

            // Verifica daca randul are cel putin 3 pozitii ocupate
            int occupiedCount = 0;
            for (size_t col = 0; col < board.GetCols(); ++col) {
                if (board[{fromRow, col}].has_value()) {
                    ++occupiedCount;
                }
            }

            if (occupiedCount < 3) {
                std::cout << "The selected row must have at least 3 occupied positions. Try again.\n";
                continue;
            }

            break;
        }

        // Solicita utilizatorului randul de destinatie
        while (true) {
            std::cout << "Enter the destination row (must be on the edge): ";
            std::cin >> toRow;

            // Verifica daca randul de destinatie este la margine si diferit de cel de plecare
            if ((toRow != 0 && toRow != board.GetRows() - 1) || toRow == fromRow) {
                std::cout << "Invalid destination row. You can only move to the opposite edge (0 or "
                    << board.GetRows() - 1 << ") and not the same as the source row. Try again.\n";
                continue;
            }

            break;
        }

        // Muta randul
        for (size_t col = 0; col < board.GetCols(); ++col) {
            if (board[{fromRow, col}].has_value()) {
                board[{toRow, col}] = board[{fromRow, col}];
                board[{fromRow, col}].reset();
            }
        }

        std::cout << "Row " << fromRow << " moved to row " << toRow << ".\n";
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

    //Functii ajutatoare
    bool Mage::isAbilityUsed() const {
        return m_used;
    }

    void Mage::displayAbilityDescription() const {
        auto it = abilityDescriptions.find(m_ability);
        if (it != abilityDescriptions.end()) {
            std::cout << "You are about to activate the following ability:\n";
            std::cout << it->second << "\n";
        }
        else {
            std::cout << "Unknown ability. Proceeding with activation.\n";
        }
    }

    bool Mage::confirmAbilityActivation() const {
        char confirmation;
        std::cout << "Do you want to proceed with this ability? (Y/N): ";
        std::cin >> confirmation;
        return std::toupper(confirmation) == 'Y';
    }

    void Mage::cancelAbilityActivation() const {
        std::cout << "Ability activation canceled.\n";
    }

    bool Mage::executeAbility(Player& player, Player& oponnent, Board& board) {
        static const std::unordered_map<MagicAbility, std::function<void()>> abilityMap = {
            { MagicAbility::removeOponnentCard, [&]() { removeOponnentCard(player, oponnent, board); } },
            { MagicAbility::removeEntireRow,    [&]() { removeEntireRow(player, board); } },
            { MagicAbility::coverOponnetCard,   [&]() { coverOponnentCard(player, oponnent, board); } },
            { MagicAbility::createPit,          [&]() { createPit(board); } },
            { MagicAbility::moveOwnStack,       [&]() { moveOwnStack(player, board); } },
            { MagicAbility::extraEterCard,      [&]() { addExtraEterCard(player, board); } },
            { MagicAbility::moveOponnentStack,  [&]() { moveOponnentStack(oponnent, board); } },
            { MagicAbility::shiftRowToEdge,     [&]() { shiftRowToEdge(board); } }
        };

        auto abilityIt = abilityMap.find(m_ability);
        if (abilityIt != abilityMap.end()) {
            try {
                abilityIt->second();  // Incearca sa activezi abilitatea
                return true;          // Succes
            }
            catch (const std::exception& e) {
                std::cout << "Error while activating ability: " << e.what() << "\n";
                return false;         // Esec din cauza exceptiei
            }
        }
        else {
            std::cout << "Unknown ability!\n";
            return false;             // Esec pentru abilitate necunoscuta
        }
    }

    void Mage::updateAbilityUsage() {
        ++abilityUsage[m_ability];
        m_used = true;
    }

    void Mage::notifyAbilityActivated() const {
        std::cout << "Ability successfully activated.\n";
    }

}
