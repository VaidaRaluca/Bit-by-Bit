module game;
using namespace eter;
import card;
import player;
import <string>;
import <iostream>;
import amode;
import bmode;
import board;

Game::Game(Player player1, Player player2, Board board, std::string gameMode):
	m_player1{player1},m_player2{player2},m_board{board},m_gameMode{gameMode}, m_isPlayerTurn{true},
    m_player1Wins{0},m_player2Wins{0},m_nrRound{0}
{}

Player Game::GetPlayer1() const
{
	return m_player1;
}

Player Game::GetPlayer2() const
{
	return m_player2; 
}

Board Game::GetBoard() const
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

void Game::playTurn() {
    if (m_isPlayerTurn) {
        m_player1.PrintCardsInHand();
        handlePlayerTurn(GetPlayer1Ref());
    }
    else {
        m_player2.PrintCardsInHand();
        handlePlayerTurn(GetPlayer2Ref());
    }
    SetIsPlayerTurn();
}

//Functii ajutatoare

//Gestionarea turei unui jucător
void Game::handlePlayerTurn(Player& player) {
    std::cout << player.GetName()
        << "  enter the coordinates (x and y) of the position on the board and the index of the card you want to place.\n ";

    int x, y, cardIndex;
    getInputCoordinates(x, y, cardIndex);

    bool ok;
    ok=player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
    while (!ok) {
        std::cout << player.GetName() << " try to place a card again\n";
        getInputCoordinates(x, y, cardIndex);
        ok = player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
    }
}

//Obtinerea coordonatelor
void Game::getInputCoordinates(int& x, int& y, int& cardIndex) {
    std::cout << "x= "; std::cin >> x;
    std::cout << "y= "; std::cin >> y;
    std::cout << "index of the card= "; std::cin >> cardIndex;
}

char Game::VerifyGameOver()
{
    std::string winnerColor = m_board.findWinner();
    std::cout << winnerColor << '\n';
    
    if (winnerColor == m_player1.GetColor())
        {
            IncrementPlayer1Wins();
            std::cout << "Player " << m_player1.GetName() << " wins this round!" << std::endl;
            return '1';
        }
    if (winnerColor == m_player2.GetColor())
    {
        IncrementPlayer2Wins();
        std::cout << "Player " << m_player2.GetName() << " wins this round!" << std::endl;
        return '1';
    }
    if (m_player1.GetCardsInHand().empty())
        {
            std::cout << "Player " << m_player1.GetName() << " has no cards left!" << std::endl;
            return'2';
        }
    if (m_player2.GetCardsInHand().empty())
        {
            std::cout << "Player " << m_player2.GetName() << " has no cards left!" << std::endl;
            return '2';
        }
    if (m_board.isBoardFull())
    {
        std::cout << "The board is full!" << std::endl;
        return '3';
    }
    return '0';
}


