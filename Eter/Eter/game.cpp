﻿#include "Game.h"
using namespace eter;
#include <string>
#include <iostream>

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

void Game::incrementPlayer1Wins()
{
	++m_player1Wins;
}

void Game::incrementPlayer2Wins()
{
	++m_player2Wins;
}

void Game::incrementNrRound()
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
		m_player1.printCardsInHand();
		handlePlayerTurn(GetPlayer1Ref());
	}
	else {
		m_player2.printCardsInHand();
		handlePlayerTurn(GetPlayer2Ref());
	}

	handleActivateExplosion();
	SetIsPlayerTurn();
}

void Game::playIllusion() {
	if (m_isPlayerTurn) {
		m_player1.printCardsInHand();
		handlePlayerTurnWithIllusion(GetPlayer1Ref());
	}
	else {
		m_player2.printCardsInHand();
		handlePlayerTurnWithIllusion(GetPlayer2Ref());
	}
	SetIsPlayerTurn();
}


uint8_t Game::GetPlayer1Wins() const {
	return m_player1Wins;
}

uint8_t Game::GetPlayer2Wins() const {
	return m_player2Wins;
}

void Game::handlePlayerTurn(Player& player) {
	std::cout << player.GetName()
		<< " enter the coordinates (x and y) >=0 of the position on the board and the index of the card (>=0) you want to place.\n";

	size_t x, y, cardIndex;
	getInputCoordinates(x, y, cardIndex);
	std::optional<std::stack<Card>> targetCell;
	if (m_board.isValidPosition(x, y))
		targetCell = m_board[{x, y}];
	else
		std::cout << "Invalid position!\n";
	if (targetCell.has_value() && !targetCell->empty() && targetCell.value().top().GetPosition() == false) {
		Player& opponent = (player.GetName() == m_player1.GetName()) ? m_player2 : m_player1;
		handleCardCover(player, opponent, x, y, cardIndex);
	}
	else
	{
		bool ok;
		ok = player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
		while (!ok) {
			std::cout << player.GetName() << " try to place a card again\n";
			getInputCoordinates(x, y, cardIndex);
			ok = player.placeCard(x, y, player.GetCardsInHand().at(cardIndex), m_board);
		}
	}
}

void eter::Game::handlePlayerTurnWithIllusion(Player& player) {
	if (player.GetHasUsedIllusion())
	{
		std::cout << "Illusion has already been used\n";
		return;
	}
	std::cout << player.GetName()
		<< " enter the coordinates (x and y) of the position on the board and the index of the card you want to use illusion on.\n";

	size_t x, y, cardIndex;
	getInputCoordinates(x, y, cardIndex);
	if (cardIndex < 0 || cardIndex >= player.GetCardsInHand().size()) {
		std::cout << "Invalid card index.\n";
		return;
	}
	player.useIllusion(x, y, m_board, player.GetCardsInHand().at(cardIndex));
}

void eter::Game::handleActivateExplosion()
{
	if (GetIsUsedExplosion() == false && m_board.isTwoLineComplete())
	{
		std::cout << m_board;
		std::string playerName = GetIsPlayerTurn() ? m_player1.GetName() : m_player2.GetName();
		std::cout << playerName << " fill the second line. Do you want to activate the explosion? (y/n) \n";
		char choice1;
		while (true) {
			std::cin >> choice1;
			if (choice1 == 'y' || choice1 == 'n') {
				break;
			}
			std::cout << "Invalid input. Please enter 'y' or 'n' \n ";
		}

		if (choice1 == 'y')
		{
			Explosion explosion(m_board.GetDimMax(), GetBoard());
			explosion.rotateExplosion();
			std::cout << "Do you want to continue to activate the explosion ? (y/ n) \n";
			char choice2;
			while (true) {
				std::cin >> choice2;
				if (choice2 == 'y' || choice2 == 'n') {
					break;
				}
				std::cout << "Invalid input. Please enter 'y' or 'n' \n ";
			}
			if (choice2 == 'y')
			{
				GetBoardRef() = explosion.applyEffects(GetPlayer1Ref(),GetPlayer2Ref());
				m_returnedCards = explosion.GetReturnedCards();
				m_countTurnForReturnedCards = 1;
			}
		}
		SetIsUsedExplosion(true);

	}
}

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
			m_player1.addCardToHand(*it);
			it = m_returnedCards.erase(it); 
		}
		else if (it->GetColor() == m_player2.GetColor())
		{
			m_player2.addCardToHand(*it);
			it = m_returnedCards.erase(it); 
		}
	}
}

char Game::verifyGameOver()
{
	std::string winnerColor = m_board.findWinner();
	std::cout << winnerColor << '\n';

	if (winnerColor == m_player1.GetColor())
	{
		incrementPlayer1Wins();
		std::cout << "Player " << m_player1.GetName() << " wins this round!" << std::endl;
		return '1';
	}
	if (winnerColor == m_player2.GetColor())
	{
		incrementPlayer2Wins();
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

void eter::Game::resetBoard()
{
	m_board.clear();
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
		ok = currentPlayer.placeCard(x, y, currentPlayer.GetCardsInHand().at(cardIndex), m_board);
		while (!ok) {
			std::cout << currentPlayer.GetName() << " try to place a card again\n";
			getInputCoordinates(x, y, cardIndex);
			ok = currentPlayer.placeCard(x, y, currentPlayer.GetCardsInHand().at(cardIndex), m_board);
		}
		return;
	}
	if (!existingCard.GetPosition()) {
		existingCard.SetPosition(true);
		if (newCard.GetValue() > existingCard.GetValue()) {
			std::cout << "The opponent's card covers the revealed card.\n";
			currentPlayer.placeCard(x, y, newCard, m_board); // Place the card
		}
		else {
			std::cout << "The opponent's card is not stronger. It is removed from the game.\n";
			currentPlayer.GetCardsInHand().erase(currentPlayer.GetCardsInHand().begin() + cardIndex);
			currentPlayer.addToEliminatedCards(newCard);
			std::cout << currentPlayer.GetName() << " loses their turn.\n";
			return;
		}
	}
}

void eter::Game::printPlayers()
{
	std::string textColor, backgroundColor;
	std::string resetColor = "\033[0m";
	textColor = "\033[38;5;9m";  // Red text
	backgroundColor = "\033[48;5;0m";  // Black background
	std::cout << backgroundColor << textColor << m_player1.GetName() << resetColor;
	std::cout << " VS ";
	textColor = "\033[38;5;12m"; // Blue text
	std::cout << backgroundColor << textColor << m_player2.GetName() << resetColor << '\n';
}


