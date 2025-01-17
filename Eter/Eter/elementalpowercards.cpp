#include "ElementalPowerCards.h"
using namespace eter;
#include <stdexcept>
#include <unordered_map>
#include <iostream>

namespace eter {
	void swap(elementalPowerCards& first, elementalPowerCards& second) noexcept
	{
		using std::swap;
		swap(first.m_power, second.m_power);
		swap(first.m_used, second.m_used);
	}
	std::ostream& operator<<(std::ostream& os, elementalPowerCards::powerAbility ability) {
		switch (ability) {
		case elementalPowerCards::powerAbility::controlledExplosion:
			os << "Controlled Explosion";
			break;
		case elementalPowerCards::powerAbility::destruction:
			os << "Destruction";
			break;
		case elementalPowerCards::powerAbility::flame:
			os << "Flame";
			break;
		case elementalPowerCards::powerAbility::fire:
			os << "Fire";
			break;
		case elementalPowerCards::powerAbility::ash:
			os << "ASH";
			break;
		case elementalPowerCards::powerAbility::spark:
			os << "Spark";
			break;
		case elementalPowerCards::powerAbility::squall:
			os << "Squall";
			break;
		case elementalPowerCards::powerAbility::gale:
			os << "Gale";
			break;
		case elementalPowerCards::powerAbility::hurricane:
			os << "Hurricane";
			break;
		case elementalPowerCards::powerAbility::gust:
			os << "Gust";
			break;
		case elementalPowerCards::powerAbility::mirage:
			os << "Mirage";
			break;
		case elementalPowerCards::powerAbility::storm:
			os << "Storm";
			break;
		case elementalPowerCards::powerAbility::tide:
			os << "Tide";
			break;
		case elementalPowerCards::powerAbility::mist:
			os << "Mist";
			break;
		case elementalPowerCards::powerAbility::wave:
			os << "Wave";
			break;
		case elementalPowerCards::powerAbility::whirlpool:
			os << "Whirlpool";
			break;
		case elementalPowerCards::powerAbility::blizzard:
			os << "Blizzard";
			break;
		case elementalPowerCards::powerAbility::waterfall:
			os << "Waterfall";
			break;
		case elementalPowerCards::powerAbility::support:
			os << "Support";
			break;
		case elementalPowerCards::powerAbility::earthQuake:
			os << "Earthquake";
			break;
		case elementalPowerCards::powerAbility::crumble:
			os << "Crumble";
			break;
		case elementalPowerCards::powerAbility::border:
			os << "Border";
			break;
		case elementalPowerCards::powerAbility::avalanche:
			os << "Avalanche";
			break;
		case elementalPowerCards::powerAbility::rock:
			os << "Rock";
			break;
		default:
			os << "Unknown Ability";
			break;
		}
		return os;
	}

	elementalPowerCards::elementalPowerCards(powerAbility power) :
		m_power{ power },
		m_used{ false }
	{
	}

	void elementalPowerCards::SetUsed(bool used)
	{
		m_used = used;
	}

	bool elementalPowerCards::GetUsed() const
	{
		return m_used;
	}

	void elementalPowerCards::SetAbility(powerAbility power)
	{
		m_power = power;
	}

