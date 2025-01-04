#include "game.h"
using namespace eter;

Game::Game(Player player1, Player player2,std::string gameMode) :
    m_player1{ player1 }, m_player2{ player2 }, m_gameMode{ gameMode },
    m_isPlayerTurn{ true }, m_isUsedExplosion{false},
    m_player1Wins{ 0 }, m_player2Wins{ 0 }, m_nrRound{ 0 }
{}

Player Game::GetPlayer1() const
{
    return m_player1;
}

Player Game::GetPlayer2() const
{
    return m_player2;
}

Board Game::GetBoard()
{
    return m_board;
}

//Getter ce returneaza &

Player& Game::GetPlayer1Ref() {
    return m_player1;
}

Player& Game::GetPlayer2Ref() {
    return m_player2;
}

Board& Game::GetBoardRef() {
    return m_board;
}


std::string Game::GetGameMods()
{
    return m_gameMode;
}

bool Game::GetIsPlayerTurn()
{
    return m_isPlayerTurn;
}

bool eter::Game::GetIsUsedExplosion()
{
    return m_isUsedExplosion;
}

uint8_t Game::GetPlayer1Wins()
{
    return m_player1Wins;
}

uint8_t Game::GetPlayer2Wins()
{
    return m_player2Wins;
}

uint8_t Game::GetNrRound()
{
    return m_nrRound;
}

const std::vector<Card>& eter::Game::GetReturnedCards() const
{
    return m_returnedCards;
}

uint8_t eter::Game::GetCountTurnForReturnedCards()
{
    return m_countTurnForReturnedCards;
}


void Game::SetBoard(Board board)
{
    m_board = board;
}

void Game::SetGameMods(std::string gameMode)
{
    m_gameMode = gameMode;
}

void Game::SetIsPlayerTurn()
{
    m_isPlayerTurn = !m_isPlayerTurn;
}

void eter::Game::SetIsUsedExplosion( bool ok)
{
    m_isUsedExplosion = ok;
}

void Game::IncrementPlayer1Wins()
{
    ++m_player1Wins;
}

void Game::IncrementPlayer2Wins()
{
    ++m_player2Wins;
}

void Game::IncrementNrRound()
{
    ++m_nrRound;
}

void eter::Game::SetReturnedCards(const std::vector<Card>& cards)
{
    m_returnedCards = cards;
}

void eter::Game::SetCountTurnForReturnedCards(uint8_t count)
{
    m_countTurnForReturnedCards = count;
}

void Game::playTurn() {
    if (m_countTurnForReturnedCards == 3)
    {
        distributeReturnedCards();
    }
    else
        if (m_countTurnForReturnedCards ==1||m_countTurnForReturnedCards==2)
            m_countTurnForReturnedCards ++;

    if (m_isPlayerTurn) {
        m_player1.PrintCardsInHand();
        handlePlayerTurn(GetPlayer1Ref());
    }
    else {
        m_player2.PrintCardsInHand();
        handlePlayerTurn(GetPlayer2Ref());
    }

    handleActivateExplosion();
    SetIsPlayerTurn();
}

void Game::playIllusion() {
    if (m_isPlayerTurn) {
        m_player1.PrintCardsInHand();
        handlePlayerTurnWithIllusion(GetPlayer1Ref());
    }
    else {
        m_player2.PrintCardsInHand();
        handlePlayerTurnWithIllusion(GetPlayer2Ref());
    }
    SetIsPlayerTurn();
}

//Functii ajutatoare

//Gestionarea turei unui jucător
void Game::handlePlayerTurn(Player& player) {
    qDebug()    << player.GetName()
    << " enter the coordinates (x and y) >=0 of the position on the board and the index of the card (>=0) you want to place.\n";

    size_t x, y, cardIndex;
    getInputCoordinates(x, y, cardIndex);
    /*if (cardIndex < 0 || cardIndex >= player.GetCardsInHand().size()) { // gotta work on this
        std::cout << "Invalid card index\n";
        return;
    }*/
    std::optional<std::stack<Card>> targetCell;
    if (m_board.IsValidPosition(x, y))
        targetCell = m_board[std::make_pair(x, y)];
    else
        std::cout << "Invalid position!\n";
    if (targetCell.has_value() && !targetCell->empty() && targetCell.value().top().GetPosition() == false) {
        Player& opponent = (player.GetName() == m_player1.GetName()) ? m_player2 : m_player1;
        handleCardCover(player, opponent, x, y, cardIndex);
    }
    else
    {
        bool ok;
        ok = player.PlaceCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
        while (!ok) {
             qDebug() << player.GetName() << " try to place a card again\n";
            getInputCoordinates(x, y, cardIndex);
            ok = player.PlaceCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
        }
    }
}

