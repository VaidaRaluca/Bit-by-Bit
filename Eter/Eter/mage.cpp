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
            updateAbilityUsage();  // Actualizeaz? contorul utilizarii
            notifyAbilityActivated();  // Notificare de succes
        }
        else {
            std::cout << "The ability was not activated successfully. Please try again.\n";
        }
    }


    // Eliminare carte a oponentului
    void Mage::removeOponnentCard(Player& player, Player& oponnent, Board& board) {
        std::cout << "Activating ability: Remove Opponent Card\n";

        // Solicita utilizatorului pozitia cartii de eliminat
        int row, col;
        std::cout << "Enter the position (row, column) of the card to remove: ";
        std::cin >> row >> col;

        // Valideaza pozitia introdusa
        if (!board.isValidPosition(row, col)) {
            std::cout << "Invalid position (" << row << ", " << col << ") on the board.\n";
            return;
        }

        // Ob?ine stiva de la pozitia specificata
        auto& cell = board[{row, col}];
        if (!cell.has_value() || cell->empty()) {
            std::cout << "No card found at position (" << row << ", " << col << ").\n";
            return;
        }

        // Elimina cartea de la pozitia specificata
        cell->pop();
        if (cell->empty()) {
            cell.reset();  // Reseteaza celula daca stiva devine goala
        }

        std::cout << "Removed card at position (" << row << ", " << col << ").\n";
    }


    // Eliminare rand intreg
    void Mage::removeEntireRow(Player& player, Board& board) {
        std::cout << "Activating ability: Remove Entire Row\n";

        // Solicit? utilizatorului rândul pe care dore?te s?-l elimine
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

        // Solicita utilizatorului pozitia cartii pe care doreste sa o acopere
        int row, col;
        std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
        std::cin >> row >> col;

        // Valideaza pozitia introdusa
        if (!board.isValidPosition(row, col)) {
            std::cout << "Invalid position (" << row << ", " << col << ") on the board.\n";
            return;
        }

        // Verifica daca exista o carte la pozitia specificata
        auto& cell = board[{row, col}];
        if (!cell.has_value() || cell->empty()) {
            std::cout << "No card found at position (" << row << ", " << col << ").\n";
            return;
        }

        // Verifica daca jucatorul are carti in mana pentru a efectua acoperirea
        if (player.GetCardsInHand().empty()) {
            std::cout << "You have no cards in hand to cover the opponent's card.\n";
            return;
        }

        // Obtine ultima carte din mana jucatorului
        const Card& card = player.GetCardsInHand().back();

        // Acopera cartea de la pozitia specificata
        if (board.placeCard(row, col, card)) {
            player.GetCardsInHand().pop_back();  // Scoate cartea din mâna juc?torului
            player.AddPlayedCard(card);         // Adaug? cartea în lista de c?r?i jucate
            std::cout << "Card placed successfully at (" << row << ", " << col << ").\n";
        }
        else {
            std::cout << "Failed to place the card at the specified position.\n";
        }
    }


    // Creare groapa
    void Mage::createPit(Board& board) {
        std::cout << "Activating ability: Create Pit\n";

        int row, col;

        // Solicita utilizatorului sa introduca pozitia pentru groapa
        while (true) {
            std::cout << "Enter the position (row, column) to create a pit: ";
            std::cin >> row >> col;

            // Valideaz? daca pozitia este valida
            if (!board.isValidPosition(row, col)) {
                std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
                continue;
            }

            // Verific? dac? pozitia este goala
            if (board[{row, col}].has_value()) {
                std::cout << "The position (" << row << ", " << col << ") is not empty. Try again.\n";
                continue;
            }

            // Daca pozitia este valida si goala, iesi din bucla
            break;
        }

        // Creeaza groapa la pozitia specificata
        board[{row, col}].reset();
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

            // Dac? pozitia este valid? si goala, iesi din bucla
            break;
        }

        // Creeaza o carte Eter si o plaseaz? pe tabla
        Card etherCard(1, "eter", true);
        board.placeCard(row, col, etherCard);

        std::cout << "Extra Ether card placed at (" << row << ", " << col << ").\n";
    }


    // Mutare teanc propriu
    void Mage::moveOwnStack(Player& player, Board& board) {
        std::cout << "Activating ability: Move Own Stack\n";

        int fromRow, fromCol, toRow, toCol;

        // Solicita pozitia de plecare
        while (true) {
            std::cout << "Enter the position (row, column) of the stack to move: ";
            std::cin >> fromRow >> fromCol;

            // Valideaza pozitia de plecare
            if (!board.isValidPosition(fromRow, fromCol)) {
                std::cout << "Invalid position (" << fromRow << ", " << fromCol << ") on the board. Try again.\n";
                continue;
            }

            auto& fromCell = board[{fromRow, fromCol}];
            if (!fromCell.has_value() || fromCell->empty() || fromCell->top().GetColor() != player.GetColor()) {
                std::cout << "The position (" << fromRow << ", " << fromCol << ") does not contain your stack. Try again.\n";
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


    // Mutare teanc adversar
    void Mage::moveOponnentStack(Player& oponnent, Board& board) {
        std::cout << "Activating ability: Move Opponent Stack\n";

        int fromRow, fromCol, toRow, toCol;

        // Solicit? pozitia de plecare
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

            // Verifica daca randul are cel pu?in 3 pozitii ocupate
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
                abilityIt->second();  // Incearca ss activezi abilitatea
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