	elementalPowerCards::powerAbility elementalPowerCards::GetAbility() const
	{
		return powerAbility();
	}
	void elementalPowerCards::activate(Game* game,Player& player, Player& opponent, Board& board)
	{
		if (m_used)
			throw std::runtime_error("The elemental power has already been used!\n");
		switch (m_power)
		{
		case eter::elementalPowerCards::powerAbility::controlledExplosion:
			std::cout << "Activating Controlled Explosion. The board explodes.\n";
			activateExplosion(game);
			break;
		case eter::elementalPowerCards::powerAbility::destruction:
			std::cout << "Activating Destruction. Remove from play the last card played by the opponent.\n";
			activateDestruction(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::flame:
			std::cout << "Activating Flame. Reveal an opponent’s Illusion.\n";
			activateFlame(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::fire:
			std::cout << "Activating Fire.Return to their owners' hands all visible cards of the same value.\n";
			activateFire(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::ash:
			std::cout << "Activating ASH. If one of your cards was removed from play, you can immediately play it again.\n";
			activateASH(player, board);
			break;
		case eter::elementalPowerCards::powerAbility::spark:
			std::cout << "Activating Spark. Take any of your cards that is covered by an opponent’s cards and play it onto a different space.\n";
			activateSpark(player,opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::squall:
			std::cout << "Activating Squall. Return to the opponent’s hand any one of his visible cards.\n";
			activateSquall(opponent, player, board);
			break;
		case eter::elementalPowerCards::powerAbility::gale:
			std::cout << "Activating Gale. Remove any cards that are covered by others.\n";
			activateGale(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::hurricane:
			std::cout << "Activating Hurricane. Move any one full row/column by one card.\n";
			activateHurricane(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::gust:
			std::cout << "Activating Gust. Move any card on the playing field onto a neighboring card of a lower value.\n";
			activateGust(board,player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::mirage:
			std::cout << "Activating Mirage. Exchange your Illusion with a different card from your hand.\n";
			activateMirage(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::storm:
			std::cout << "Activating Storm. Remove from play any stack of minimum 2 cards.\n";
			activateStorm(board, player, opponent);
			break;
		case eter::elementalPowerCards::powerAbility::tide:
			std::cout << "Activating Tide. Change positions of 2 different cards or stacks of cards.\n";
			activateTide(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::mist:
			std::cout << "Activating Mist. Play an Illusion again. \n";
			activateMist(player, board);
			break;
		case eter::elementalPowerCards::powerAbility::wave:
			std::cout << "Activating Wave. Move any card to the adjacent empty space, then play a card from your hand to this now empty space.\n";
			activateWave(board, player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::whirlpool:
			std::cout << "Activating WhirlPool. Move onto empty space two cards from different adjacent spaces in a straight line.\n";
			activateWhirlpool(board, player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::blizzard:
			std::cout << "Activating Blizzard.The opponent cannot play any cards onto the chosen row/column during his next turn.\n";
			activateBlizzard(board, player, opponent);
			break;
		case eter::elementalPowerCards::powerAbility::waterfall:
			std::cout << "Activating Waterfall. Move all cards in a chosen column into one stack at the bottom of that column.\n";
			activateWaterfall(board);
			break;
		case eter::elementalPowerCards::powerAbility::support:
			std::cout << "Activating Support. Value of a chosen card is increased by + 1.\n";
			activateSupport(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::earthQuake:
			std::cout << "Activating EarthQuake. Remove from play all visible ‘1’ cards.\n";
			activateEarthQuake(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::crumble:
			std::cout << "Activating Crumble. Value of a card is decreased by 1.\n";
			activateCrumble(board, player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::border:
			std::cout << "Activating Border.Place this card in any empty space on the playing field to establish the border of the play area.\n";
			activateBorder(board,  player);
			break;
		case eter::elementalPowerCards::powerAbility::avalanche:
			std::cout << "Activating Avalanche. Move two neighboring cards / stacs by one space.\n";
			activateAvalanche(board,player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::rock:
			std::cout << "Activating Rock. Cover any Illusion card with your card.\n";
			activateRock(board, player);
			break;
		default:
			throw std::invalid_argument("Unknown power!\n!");
			break;
		}
		m_used = true;
		std::cout << "Power activated successfully!\n";
	}

	void elementalPowerCards::activateExplosion(Game* game)
	{
		Explosion explosion(game->GetBoard().GetDimMax(), game->GetBoard());
		explosion.rotateExplosion();
		std::cout << "Do you want to continue to activate the explosion ? (y/ n) \n";
		char choice;
		std::cin >> choice;
		if (choice == 'y')
		{
			game->GetBoardRef() = explosion.applyEffects(game->GetPlayer1Ref(), game->GetPlayer2Ref());
			game->SetReturnedCards(explosion.GetReturnedCards());
			game->SetCountTurnForReturnedCards (1);
			game->SetIsUsedExplosion(true);
		}
	}

	void elementalPowerCards::activateDestruction(Player& player, Player& opponent, Board& board) {
		auto& opponentPlayedCards = opponent.GetPlayedCardsForPower();

		if (opponentPlayedCards.empty()) {
			std::cout << "The opponent has no played cards to remove.\n";
		}
		else
		{

			const auto& lastPlayedCardWithPos = opponentPlayedCards.back();
			const Card& lastCardPlayed = lastPlayedCardWithPos.first;
			size_t  x = lastPlayedCardWithPos.second.first;
			size_t  y = lastPlayedCardWithPos.second.second;

			std::cout << "Debug: Last card played by the opponent is value " << lastCardPlayed.GetValue() + 1 - 1
				<< " and color " << lastCardPlayed.GetColor() << " at position (" << (int)x << ", " << (int)y << ").\n";

			board.removeCard(x, y);
			opponentPlayedCards.pop_back();

			opponent.addToEliminatedCards(lastCardPlayed);

			std::cout << "Removed opponent's card with value " << lastCardPlayed.GetValue() + 1 - 1 << " and color " << lastCardPlayed.GetColor()
				<< " from position (" << (int)x << ", " << (int)y << ").\n";
		}
	}


	void elementalPowerCards::activateSquall(Player& opponent, Player& player, Board& board)
	{
		std::cout << " Return Opponent's Card to Hand\n";

		size_t row, col;
		bool validPosition{ false };

		while (!validPosition)
		{
			std::cout << "Enter the position (row, column) of the opponent's card to return to their hand: ";
			std::cin >> row >> col;

			if (!board.isValidPosition(row, col))
			{
				std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
				continue;
			}

			auto& cell{ board[{row, col}] };
			if (!cell.has_value() || cell->empty())
			{
				std::cout << "No card found at position (" << row << ", " << col << "). Try again.\n";
				continue;
			}

			if (cell.value().top().GetColor() != opponent.GetColor())
			{
				std::cout << "The top card at (" << row << ", " << col << ") is not an opponent's card. Try again.\n";
				continue;
			}

			validPosition = true;
		}

		auto& selectedCell{ board[{row, col}] };
		const Card cardToReturn{ selectedCell.value().top() };

		std::cout << "Card to return: Value=" << cardToReturn.GetValue() - 1 + 1
			<< ", Color=" << cardToReturn.GetColor() << "\n";

		selectedCell->pop();

		if (selectedCell->empty())
		{
			selectedCell.reset();
		}

		auto& opponentPlayedCards = opponent.GetPlayedCardsForPower();
		auto it = std::find_if(opponentPlayedCards.begin(), opponentPlayedCards.end(),
			[&](const std::pair<Card, std::pair<uint8_t, uint8_t>>& cardWithPos)
			{
				return cardWithPos.first == cardToReturn &&
					cardWithPos.second.first == row &&
					cardWithPos.second.second == col;
			});

		if (it != opponentPlayedCards.end())
		{
			opponentPlayedCards.erase(it);
			std::cout << "Card removed from opponent's played cards.\n";
		}

		
		opponent.addCardToHand(cardToReturn);

		std::cout << "Opponent's card with value " << cardToReturn.GetValue() - 1 + 1
			<< " and color " << cardToReturn.GetColor()
			<< " was returned to their hand from position (" << row << ", " << col << ").\n";
	}



	void elementalPowerCards::activateFire(Player& player, Player& opponent, Board& board) {
		std::cout << "Activate fire" << std::endl;

		std::vector<std::tuple<Card, size_t, size_t>> visibleCards;

 		for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i) {
			for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j) {
				auto& cellOpt = board[{i, j}];
				if (cellOpt.has_value() && !cellOpt->empty()) {
					const Card& topCard = cellOpt->top();
					if (topCard.GetPosition()) {    
						visibleCards.push_back({ topCard, i, j });
						std::cout << "Visible card at (" << i << ", " << j << ") with value "
							<< static_cast<int>(topCard.GetValue()) << std::endl;
					}
				}
			}
		}

		 
		if (visibleCards.size() < 2) {
			std::cout << "Not enough visible cards on the board.\n";
			return;
		}

		int chosenNumber = 0;

		 
		while (true) {
			std::cout << "Enter a number with at least two visible cards on the board: ";
			std::cin >> chosenNumber;

			size_t count = std::count_if(visibleCards.begin(), visibleCards.end(),
				[chosenNumber](const auto& cardInfo) {
					return std::get<0>(cardInfo).GetValue() == chosenNumber;
				});

			if (count >= 2) {
				std::cout << "You chose the number " << chosenNumber << " with " << count << " visible cards.\n";
				break;
			}
			else {
				std::cout << "Invalid choice. There are less than two visible cards with this number.\n";
			}
		}

		 
		for (auto it = visibleCards.begin(); it != visibleCards.end();) {
			const Card& card = std::get<0>(*it);
			size_t row = std::get<1>(*it);
			size_t col = std::get<2>(*it);

			if (card.GetValue() == chosenNumber) {
				board.removeCard(row, col);
				std::cout << "Removed card with value " << static_cast<int>(card.GetValue())
					<< " from position (" << row << ", " << col << ").\n";

				bool cardReturned = false;

 				for (auto& playerCard : player.GetPlayedCards()) {
					if (playerCard == card) {
						player.GetPlayedCards().erase(std::remove(player.GetPlayedCards().begin(),
							player.GetPlayedCards().end(), card),
							player.GetPlayedCards().end());
						player.addCardToHand(card);
						std::cout << "Returned card to player's hand.\n";
						cardReturned = true;
						break;
					}
				}

				if (!cardReturned) {
					for (auto& opponentCard : opponent.GetPlayedCards()) {
						if (opponentCard == card) {
							opponent.GetPlayedCards().erase(std::remove(opponent.GetPlayedCards().begin(),
								opponent.GetPlayedCards().end(), card),
								opponent.GetPlayedCards().end());
							opponent.addCardToHand(card);
							std::cout << "Returned card to opponent's hand.\n";
							cardReturned = true;
							break;
						}
					}
				}

				if (!cardReturned) {
					std::cout << "Card not found in either player's hand.\n";
				}

				it = visibleCards.erase(it);   
			}
			else {
				++it;
			}
		}

		std::cout << "Power activated successfully!" << std::endl;
	}




	void elementalPowerCards::activateASH(Player& player, Board& board)
	{
		auto& eliminatedCards = player.GetEliminatedCards();

		if (eliminatedCards.empty())
		{
			std::cout << "No eliminated cards to choose from!\n";
			return;
		}

		std::cout << "Choose a card to play from your eliminated cards:\n";
		for (size_t i = 0; i < eliminatedCards.size(); ++i)
		{
			std::cout << i + 1 << ". Card with value " << eliminatedCards[i].GetValue() - 1 + 1
				<< " and color " << eliminatedCards[i].GetColor() << '\n';
		}

		size_t choice;
		while (true)
		{
			std::cout << "Enter your choice (1-" << eliminatedCards.size() << "): ";
			std::cin >> choice;

			if (choice >= 1 && choice <= eliminatedCards.size())
				break;

			std::cout << "Invalid choice. Please try again.\n";
		}

		Card chosenCard = eliminatedCards[choice - 1];

		size_t row, col;
		while (true)
		{
			std::cout << "Enter the coordinates where you want to place the chosen card: ";
			std::cin >> row >> col;

			if (board.placeCard(row, col, chosenCard))
			{
				player.addPlayedCard(chosenCard);
				player.addPlayedCardForPower(chosenCard, row, col);
				std::cout << "Card with value " << chosenCard.GetValue()
					<< " and color " << chosenCard.GetColor()
					<< " has been placed back on the board at position (" << static_cast<int>(row)
					<< ", " << static_cast<int>(col) << ").\n";
				break;
			}
			else
			{
				std::cout << "The position to place the card is invalid! Please choose again.\n";
			}
		}

		eliminatedCards.erase(eliminatedCards.begin() + (choice - 1));
	}
	void elementalPowerCards::activateSpark(Player& player, Player& opponent, Board& board)
	{
		std::vector<std::tuple<Card, size_t, size_t>> coveredCards;
		for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i)
		{
			for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j)
			{
				auto& cellOpt = board[{i, j}];
				if (cellOpt.has_value() && !cellOpt->empty())
				{
					std::stack<Card> tempStack;
					bool foundCoveredCard = false;

					while (!cellOpt->empty())
					{
						Card topCard = cellOpt->top();
						cellOpt->pop();

						if (!tempStack.empty() && tempStack.top().GetColor() == opponent.GetColor() &&
							topCard.GetColor() == player.GetColor())
						{
							coveredCards.push_back({ topCard, i, j });
							foundCoveredCard = true;
						}

						tempStack.push(topCard);
					}

					while (!tempStack.empty())
					{
						cellOpt->push(tempStack.top());
						tempStack.pop();
					}
					if (foundCoveredCard)
					{
						continue;
					}
				}
			}
		}
		std::cout << "Covered cards found:\n";
		for (const auto& cardInfo : coveredCards)
		{
			const Card& card = std::get<0>(cardInfo);
			size_t row = std::get<1>(cardInfo);
			size_t col = std::get<2>(cardInfo);

			std::cout << "Card: Value = " << card.GetValue() + 1 - 1
				<< ", Color = " << card.GetColor()
				<< ", Position = (" << row << ", " << col << ")\n";
		}
		if (coveredCards.empty())
		{
			std::cout << "No cards of yours are covered by the opponent.\n";
			return;
		}

		int chosenValue = 0, chosenRow = -1, chosenCol = -1;
		while (true)
		{
			std::cout << "Enter the value, the row, and the column of the card you want to move: ";
			std::cin >> chosenValue >> chosenRow >> chosenCol;

			auto it = std::find_if(coveredCards.begin(), coveredCards.end(),
				[chosenValue, chosenRow, chosenCol](const auto& cardInfo) {
					return std::get<0>(cardInfo).GetValue() == chosenValue &&
						std::get<1>(cardInfo) == chosenRow &&
						std::get<2>(cardInfo) == chosenCol;
				});

			if (it != coveredCards.end())
			{
				std::cout << "You chose a card with value " << chosenValue << ".\n";
				break;
			}
			else
			{
				std::cout << "No card with this value is covered by the opponent. Please try again.\n";
			}
		}

		auto& cellOpt = board[{chosenRow, chosenCol}];
		Card selectedCard;

		if (cellOpt.has_value() && !cellOpt->empty())
		{
			std::stack<Card> tempStack;

			while (!cellOpt->empty())
			{
				Card topCard = cellOpt->top();
				cellOpt->pop();

				if (topCard.GetValue() == chosenValue && topCard.GetColor() == player.GetColor())
				{
					selectedCard = topCard;
					break;
				}

				tempStack.push(topCard);
			}

			while (!tempStack.empty())
			{
				cellOpt->push(tempStack.top());
				tempStack.pop();
			}
			player.removePlayedCardForPower(selectedCard, chosenRow, chosenCol);
			std::cout << "Card with value " << chosenValue << " removed from the original stack.\n";
		}

		size_t newX, newY;
		bool placedSuccessfully = false;
		do
		{
			std::cout << "Choose the new position (x y) to place the card: ";
			std::cin >> newX >> newY;

			placedSuccessfully = board.placeCard(newX, newY, selectedCard);

			if (!placedSuccessfully)
			{
				std::cout << "Please try again.\n";
			}
		} while (!placedSuccessfully);
		player.addPlayedCardForPower(selectedCard, newX, newY);
		std::cout << "Card moved to position (" << (int)newX << ", " << (int)newY << ").\n";
	}

	void elementalPowerCards::activateEarthQuake(Player& player, Player& opponent, Board& board)
	{
		for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i)
		{
			for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j)
			{
				auto& cellOpt = board[{i, j}];

				if (cellOpt.has_value() && !cellOpt->empty())
				{
					const Card& topCard = cellOpt->top();
					if (topCard.GetValue() == 1) 
					{
						Player* owner = nullptr;
						if (topCard.GetColor() == player.GetColor())
						{
							owner = &player;
						}
						else if (topCard.GetColor() == opponent.GetColor())
						{
							owner = &opponent;
						}

						if (owner)
						{
							owner->addToEliminatedCards(topCard);
							std::cout << "The card with value " << static_cast<int>(topCard.GetValue())
								<< " has been eliminated.\n";
						}
						board.removeCard(i, j);
					}
				}
			}
		}
	}

	void eter::elementalPowerCards::activateMist(Player& player, Board& board)
	{
 		bool hasIllusionOnBoard = false;
		size_t illusionRow = 0, illusionCol = 0;

		for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i) {
			for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j) {
				auto& cellOpt = board[{i, j}];
				if (cellOpt.has_value() && !cellOpt->empty()) {
					Card& topCard = cellOpt->top();
					if (topCard.GetColor() == player.GetColor() && !topCard.GetPosition()) {
						hasIllusionOnBoard = true;
						illusionRow = i;
						illusionCol = j;
						break;
					}
				}
			}
			if (hasIllusionOnBoard) break;
		}

 		if (hasIllusionOnBoard) {
			auto& illusionCell = board[{illusionRow, illusionCol}];
			if (illusionCell.has_value() && !illusionCell->empty()) {
				Card& illusionCard = illusionCell->top();
				illusionCard.SetPosition(true); 
				std::cout << "Your existing illusion at (" << illusionRow << ", " << illusionCol << ") has been revealed.\n";
			}
		}

 		auto& cardsInHand = player.GetCardsInHand();
		if (cardsInHand.empty()) {
			std::cout << "You have no cards in your hand to play as an illusion.\n";
			return;
		}

		std::cout << "Choose a card from your hand to play as an illusion:\n";
		for (size_t i = 0; i < cardsInHand.size(); ++i) {
			std::cout << i + 1 << ": Card with value " << static_cast<int>(cardsInHand[i].GetValue()) << "\n";
		}

		size_t chosenCardIndex;
		while (true) {
			std::cout << "Enter the index of the card to play: ";
			std::cin >> chosenCardIndex;
			if (chosenCardIndex >= 1 && chosenCardIndex <= cardsInHand.size()) {
				break;
			}
			else {
				std::cout << "Invalid choice. Try again.\n";
			}
		}

 		Card selectedCard = cardsInHand[chosenCardIndex - 1];
		selectedCard.SetPosition(false);  
		cardsInHand.erase(cardsInHand.begin() + (chosenCardIndex - 1));

 		size_t row, col;
		while (true) {
			std::cout << "Enter the coordinates to place the new illusion (row, column): ";
			std::cin >> row >> col;
			if (board.isValidPosition(row, col) && (!board[{row, col}].has_value() || board[{row, col}]->empty())) {
				break;
			}
			else {
				std::cout << "Invalid position or position already occupied. Try again.\n";
			}
		}

		auto& cell = board[{row, col}];
		if (!cell.has_value()) {
			cell.emplace();
		}
		cell->push(selectedCard);
		player.addPlayedCard(selectedCard);

		std::cout << "Placed illusion card with value " << static_cast<int>(selectedCard.GetValue()) << " at position ("
			<< row << ", " << col << ").\n";
	}

void elementalPowerCards::activateGale(Player& player, Player& opponent, Board& board)
{
	for (size_t row = board.GetIndexLineMin(); row <= board.GetIndexLineMax(); ++row)
	{
		for (size_t col = board.GetIndexColMin(); col <= board.GetIndexColMax(); ++col)
		{
			auto& cellOpt = board[{row, col}];
			if (cellOpt.has_value())
			{
				auto& cell = cellOpt.value();

				if (cell.size() > 1)
				{
					Card topCard = cell.top();
					cell.pop();

					std::stack<Card> tempStack;
					while (!cell.empty())
					{
						Card currentCard = cell.top();
						cell.pop();

						if (currentCard.GetColor() == player.GetColor())
						{
							player.addCardToHand(currentCard);
							auto& playedCards = player.GetPlayedCards();
							playedCards.erase(
								std::remove(playedCards.begin(), playedCards.end(), currentCard),
								playedCards.end()
							);
							std::cout << "The card with the value " << currentCard.GetValue() + 1 - 1 << " returned to the player's hand.\n";
						}
						else
						{
							opponent.addCardToHand(currentCard);
							auto& playedCards = opponent.GetPlayedCards();
							playedCards.erase(
								std::remove(playedCards.begin(), playedCards.end(), currentCard),
								playedCards.end()
							);
							std::cout << "The card with the value " << currentCard.GetValue() + 1 - 1 << " returned to the opponent's hand.\n";
						}

						tempStack.push(currentCard);
					}
					while (!tempStack.empty())
					{
						cell.push(tempStack.top());
						tempStack.pop();
					}
					cell.push(topCard);
				}
			}
		}
	}
}

void elementalPowerCards::activateGust(Board& board, Player& player, Player& opponent)
{
	size_t selectedRow, selectedCol;
	bool validCardSelected = false;
	std::optional<std::stack<Card>> selectedStack;

	while (!validCardSelected)
	{
		std::cout << "Select a card (row, column): ";
		std::cin >> selectedRow >> selectedCol;

		if (selectedRow < board.GetIndexLineMin() || selectedRow > board.GetIndexLineMax() ||
			selectedCol < board.GetIndexColMin() || selectedCol > board.GetIndexColMax())
		{
			std::cout << "Invalid position. Try again.\n";
			continue;
		}

		selectedStack = board[{selectedRow, selectedCol}];
		if (!selectedStack.has_value() || selectedStack->empty())
		{
			std::cout << "No visible card at this position. Try again.\n";
			continue;
		}

		validCardSelected = true;
	}

	bool placedCard = false;
	size_t finalRow = selectedRow, finalCol = selectedCol;

	while (!placedCard)
	{
		std::cout << "Select the direction where you want to move the card: U(up), D(down), L(left), R(right): ";
		char direction;
		std::cin >> direction;
		switch (direction)
		{
		case 'U': finalRow = selectedRow - 1; finalCol = selectedCol; break;
		case 'D': finalRow = selectedRow + 1; finalCol = selectedCol; break;
		case 'L': finalRow = selectedRow; finalCol = selectedCol - 1; break;
		case 'R': finalRow = selectedRow; finalCol = selectedCol + 1; break;
		default:
			std::cout << "Invalid direction. Try again.\n";
			continue;
		}
		if (finalRow < board.GetIndexLineMin() || finalRow > board.GetIndexLineMax() ||
			finalCol < board.GetIndexColMin() || finalCol > board.GetIndexColMax())
		{
			std::cout << "Invalid position. Try again.\n";
			continue;
		}

		auto& finalStack = board[{finalRow, finalCol}];
		if (finalStack.has_value() && !finalStack->empty() &&
			finalStack->top().GetValue() < selectedStack->top().GetValue())
		{
			placedCard = true;
		}
		else
			std::cout << "Invalid move. The card at the target position must have a lower value. Try again.\n";
	}
	board.placeCard(finalRow, finalCol, selectedStack->top());
	if (selectedStack->top().GetColor() == player.GetColor())
	{
		player.removePlayedCardForPower(selectedStack->top(), selectedRow, selectedCol);
		player.addPlayedCardForPower(selectedStack->top(), finalRow, finalCol);
	}
	else
	{
		opponent.removePlayedCardForPower(selectedStack->top(), selectedRow, selectedCol);
		opponent.addPlayedCardForPower(selectedStack->top(), finalRow, finalCol);
	}
	board.removeCard(selectedRow, selectedCol);
}


void elementalPowerCards::activateTide(Player& player, Player& opponent, Board& board)
{
	std::cout << "Activate tide" << std::endl;

	std::vector<std::tuple<size_t, size_t>> visibleCardPositions;

	for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i) {
		for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j) {
			auto& cellOpt = board[{i, j}];
			if (cellOpt.has_value() && !cellOpt->empty()) {
				visibleCardPositions.push_back({ i, j });
				std::cout << "Stack of cards at (" << i << ", " << j << ") detected." << std::endl;
			}
		}
	}

	if (visibleCardPositions.size() < 2)
	{
		std::cout << "Not enough stacks of cards on the board to swap positions.\n";
		return;
	}

	size_t firstRow, firstCol, secondRow, secondCol;

	std::cout << "Choose the first stack to swap (row and column):\n";
	while (true)
	{
		std::cin >> firstRow >> firstCol;
		if (std::find(visibleCardPositions.begin(), visibleCardPositions.end(), std::make_tuple(firstRow, firstCol)) != visibleCardPositions.end()) {
			break;
		}
		else {
			std::cout << "Invalid position. Please choose a valid stack.\n";
		}
	}

	std::cout << "Choose the second stack to swap (row and column):\n";
	while (true) {
		std::cin >> secondRow >> secondCol;
		if (std::find(visibleCardPositions.begin(), visibleCardPositions.end(), std::make_tuple(secondRow, secondCol)) != visibleCardPositions.end() &&
			!(firstRow == secondRow && firstCol == secondCol)) {
			break;
		}
		else {
			std::cout << "Invalid position. Please choose a valid and different stack.\n";
		}
	}

	// Swap the stacks of cards
	auto firstStack = board[{firstRow, firstCol}];
	auto secondStack = board[{secondRow, secondCol}];

	board[{firstRow, firstCol}] = secondStack;
	board[{secondRow, secondCol}] = firstStack;

	std::cout << "Swapped stacks between positions (" << firstRow << ", " << firstCol << ") and ("
		<< secondRow << ", " << secondCol << ").\n";

	std::cout << "Tide power activated successfully!" << std::endl;
}

void elementalPowerCards::activateWave(Board& board, Player& player, Player& opponent) {
	size_t row, col;

	while (true) {
		std::cout << "Enter the coordinates of the stack to move (row, column): ";
		std::cin >> row >> col;

		if (board.isValidPosition(row, col) && board[{row, col}].has_value()) {
			break;
		}
		std::cout << "Invalid position. Try again.\n";
	}

	auto& stack = board[{row, col}];

	size_t toRow, toCol;
	bool isToValid = false;

	while (!isToValid) {
		std::cout << "Enter the destination position (row, column): ";
		std::cin >> toRow >> toCol;

		if (!board.isValidPosition(toRow, toCol)) {
			std::cout << "Invalid position. Try again.\n";
			continue;
		}
		if (!board.isAdjacentToOccupiedSpace(toRow, toCol)) {
			std::cout << "The position is not adjacent to any occupied space. Try again.\n";
			continue;
		}
		if (board[{toRow, toCol}].has_value()) {
			std::cout << "Destination position is not empty. Try again.\n";
			continue;
		}
		isToValid = true;
	}

	auto& destCell = board[{toRow, toCol}];
	destCell = std::move(stack);

	while (!stack->empty()) {
		Card topCard = stack->top();
		stack->pop();

		if (topCard.GetColor() == player.GetColor()) {
			player.removePlayedCardForPower(topCard, row, col);
			player.addPlayedCardForPower(topCard, toRow, toCol);
		}
		else {
			opponent.removePlayedCardForPower(topCard, row, col);
			opponent.addPlayedCardForPower(topCard, toRow, toCol);
		}
	}
	stack.reset();
	std::cout << "Stack moved from (" << row << ", " << col << ") to (" << toRow << ", " << toCol << ").\n";

	std::cout << "Choose a card from your hand:\n";
	player.printCardsInHand();
	size_t cardIndex = 0;
	std::cin >> cardIndex;

	const Card& selectedCard = player.GetCardsInHand().at(cardIndex - 1);
	board[{row, col}] = std::stack<Card>{};
	board[{row, col}]->push(selectedCard);
	player.addPlayedCardForPower(selectedCard, row, col);
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + (cardIndex - 1));
}

void elementalPowerCards::activateStorm(Board& board, Player& player, Player& opponent)
{
	size_t row, col;
	while (true) {
		std::cout << "Enter the coordinates of the stack you want to remove (x, y): ";
		std::cin >> row >> col;
		auto& stackOpt = board[{row, col}];
		if (stackOpt.has_value() && stackOpt->size() >= 2) 
		{
			while (!stackOpt->empty())
			{
				Card topCard = stackOpt->top();
				stackOpt->pop();

				if (topCard.GetColor() == player.GetColor())
				{
					player.addToEliminatedCards(topCard);
					player.removePlayedCardForPower(topCard, row, col);
				}
				else if (topCard.GetColor() == opponent.GetColor())
				{
					opponent.addToEliminatedCards(topCard);
					opponent.removePlayedCardForPower(topCard, row, col);
				}

				std::cout << "Card with value " << topCard.GetValue()+1-1
					<< " on position " << row << " " << col
					<< " has been removed.\n";
			}
			stackOpt.reset();
			break; 
		}
		else {
			std::cout << "Invalid stack! The stack must exist and have a size >= 2. Try again.\n";
		}
	}
}


void elementalPowerCards::activateWaterfall(Board& board)
{
	char choice;
	std::cout << "Choose 'R' for row or 'C' for column: ";
	std::cin >> choice;
	size_t number;
	while (true)
	{
		bool validChoice = false;
		std::cout << "Choose the line/column number you want to move:";
		std::cin >> number;
		if (choice == 'R' && board.countOccupiedCellsOnRow(number) < 3) {
			std::cout << "The chosen line must have at least 3 occupied positions.Try again.\n";
			continue;
		}
		if (choice == 'C' && board.countOccupiedCellsOnColumn(number) < 3) {
			std::cout << "The chosen line must have at least 3 occupied positions.Try again.\n";
			continue;
		}
		if (validChoice == false) {
			break;
		}
	}
	size_t toRow, toCol;
	char direction;
	std::vector<Card>movedCards;
	if (choice == 'C')
	{
		std::cout << "Choose the direction you want to move the column: U(up),D(down): ";
		std::cin >> direction;
		if (direction == 'U')
		{
			toRow = board.GetIndexLineMin();
			toCol = number;
			if (!board[{toRow, toCol}].has_value())
				toRow++;
			for (size_t i = toRow + 1; i <= board.GetIndexLineMax(); ++i)
			{
				auto& cell = board[{i, number}];
				while (!cell->empty())
				{
					board[{toRow, toCol}]->push(cell->top());
					cell->pop();
				}
				cell.reset();
			}
		}
		else if (direction == 'D')
		{
			toRow = board.GetIndexLineMax();
			toCol = number;
			if (!board[{toRow, toCol}].has_value())
				toRow--;
			for (size_t i = toRow - 1; i >= board.GetIndexLineMin(); --i)
			{
				auto& cell = board[{i, number}];
				while (!cell->empty())
				{
					board[{toRow, toCol}]->push(cell->top());
					cell->pop();
				}
				cell.reset();
			}
		}
	}
	else if (choice == 'R')
	{
		std::cout << "Choose the direction you want to move the row: L(left),R(right): ";
		std::cin >> direction;
		if (direction == 'L')
		{
			toCol = board.GetIndexColMin();
			toRow = number;
			if (!board[{toRow, toCol}].has_value())
				toCol++;
			for (size_t i = toCol + 1; i <= board.GetIndexColMax(); ++i)
			{
				auto& cell = board[{number, i}];
				while (!cell->empty())
				{
					board[{toRow, toCol}]->push(cell->top());
					cell->pop();
				}
				cell.reset();
			}
		}
		else if (direction == 'R')
		{
			toCol = board.GetIndexColMax();
			toRow = number;
			if (!board[{toRow, toCol}].has_value())
				toCol--;
			for (size_t i = toCol - 1; i >= board.GetIndexColMin(); --i)
			{
				auto& cell = board[{ number, i}];
				while (!cell->empty())
				{
					board[{toRow, toCol}]->push(cell->top());
					cell->pop();
				}
				cell.reset();
			}
		}
	}
}

void elementalPowerCards::activateWhirlpool(Board& board, Player& player, Player& opponent)
{
	std::cout << "Move onto empty space two cards from different adjacent spaces in a straight line.\n ";
	size_t row1, col1, row2, col2;
	bool firstStackValid = false;
	bool secondStackValid = false;

	while (true) {
		if (!firstStackValid) {
			std::cout << "Enter the coordinates of the first card (row col): ";
			std::cin >> row1 >> col1;

			if (board.isValidPosition(row1, col1) && board[{row1, col1}].has_value()) {
				firstStackValid = true;
			}
			else {
				std::cout << "Invalid position for the first card. Try again.\n";
				continue;
			}
		}

		if (!secondStackValid) {
			std::cout << "Enter the coordinates of the second card (row col): ";
			std::cin >> row2 >> col2;

			if (board.isValidPosition(row2, col2) && board[{row2, col2}].has_value()) {
				secondStackValid = true;
			}
			else {
				std::cout << "Invalid position for the second card. Try again.\n";
				continue;
			}
		}

		if (firstStackValid && secondStackValid) {
			if (((row1 == row2 && std::abs(static_cast<int>(col1) - static_cast<int>(col2)) == 2) ||
				(col1 == col2 && std::abs(static_cast<int>(row1) - static_cast<int>(row2)) == 2)) &&
				board[{row1, col1}]->size() == 1 && board[{row2, col2}]->size() == 1) {
				break;
			}
			else {
				std::cout << "Cards must be individual on the same line/column and have an empty space between them. Try again.\n";
				firstStackValid = false;
				secondStackValid = false;
			}
		}
	}

	size_t toRow, toCol;
	if (row1 == row2) {
		toRow = row1;
		toCol = std::min(col1, col2) + 1;
	}
	else {
		toCol = col1;
		toRow = std::min(row1, row2) + 1;
	}

	Card firstCard = board[{row1, col1}]->top();
	Card secondCard = board[{row2, col2}]->top();

	if (firstCard.GetColor() == player.GetColor()) {
		player.addPlayedCardForPower(firstCard, toRow, toCol);
		player.removePlayedCardForPower(firstCard, row1, col1);
	}
	else {
		opponent.addPlayedCardForPower(firstCard, toRow, toCol);
		opponent.removePlayedCardForPower(firstCard, row2, col2);
	}

	if (secondCard.GetColor() == player.GetColor()) {
		player.addPlayedCardForPower(secondCard, toRow, toCol);
		player.removePlayedCardForPower(secondCard, row1, col1);
	}
	else {
		opponent.addPlayedCardForPower(secondCard, toRow, toCol);
		opponent.removePlayedCardForPower(secondCard, row2, col2);
	}

	if (firstCard.GetValue() > secondCard.GetValue()) {
		board[{toRow, toCol}] = std::move(board[{row2, col2}]);
		board[{toRow, toCol}]->push(firstCard);
		board[{row2, col2}].reset();
		board.removeCard(row1, col1);
	}
	else if (firstCard.GetValue() < secondCard.GetValue()) {
		board[{toRow, toCol}] = std::move(board[{row1, col1}]);
		board[{toRow, toCol}]->push(secondCard);
		board[{row1, col1}].reset();
		board.removeCard(row2, col2);

	}
	else {
		std::cout << "Which card do you want to place first?" << std::endl
			<< "1. " << firstCard.GetColor() << " " << firstCard.GetValue() << std::endl
			<< "2. " << secondCard.GetColor() << " " << secondCard.GetValue() << std::endl;

		int choice;
		std::cin >> choice;
		if (choice == 1) {
			board[{toRow, toCol}] = std::move(board[{row1, col1}]);
			board[{toRow, toCol}]->push(secondCard);
			board[{row1, col1}].reset();
			board.removeCard(row2, col2);
		}
		else {
			board[{toRow, toCol}] = std::move(board[{row2, col2}]);
			board[{toRow, toCol}]->push(firstCard);
			board[{row2, col2}].reset();
			board.removeCard(row1, col1);
		}
	}
}

void elementalPowerCards::activateFlame(Player& player, Player& opponent, Board& board) {
	std::cout << "Activate flame" << std::endl;

	std::vector<std::tuple<Card*, size_t, size_t>> illusionCards;

	for (size_t i = board.GetIndexLineMin(); i <= board.GetIndexLineMax(); ++i) {
		for (size_t j = board.GetIndexColMin(); j <= board.GetIndexColMax(); ++j) {
			auto& cellOpt = board[{i, j}];
			if (cellOpt.has_value() && !cellOpt->empty()) {
				Card& topCard = cellOpt->top();
				if (!topCard.GetPosition() && topCard.GetColor() == opponent.GetColor()) {
					illusionCards.push_back({ &topCard, i, j });
					std::cout << "Found illusion card at (" << i << ", " << j << ").\n";
				}
			}
		}
	}

	if (illusionCards.empty()) {
		std::cout << "No illusion cards played by the opponent  found on the board.\n";
	}
	else
	{
		auto [illusionCard, row, col] = illusionCards.front();
		illusionCard->SetPosition(true);
		std::cout << "Revealed illusion card at (" << row << ", " << col << ").\n";
	}

	auto& cardsInHand = player.GetCardsInHand();

	if (cardsInHand.empty())
	{
		std::cout << "No cards in hand to place on the board.\n";
		return;
	}

	std::cout << "Choose a card from your hand to place: \n";
	for (size_t i = 0; i < cardsInHand.size(); ++i) {
		const Card& card = cardsInHand[i];
		std::cout << i + 1 << ": Card with value " << static_cast<int>(card.GetValue()) << "\n";
	}

	size_t chosenIndex;
	while (true) {
		std::cout << "Enter the index of the card to place: ";
		std::cin >> chosenIndex;
		if (chosenIndex >= 1 && chosenIndex <= cardsInHand.size()) {
			break;
		}
		else {
			std::cout << "Invalid choice. Try again.\n";
		}
	}

	Card selectedCard = cardsInHand[chosenIndex - 1];
	cardsInHand.erase(cardsInHand.begin() + (chosenIndex - 1));

	size_t targetRow, targetCol;
	while (true) {
		std::cout << "Enter the row and column to place the card: ";
		std::cin >> targetRow >> targetCol;
		if (board.isValidPosition(targetRow, targetCol) && (!board[{targetRow, targetCol}].has_value() || board[{targetRow, targetCol}]->empty())) {
			break;
		}
		else {
			std::cout << "Invalid position. Try again.\n";
		}
	}

	auto& cell = board[{targetRow, targetCol}];
	if (!cell.has_value()) {
		cell.emplace();
	}
	cell->push(selectedCard);
	std::cout << "Placed card with value " << static_cast<int>(selectedCard.GetValue()) << " at ("
		<< targetRow << ", " << targetCol << ").\n";

	std::cout << "Flame power activated successfully!" << std::endl;
}
void elementalPowerCards::activateHurricane(Player& player, Player& opponent, Board& board) {
	std::cout << "Activate hurricane" << std::endl;

	size_t rowOrCol;
	bool isRow;

 	while (true) 
	{
		std::cout << "Do you want to shift a row or a column? (0 for row, 1 for column): ";
		std::cin >> rowOrCol;
		if (rowOrCol == 0 || rowOrCol == 1) {
			isRow = (rowOrCol == 0);
			break;
		}
		std::cout << "Invalid choice. Please enter 0 for row or 1 for column.\n";
	}

	size_t index;
	bool validSelection = false;

 	while (!validSelection) {
		std::cout << "Enter the " << (isRow ? "row" : "column") << " number to shift: ";
		std::cin >> index;

		if ((isRow && index >= board.GetIndexLineMin() && index <= board.GetIndexLineMax()) ||
			(!isRow && index >= board.GetIndexColMin() && index <= board.GetIndexColMax())) {
			validSelection = true;
		}
		else {
			std::cout << "Invalid choice. Please enter a valid " << (isRow ? "row" : "column") << " index within the board limits.\n";
		}
	}

 	bool isFullyOccupied = isRow
		? (board.countOccupiedCellsOnRow(index) == (board.GetIndexColMax() - board.GetIndexColMin() + 1))
		: (board.countOccupiedCellsOnColumn(index) == (board.GetIndexLineMax() - board.GetIndexLineMin() + 1));

 	std::cout << "Occupied cells in " << (isRow ? "row" : "column") << " " << index << ": "
		<< (isRow ? board.countOccupiedCellsOnRow(index) : board.countOccupiedCellsOnColumn(index))
		<< " (needed: "
		<< (isRow ? (board.GetIndexColMax() - board.GetIndexColMin() + 1)
			: (board.GetIndexLineMax() - board.GetIndexLineMin() + 1))
		<< ")\n";

	if (!isFullyOccupied) {
		std::cout << "The " << (isRow ? "row" : "column") << " is not fully occupied and cannot be shifted.\n";
		return;
	}

	int direction;
	while (true) {
		std::cout << "Enter shift direction (1 for forward, -1 for backward): ";
		std::cin >> direction;
		if (direction == 1 || direction == -1) {
			break;
		}
		std::cout << "Invalid direction. Please enter 1 for forward or -1 for backward.\n";
	}

	std::vector<Card> returnedCards;

 	if (isRow) {
		returnedCards = (direction == 1)
			? board.shiftRowForward(index)
			: board.shiftRowBackward(index);
	}
	else {
		returnedCards = (direction == 1)
			? board.shiftColumnForward(index)
			: board.shiftColumnBackward(index);
	}

 	for (const auto& card : returnedCards) {
		if (card.GetColor() == player.GetColor()) {
			player.addCardToHand(card);
		}
		else {
			opponent.addCardToHand(card);
		}
	}

	std::cout << "The " << (isRow ? "row" : "column") << " has been shifted successfully." << std::endl;
}


void elementalPowerCards::activateMirage( Board& board, Player& player) {
	std::cout << "Activate mirage" << std::endl;

 	bool illusionFound = false;
	size_t illusionRow = 0, illusionCol = 0;
	Card* illusionCard = nullptr;

	for (size_t row = board.GetIndexLineMin(); row <= board.GetIndexLineMax(); ++row) {
		for (size_t col = board.GetIndexColMin(); col <= board.GetIndexColMax(); ++col) {
			if (!board.isValidPosition(row, col)) {
				continue;
			}

			auto& cell = board[{row, col}];
			if (cell.has_value() && !cell->empty()) {
				Card& topCard = cell->top();
				if (!topCard.GetPosition() && topCard.GetColor() == player.GetColor()) {
					illusionFound = true;
					illusionRow = row;
					illusionCol = col;
					illusionCard = &topCard;
					break;
				}
			}
		}
		if (illusionFound) break;
	}

	if (!illusionFound) {
		std::cout << "No illusion found on the board to replace.\n";
		return;
	}

 	auto& illusionCell = board[{illusionRow, illusionCol}];
	if (!illusionCell.has_value() || illusionCell->empty()) {
		std::cout << "Error: Illusion cell is invalid or empty.\n";
		return;
	}

	illusionCell->pop();  
	illusionCard->SetPosition(true); 
	illusionCard->SetColor(player.GetColor()); 
	player.addCardToHand(*illusionCard);

	std::cout << "Your illusion at position (" << illusionRow << ", " << illusionCol << ") has been returned to your hand as a normal card with the player's color.\n";

 	auto& cardsInHand = player.GetCardsInHand();
	if (cardsInHand.empty()) {
		std::cout << "You have no cards in hand to play as a new illusion.\n";
		return;
	}

	std::cout << "Choose a card from your hand to play as a new illusion:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i) {
		std::cout << i + 1 << ": Card with value " << static_cast<int>(cardsInHand[i].GetValue()) << "\n";
	}

	size_t selectedCardIndex;
	while (true) {
		std::cout << "Enter the index of the card to use: ";
		std::cin >> selectedCardIndex;
		if (selectedCardIndex >= 1 && selectedCardIndex <= cardsInHand.size()) {
			break;
		}
		std::cout << "Invalid selection. Try again.\n";
	}

	Card newIllusion = cardsInHand[selectedCardIndex - 1];
	newIllusion.SetPosition(false);  
	newIllusion.SetColor(player.GetColor());  
	cardsInHand.erase(cardsInHand.begin() + (selectedCardIndex - 1));

 	if (!illusionCell.has_value()) {
		illusionCell.emplace();
	}

	illusionCell->push(newIllusion);
	player.addPlayedCard(newIllusion);

	std::cout << "Placed new illusion card with value " << static_cast<int>(newIllusion.GetValue())
		<< " at position (" << illusionRow << ", " << illusionCol << ").\n";
	std::cout << "Mirage power activated successfully!" << std::endl;
}


void eter::elementalPowerCards::activateBlizzard(Board& board, Player& player, Player& opponent)
{
	char choice;
	std::cout << "Do you want to block a row (R) or a column (C)? ";
	std::cin >> choice;
	size_t lineNumber;
	if (choice == 'R')
		std::cout << "Enter the row you want to block: ";
	else
		std::cout << "Enter the column you want to block: ";
	std::cin >> lineNumber;
	board.setBlockedLine(lineNumber, choice);
	if (choice == 'R')
		std::cout << "You blocked the row with number " << lineNumber;
	else
		std::cout << "You blocked the column with number " << lineNumber;
}

void eter::elementalPowerCards::activateSupport(Board& board, Player& player)
{
	size_t row, col;
	while (true)
	{
		std::cout << "Enter the position (row, col) of a card with value 1/2/3: ";
		std::cin >> row >> col;

		if (!board.isValidPosition(row, col))
		{
			std::cout << "Invalid position. Try again.\n";
			continue;
		}

		auto& cell = board[{row, col}];
		if (!cell.has_value())
		{
			std::cout << "No card at this position. Try again.\n";
			continue;
		}
		if (cell->top().GetColor() != player.GetColor())
		{
			std::cout << "The card is not yours. Try again.\n";
			continue;
		}
		if (cell->top().GetValue() < 1 || cell->top().GetValue() > 3)
		{
			std::cout << "The value of the card is not correct. Try again.\n";
			continue;
		}
		break;
	}
	player.removePlayedCardForPower(board[{row, col}]->top(), row, col);
	uint8_t value;
	value = board[{row, col}]->top().GetValue();
	++value;
	board[{row, col}]->top().SetValue(value);
	player.addPlayedCardForPower(board[{row, col}]->top(), row, col);
	std::cout << "The value of the card at position " << row << " and " << col << " increased by 1.\n";
}

void eter::elementalPowerCards::activateCrumble(Board& board, Player& player, Player& opponent)
{
	size_t row, col;
	while (true)
	{
		std::cout << "Enter the position (row, col) of a card with value 2/3/4: ";
		std::cin >> row >> col;

		if (!board.isValidPosition(row, col))
		{
			std::cout << "Invalid position. Try again.\n";
			continue;
		}

		auto& cell = board[{row, col}];
		if (!cell.has_value())
		{
			std::cout << "No card at this position. Try again.\n";
			continue;
		}
		if (cell->top().GetColor() != opponent.GetColor())
		{
			std::cout << "The card is not your opponent's. Try again.\n";
			continue;
		}
		if (cell->top().GetValue() < 2 || cell->top().GetValue() > 4)
		{
			std::cout << "The value of the card is not correct. Try again.\n";
			continue;
		}
		break;
	}
	opponent.removePlayedCardForPower(board[{row, col}]->top(), row, col);
	uint8_t value;
	value = board[{row, col}]->top().GetValue();
	--value;
	board[{row, col}]->top().SetValue(value);
	opponent.addPlayedCardForPower(board[{row, col}]->top(), row, col);
	std::cout << "The value of the card at position " << row << " and " << col << " decreased by 1.\n";
}
void eter::elementalPowerCards::activateRock(Board& board, Player& player)
{
 	std::vector<std::pair<size_t, size_t>> illusionPositions;

	for (size_t row = board.GetIndexLineMin(); row <= board.GetIndexLineMax(); ++row) {
		for (size_t col = board.GetIndexColMin(); col <= board.GetIndexColMax(); ++col) {
			auto& cellOpt = board[{row, col}];
			if (cellOpt.has_value() && !cellOpt->empty()) {
				Card& topCard = cellOpt->top();
				if (!topCard.GetPosition()) {  
					illusionPositions.emplace_back(row, col);
				}
			}
		}
	}

 	if (illusionPositions.empty()) {
		std::cout << "No Illusion cards found on the board. ROCK action cancelled.\n";
		return;
	}

 	std::cout << "Select an Illusion card to cover from the following positions:\n";
	for (size_t i = 0; i < illusionPositions.size(); ++i) {
		std::cout << i + 1 << ": Row " << illusionPositions[i].first
			<< ", Column " << illusionPositions[i].second << "\n";
	}

	size_t selectedPositionIndex;
	while (true) {
		std::cout << "Enter the index of the Illusion card to cover: ";
		std::cin >> selectedPositionIndex;
		if (selectedPositionIndex >= 1 && selectedPositionIndex <= illusionPositions.size()) {
			break;
		}
		std::cout << "Invalid selection. Try again.\n";
	}

	auto [selectedRow, selectedCol] = illusionPositions[selectedPositionIndex - 1];

 	auto& cardsInHand = player.GetCardsInHand();
	if (cardsInHand.empty()) {
		std::cout << "You have no cards in your hand to cover the Illusion card.\n";
		return;
	}

	std::cout << "Select a card from your hand to cover the Illusion card:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i) {
		std::cout << i + 1 << ": Card with value " << static_cast<int>(cardsInHand[i].GetValue()) << "\n";
	}

	size_t chosenCardIndex;
	while (true) {
		std::cout << "Enter the index of the card to use: ";
		std::cin >> chosenCardIndex;
		if (chosenCardIndex >= 1 && chosenCardIndex <= cardsInHand.size()) {
			break;
		}
		std::cout << "Invalid selection. Try again.\n";
	}

 	Card selectedCard = cardsInHand[chosenCardIndex - 1];
	cardsInHand.erase(cardsInHand.begin() + (chosenCardIndex - 1));

	auto& cellOpt = board[{selectedRow, selectedCol}];
	if (!cellOpt.has_value()) {
		cellOpt.emplace();
	}
	cellOpt->push(selectedCard);

	player.addPlayedCard(selectedCard);

	std::cout << "Covered the Illusion card at (" << selectedRow << ", " << selectedCol << ") with a card of value "
		<< static_cast<int>(selectedCard.GetValue()) << " from your hand.\n";
}



void elementalPowerCards::activateAvalanche(Board& board, Player& player, Player& opponent)
{
	size_t row1, col1, row2, col2;
	bool firstStackValid = false;
	bool secondStackValid = false;

	while (true) {
		if (!firstStackValid) {
			std::cout << "Enter the coordinates of the first stack (row col): ";
			std::cin >> row1 >> col1;

			if (board.isValidPosition(row1, col1) && board[{row1, col1}].has_value()) {
				firstStackValid = true;
			}
			else {
				std::cout << "Invalid position for the first stack. Try again.\n";
				continue;
			}
		}

		if (!secondStackValid) {
			std::cout << "Enter the coordinates of the second stack (row col): ";
			std::cin >> row2 >> col2;

			if (board.isValidPosition(row2, col2) && board[{row2, col2}].has_value()) {
				secondStackValid = true;
			}
			else {
				std::cout << "Invalid position for the second stack. Try again.\n";
				continue;
			}
		}
		if (firstStackValid && secondStackValid) {
			if ((row1 == row2 && std::abs(static_cast<int>(col1) - static_cast<int>(col2)) == 1) ||
				(col1 == col2 && std::abs(static_cast<int>(row1) - static_cast<int>(row2)) == 1)) {
				break;
			}
			else {
				std::cout << "Stacks must be on the same row/column or adjacent. Try again.\n";
				firstStackValid = false;
				secondStackValid = false;
			}
		}
	}
	while (true) {
		std::cout << "Choose the direction to an empty space where you want to shift the stacks: L(left), R(right), U(up), D(down):";
		char direction;
		std::cin >> direction;
		size_t toRow, toCol;
		bool validMove = false;

		if (direction == 'L') {
			if (row1 != row2) {
				std::cout << "You can't shift the stacks in the left direction. Try again.\n";
			}
			else {
				toRow = row1;
				toCol = std::min(col1, col2) - 1;
				auto& destCell = board[{toRow, toCol}];
				if (destCell.has_value()) {
					std::cout << "The space that the first card moves onto must be empty. Try again.\n";
				}
				else {
					auto& firstCell = (col1 < col2) ? board[{row1, col1}] : board[{row2, col2}];
					auto& secondCell = (col1 < col2) ? board[{row2, col2}] : board[{row1, col1}];

					destCell = std::move(firstCell);
					firstCell.reset();
					firstCell = std::move(secondCell);
					secondCell.reset();
					std::cout << "The stacks have been shifted to the left.\n";
					validMove = true;
				}
			}
		}
		else if (direction == 'R') {
			if (row1 != row2) {
				std::cout << "You can't shift the stacks in the right direction. Try again.\n";
			}
			else {
				toRow = row1;
				toCol = std::max(col1, col2) + 1;
				auto& destCell = board[{toRow, toCol}];
				if (destCell.has_value()) {
					std::cout << "The space that the first card moves onto must be empty. Try again.\n";
				}
				else {
					auto& firstCell = (col2 > col1) ? board[{row2, col2}] : board[{row1, col1}];
					auto& secondCell = (col2 > col1) ? board[{row1, col1}] : board[{row2, col2}];

					destCell = std::move(firstCell);
					firstCell.reset();
					firstCell = std::move(secondCell);
					secondCell.reset();
					std::cout << "The stacks have been shifted to the right.\n";
					validMove = true;
				}
			}
		}
		else if (direction == 'U') {
			if (col1 != col2) {
				std::cout << "You can't shift the stacks in the up direction. Try again.\n";
			}
			else {
				toRow = std::min(row1, row2) - 1;
				toCol = col1;
				auto& destCell = board[{toRow, toCol}];
				if (destCell.has_value()) {
					std::cout << "The space that the first card moves onto must be empty. Try again.\n";
				}
				else {
					auto& firstCell = (row2 > row1) ? board[{row1, col1}] : board[{row2, col2}];
					auto& secondCell = (row2 > row1) ? board[{row2, col2}] : board[{row1, col1}];

					destCell = std::move(firstCell);
					firstCell.reset();
					firstCell = std::move(secondCell);
					secondCell.reset();
					std::cout << "The stacks have been shifted up.\n";
					validMove = true;
				}
			}
		}
		else if (direction == 'D') {
			if (col1 != col2) {
				std::cout << "You can't shift the stacks down. Try again.\n";
			}
			else {
				toRow = std::max(row1, row2) + 1;
				toCol = col1;
				auto& destCell = board[{toRow, toCol}];
				if (destCell.has_value()) {
					std::cout << "The space that the first card moves onto must be empty. Try again.\n";
				}
				else {
					auto& firstCell = (row2 > row1) ? board[{row2, col2}] : board[{row1, col1}];
					auto& secondCell = (row2 > row1) ? board[{row1, col1}] : board[{row2, col2}];

					destCell = std::move(firstCell);
					firstCell.reset();
					firstCell = std::move(secondCell);
					secondCell.reset();
					std::cout << "The stacks have been shifted down.\n";
					validMove = true;
				}
			}
		}

		if (validMove) {
			break;
		}
	}

}
void eter::elementalPowerCards::activateBorder(Board& board, Player& player) {
	size_t row, col;

	while (true) {
		std::cout << "Enter the row and column to place the Border card: ";
		std::cin >> row >> col;

		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position. Position is outside the board. Try again.\n";
			continue;
		}

		if (!(row == board.GetIndexLineMin() || row == board.GetIndexLineMax() ||
			col == board.GetIndexColMin() || col == board.GetIndexColMax())) {
			std::cout << "The position must define a border of the playing area. "
				<< " Try again.\n";
			continue;
		}

		auto& cell = board[{row, col}];
		if (cell.has_value() && !cell->empty()) {
			std::cout << "The selected position is not empty. Try again.\n";
			continue;
		}

		Card borderCard;
		borderCard.SetValue(0);
		borderCard.SetColor("Neutral");
		borderCard.SetPosition(true);

		if (!cell.has_value()) {
			cell.emplace();
		}
		cell->push(borderCard);
		std::cout << "Border card  placed at (" << row << ", " << col << ").\n";
		break;
	}

	std::cout << "Now play your normal card.\n";
	size_t normalRow, normalCol;
	while (true) {
		std::cout << "Enter the row and column to place your normal card: ";
		std::cin >> normalRow >> normalCol;

		if (!board.isValidPosition(normalRow, normalCol)) {
			std::cout << "Invalid position. Position is outside the board. \n";
			continue;
		}

		auto& normalCell = board[{normalRow, normalCol}];
		if (normalCell.has_value() && !normalCell->empty()) {
			std::cout << "The selected position is not empty.\n";
			continue;
		}

		auto& cardsInHand = player.GetCardsInHand();
		if (cardsInHand.empty()) {
			std::cout << "You have no cards in your hand to play.\n";
			return;
		}

		std::cout << "Choose a card from your hand to play: \n";
		for (size_t i = 0; i < cardsInHand.size(); ++i) {
			const Card& card = cardsInHand[i];
			std::cout << i + 1 << ": Card with value " << static_cast<int>(card.GetValue()) << ", Color: " << card.GetColor() << "\n";
		}

		size_t chosenIndex;
		while (true) {
			std::cin >> chosenIndex;
			if (std::cin.fail() || chosenIndex < 1 || chosenIndex > cardsInHand.size()) {
				std::cout << "Invalid choice. Please select a valid card index. \n";
				std::cin.clear();
				continue;
			}
			break;
		}

		Card selectedCard = cardsInHand[chosenIndex - 1];
		cardsInHand.erase(cardsInHand.begin() + (chosenIndex - 1));

		if (!normalCell.has_value())
		{
			normalCell.emplace();
		}
		normalCell->push(selectedCard);
		std::cout << "Normal card with value " << static_cast<int>(selectedCard.GetValue()) << " placed at (" << normalRow << ", " << normalCol << ").\n";
		break;
	}

}





};