void eter::Game::handlePlayerTurnWithIllusion(Player& player) {
    if (player.GetHasUsedIllusion())
    {
         qDebug() << "Illusion has already been used\n";
        return;
    }
     qDebug() << player.GetName()
              << " enter the coordinates (x and y) of the position on the board and the index of the card you want to use illusion on.\n";

    size_t x, y, cardIndex;
    getInputCoordinates(x, y, cardIndex);
    if (cardIndex < 0 || cardIndex >= player.GetCardsInHand().size()) {
         qDebug() << "Invalid card index.\n";
        return;
    }
    player.UseIllusion(x, y, m_board, player.GetCardsInHand().at(cardIndex));
}

void eter::Game::handleActivateExplosion()
{
    if (GetIsUsedExplosion() == false && m_board.IsTwoLineComplete())
    {
        std::cout << m_board;
        QString playerName = GetIsPlayerTurn() ? m_player1.GetName() : m_player2.GetName();
         qDebug() << playerName << " fill the second line. Do you want to activate the explosion? (y/n) \n";
        char choice;
        std::cin >> choice;
        if (choice == 'y')
        {
            Explosion explosion(m_board.GetDimMax(), GetBoard());
            explosion.rotateExplosion();
            std::cout << "Do you want to continue to activate the explosion ? (y/ n) \n";
            std::cin >> choice;
            if (choice == 'y')
            {
                GetBoardRef() = explosion.applyEffects();
                m_returnedCards = explosion.GetReturnedCards();
                m_countTurnForReturnedCards = 1;
            }
        }
        SetIsUsedExplosion(true);

    }
}

//Obtinerea coordonatelor
void Game::getInputCoordinates(size_t& x, size_t& y, size_t& cardIndex) {
    std::cout << "x = "; std::cin >> x;
    std::cout << "y = "; std::cin >> y;
    std::cout << "index of the card = "; std::cin >> cardIndex;
}

void eter::Game::distributeReturnedCards()
{
    auto it = m_returnedCards.begin();
    while (it != m_returnedCards.end())
    {
        if (it->GetColor() == m_player1.GetColor())
        {
            m_player1.AddToCardsInHand(*it);
            it = m_returnedCards.erase(it);
        }
        else if (it->GetColor() == m_player2.GetColor())
        {
            m_player2.AddToCardsInHand(*it);
            it = m_returnedCards.erase(it);
        }
    }
}

char Game::VerifyGameOver()
{
    std::string winnerColor = m_board.FindWinner();
    std::cout << winnerColor << '\n';

    if (winnerColor == m_player1.GetColor())
    {
        IncrementPlayer1Wins();
         qDebug() << "Player " << m_player1.GetName() << " wins this round!";
        return '1';
    }
    if (winnerColor == m_player2.GetColor())
    {
        IncrementPlayer2Wins();
         qDebug() << "Player " << m_player2.GetName() << " wins this round!";
        return '1';
    }
    if (m_player1.GetCardsInHand().empty())
    {
         qDebug() << "Player " << m_player1.GetName() << " has no cards left!";
        return'2';
    }
    if (m_player2.GetCardsInHand().empty())
    {
         qDebug() << "Player " << m_player2.GetName() << " has no cards left!";
        return '2';
    }
    if (m_board.IsBoardFull())
    {
         qDebug() << "The board is full!";
        return '3';
    }
    return '0';
}

void eter::Game::resetBoard()
{
    m_board.Clear();
}

void Game::handleCardCover(Player& currentPlayer, Player& opponent, size_t x, size_t y, size_t cardIndex) {
    auto& targetCell = m_board[{x, y}];
    if (!targetCell.has_value() || targetCell->empty()) {
        std::cout << "Invalid action. There's no card to cover at (" << x << ", " << y << ").\n";
        return;
    }
    Card& newCard = currentPlayer.GetCardsInHand().at(cardIndex);
    Card& existingCard = targetCell->top();
    if (existingCard.GetColor() == currentPlayer.GetColor()) {
        std::cout << "Cannot place card over your own illusion.\n";
        bool ok;
        ok = currentPlayer.PlaceCard(x, y, currentPlayer.GetCardsInHand().at(cardIndex), m_board);
        while (!ok) {
             qDebug() << currentPlayer.GetName() << " try to place a card again\n";
            getInputCoordinates(x, y, cardIndex);
            ok = currentPlayer.PlaceCard(x, y, currentPlayer.GetCardsInHand().at(cardIndex), m_board);
        }
        return;
    }
    if (!existingCard.GetPosition()) {
        existingCard.SetPosition(true);
        if (newCard.GetValue() > existingCard.GetValue()) {
            std::cout << "The opponent's card covers the revealed card.\n";
            currentPlayer.PlaceCard(x, y, newCard, m_board); // Place the card
        }
        else {
            std::cout << "The opponent's card is not stronger. It is removed from the game.\n";
            currentPlayer.GetCardsInHand().erase(currentPlayer.GetCardsInHand().begin() + cardIndex);
            currentPlayer.AddToEliminatedCards(newCard);
             qDebug() << currentPlayer.GetName() << " loses their turn.\n";
            return;
        }
    }
}


