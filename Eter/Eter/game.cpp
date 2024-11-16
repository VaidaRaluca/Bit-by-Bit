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
        handlePlayerTurn(m_player1);
    }
    else {
        handlePlayerTurn(m_player2);
    }
    SetIsPlayerTurn();
}

void Game::startGame()
{
    if (m_gameMode == "AMode") 
    {
        AMode mode(m_player1, m_player2, m_board);
        mode.startMatch();   
    }
    else
        if (m_gameMode == "BMode")
        {  
             


        }
        else {
         
            std::cout << "Modul de joc necunoscut!" << std::endl;
         }
}

uint8_t Game::VerifyGameOver()
{
    const std::string winnerColor = m_board.findWinner();
    if (GetIsPlayerTurn())
    {
        if (winnerColor == m_player1.GetColor())
        {
            IncrementPlayer1Wins();
            return 1;
        }
        if (m_player1.GetCardsInHand().empty())
            return 2;
    }
    else
    {
        if (winnerColor == m_player2.GetColor())
        {
            IncrementPlayer2Wins();
            return 1;
        }
        if (m_player2.GetCardsInHand().empty())
            return 2;
    }
    if (m_board.isBoardFull())
        return 3;

    return 0;
}

//Functii ajutatoare

//Gestionarea turei unui jucător
void Game::handlePlayerTurn(Player& player) {
    player.PrintCardsInHand();
    std::cout << player.GetName() 
        << " introdu coordonatele pozitiei de pe tabla (x si y) si indexul cartii pe care doresti sa o plasezi ";

    int x, y, cardIndex;
    getInputCoordinates(x, y, cardIndex);

    // Plaseaza cartea pe tabla
    bool ok = player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
    while (!ok) {
        std::cout << player.GetName() << " introdu coordonatele corecte.\n";
        getInputCoordinates(x, y, cardIndex);
        ok = player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
    }
}

//Obtinerea coordonatelor
void Game::getInputCoordinates(int& x, int& y, int& cardIndex) {
    std::cout << "x= "; std::cin >> x;
    std::cout << "y= "; std::cin >> y;
    std::cout << "CardIndex= "; std::cin >> cardIndex;
}

