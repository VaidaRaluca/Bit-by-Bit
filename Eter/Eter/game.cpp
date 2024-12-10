module game;
using namespace eter;
import card;
import player;
import <string>;
import <iostream>;
import amode;
import bmode;
import cmode;
import board;

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

void Game::playTurn() {
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
	std::cout << player.GetName()
		<< " enter the coordinates (x and y) >=0 of the position on the board and the index of the card (>=0) you want to place.\n";

	size_t x, y, cardIndex;
	getInputCoordinates(x, y, cardIndex);
	/*if (cardIndex < 0 || cardIndex >= player.GetCardsInHand().size()) { // gotta work on this
		std::cout << "Invalid card index\n";
		return;
	}*/
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
	if (m_board.isTwoLineComplete() && GetIsUsedExplosion() == false)
	{
		std::cout << m_board;
		std::string playerName = GetIsPlayerTurn() ? m_player1.GetName() : m_player2.GetName();
		std::cout << playerName << " fill the second line. Do you want to activate the explosion? (y/n) \n";
		char choice;
		std::cin >> choice;
		if (choice == 'y')
		{
			Explosion explosion(m_board.GetDimMax(), GetBoard());
			explosion.generateRandomEffects();
			explosion.printeffectMatrix();
			std::cout << "Do you want to rotate the explosion card?\n";
			std::cout << "Press l(for left rotation) r (for right rotation) or any key to end rotation.\n";
			std::cin >> choice;
			while (choice == 'l' || choice == 'r')
			{
				if (choice == 'l')
				{
					explosion.rotateCounterClockwise();
					explosion.printeffectMatrix();
				}
				else
				{
					explosion.rotateClockwise();
					explosion.printeffectMatrix();
				}
				std::cin >> choice;
			}
			std::cout << "Do you want to continue to activate the explosion ? (y/ n) \n";
			std::cin >> choice;
			if (choice == 'y')
			{
				GetBoardRef() = explosion.applyEffects();
				SetIsUsedExplosion(true);
			}
		}
	}
}

//Obtinerea coordonatelor
void Game::getInputCoordinates(size_t& x, size_t& y, size_t& cardIndex) {
	std::cout << "x = "; std::cin >> x;
	std::cout << "y = "; std::cin >> y;
	std::cout << "index of the card = "; std::cin >> cardIndex;
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
			currentPlayer.AddToEliminatedCards(newCard);
			std::cout << currentPlayer.GetName() << " loses their turn.\n";
			return;
		}
	}
}



