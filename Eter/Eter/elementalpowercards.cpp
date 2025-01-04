module elementalpowercards;
import board;
import player;
import card;
import <stdexcept>;
import <unordered_map>;
import <iostream>;

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

	void elementalPowerCards::setUsed(bool used)
	{
		m_used = used;
	}

	bool elementalPowerCards::getUsed() const
	{
		return m_used;
	}

	void elementalPowerCards::setAbility(powerAbility power)
	{
		m_power = power;
	}

	elementalPowerCards::powerAbility elementalPowerCards::getAbility() const
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
			activateExplosion(game);
			break;
		case eter::elementalPowerCards::powerAbility::destruction:
			activateDestruction(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::flame:
			activateFlame(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::fire:
			activateFire(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::ash:
			activateASH(player, board);
			break;
		case eter::elementalPowerCards::powerAbility::spark:
			activateSpark(player,opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::squall:
			activateSquall(opponent, player, board);
			break;
		case eter::elementalPowerCards::powerAbility::gale:
			activateGale(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::hurricane:
			activateHurricane(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::gust:
			activateGust(board,player,opponent);
			break;
		case eter::elementalPowerCards::powerAbility::mirage:
			activateMirage(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::storm:
			activateStorm(board, player, opponent);
			break;
		case eter::elementalPowerCards::powerAbility::tide:
			activateTide(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::mist:
			activateMist(player, board);
			break;
		case eter::elementalPowerCards::powerAbility::wave:
			activateWave(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::whirlpool:
			activateWhirlpool(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::blizzard:
			activateBlizzard(board, player, opponent);
			break;
		case eter::elementalPowerCards::powerAbility::waterfall:
			activateWaterfall(board);
			break;
		case eter::elementalPowerCards::powerAbility::support:
			activateSupport(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::earthQuake:
			activateEarthQuake(player, opponent, board);
			break;
		case eter::elementalPowerCards::powerAbility::crumble:
			activateCrumble(board, player);
			break;
		case eter::elementalPowerCards::powerAbility::border:
			break;
		case eter::elementalPowerCards::powerAbility::avalanche:
			activateAvalanche(board);
			break;
		case eter::elementalPowerCards::powerAbility::rock:
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
			game->GetBoardRef() = explosion.applyEffects();
			game->SetReturnedCards(explosion.GetReturnedCards());
			game->SetCountTurnForReturnedCards (1);
			game->SetIsUsedExplosion(true);
		}
	}

	void elementalPowerCards::activateDestruction(Player& player, Player& opponent, Board& board) {
		// Obținem vectorul de cărți jucate ale adversarului
		auto& opponentPlayedCards = opponent.GetPlayedCardsForPower();

		// Verificăm dacă adversarul a jucat cel puțin o carte
		if (opponentPlayedCards.empty()) {
			std::cout << "The opponent has no played cards to remove.\n";
		}
		else
		{
			// Obținem ultima carte jucată de adversar și poziția sa
			const auto& lastPlayedCardWithPos = opponentPlayedCards.back();
			const Card& lastCardPlayed = lastPlayedCardWithPos.first;
			size_t  x = lastPlayedCardWithPos.second.first;
			size_t  y = lastPlayedCardWithPos.second.second;

			std::cout << "Debug: Last card played by the opponent is value " << lastCardPlayed.GetValue() + 1 - 1
				<< " and color " << lastCardPlayed.GetColor() << " at position (" << (int)x << ", " << (int)y << ").\n";

			board.removeCard(x, y);
			opponentPlayedCards.pop_back();

			opponent.AddToEliminatedCards(lastCardPlayed);

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


		opponent.AddCardToHand(cardToReturn);

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
						player.AddCardToHand(card);
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
							opponent.AddCardToHand(card);
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
				player.AddPlayedCard(chosenCard);
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
			player.RemovePlayedCardForPower(selectedCard, chosenRow, chosenCol);
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
							owner->AddToEliminatedCards(topCard);
							std::cout << "The card with value " << static_cast<int>(topCard.GetValue())
								<< " has been eliminated.\n";
						}
						board.removeCard(i, j);
					}
				}
			}
		}
	}

void elementalPowerCards::activateMist(Player& player, Board& board)
{
	uint8_t row, col;
	std::cout << "Enter the coordinates of the position to use an illusion:";
	std::cin >> row >> col;
	std::vector<Card>& cardsInHand = player.GetCardsInHand();
	int selectedCardIndex = -1;

	std::cout << "Select a new illusion from your hand:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i)
		std::cout << i << ": " << cardsInHand[i] << "\n";
	std::cin >> selectedCardIndex;

	if (selectedCardIndex < 0 || selectedCardIndex >= cardsInHand.size()) {
		std::cout << "Invalid selection. Mirage cancelled.\n";
		return;
	}

	Card newIllusion = cardsInHand[selectedCardIndex];
	player.useIllusion(row, col, board, newIllusion);
	player.AddPlayedCard(newIllusion);
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);

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
							player.AddCardToHand(currentCard);
							auto& playedCards = player.GetPlayedCards();
							playedCards.erase(
								std::remove(playedCards.begin(), playedCards.end(), currentCard),
								playedCards.end()
							);
							std::cout << "The card with the value " << currentCard.GetValue() + 1 - 1 << " returned to the player's hand.\n";
						}
						else
						{
							opponent.AddCardToHand(currentCard);
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

		if (selectedStack->size() > 1)
		{
			std::cout << "The position has a stack of cards. Choose a position that has only 1 card.\n";
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
		player.RemovePlayedCardForPower(selectedStack->top(), selectedRow, selectedCol);
		player.addPlayedCardForPower(selectedStack->top(), finalRow, finalCol);
	}
	else
	{
		opponent.RemovePlayedCardForPower(selectedStack->top(), selectedRow, selectedCol);
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

void elementalPowerCards::activateWave(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the coordinates of the stack to move (row, column): ";
	std::cin >> row >> col;
	if (row < 0 || row >= board.GetIndexMax() || col < 0 || col >= board.GetIndexMax())
	{
		std::cout << "Invalid position. Try again.\n";
		return;
	}
	auto& stack = board[{row, col}];
	if (!stack.has_value() || stack->size() <= 1)
	{
		std::cout << "Selected stack must contain more than one card.\n";
		return;
	}
	int newRow, newCol;
	bool foundEmptyAdjacent = false;
	do {
		std::cout << "Enter the coordinates for an empty adjacent position (row, column): ";
		std::cin >> newRow >> newCol;
		if (board.isValidPosition(newRow, newCol) && !board[{newRow, newCol}].has_value())
			foundEmptyAdjacent = true;
		else
			std::cout << "The chosen position is not empty or is invalid. Try again.\n";
	} while (!foundEmptyAdjacent);

	board[{newRow, newCol}] = stack;
	stack.reset();
	if (player.GetCardsInHand().empty())
	{
		std::cout << "No cards available in hand to play.\n";
		return;
	}

	std::cout << "Choose a card to play from your hand:\n";
	for (size_t i = 0; i < player.GetCardsInHand().size(); ++i) 
	{
		std::cout << i + 1 << ": " << player.GetCardsInHand()[i].GetValue() << "\n";
	}
	int cardIndex;
	std::cin >> cardIndex;
	if (cardIndex < 1 || static_cast<size_t>(cardIndex) > player.GetCardsInHand().size())
	{
		std::cout << "Invalid choice.\n";
		return;
	}
	Card chosenCard = player.GetCardsInHand()[cardIndex - 1];
	board.placeCard(newRow, newCol, chosenCard);
	player.AddPlayedCard(chosenCard);
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + cardIndex - 1);
}

void elementalPowerCards::activateStorm(Board& board, Player& player, Player& opponent)
{
	for (size_t row = 0; row < board.GetIndexMax(); ++row)
	{
		for (size_t col = 0; col < board.GetIndexMax(); ++col)
		{
			auto& stack = board[{static_cast<int>(row), static_cast<int>(col)}];
			if (stack.has_value() && stack.value().size() >= 2)
			{
				while (!stack.value().empty())
				{
					Card topCard = stack.value().top();
					stack.value().pop();
					if (topCard.GetColor() == player.GetColor())
					{
						player.AddToEliminatedCards(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddToEliminatedCards(topCard);
					}
				}
			}
		}
	}
}

void elementalPowerCards::activateWaterfall(Board& board)
{
	char choice;
	std::cout << "Choose 'R' for row or 'C' for column: ";
	std::cin >> choice;
	if (choice == 'R') {
		int row;
		char direction;
		std::cout << "Enter the row number with at least 3 occupied positions: ";
		std::cin >> row;
		if (row < 0 || row >= board.GetIndexMax())
		{
			std::cout << "Invalid row. Try again.\n";
			return;
		}

		int occupiedCount = 0;
		for (size_t col = 0; col < board.GetIndexMax(); ++col)
			if (board[{row, static_cast<int>(col)}].has_value())
				++occupiedCount;

		if (occupiedCount < 3)
		{
			std::cout << "Selected row must have at least 3 occupied positions.\n";
			return;
		}

		std::cout << "Enter the direction of the cascade (D for down, U for up): ";
		std::cin >> direction;

		if (direction != 'D' && direction != 'U') {
			std::cout << "Invalid direction. Try again.\n";
			return;
		}

		std::stack<Card> finalStack;
		if (direction == 'D')
		{
			for (size_t col = 0; col < board.GetIndexMax(); ++col)
			{
				if (board[{row, static_cast<int>(col)}].has_value())
				{
					auto& currentStack = board[{row, static_cast<int>(col)}].value();
					while (!currentStack.empty())
					{
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, static_cast<int>(col)}].reset();
				}
			}
			board[{row, 0}] = finalStack;
		}
		else if (direction == 'U')
		{
			for (int col = static_cast<int>(board.GetIndexMax() - 1); col >= 0; --col)
			{
				if (board[{row, col}].has_value())
				{
					auto& currentStack = board[{row, col}].value();
					while (!currentStack.empty())
					{
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, col}].reset();
				}
			}
			board[{row, static_cast<int>(board.GetIndexMax() - 1)}] = finalStack;
		}
	}
	else if (choice == 'C') {
		int col;
		char direction;
		std::cout << "Enter the column number with at least 3 occupied positions: ";
		std::cin >> col;
		if (col < 0 || col >= board.GetIndexMax()) {
			std::cout << "Invalid column. Try again.\n";
			return;
		}

		int occupiedCount = 0;
		for (size_t row = 0; row < board.GetIndexMax(); ++row) {
			if (board[{static_cast<int>(row), col}].has_value()) {
				++occupiedCount;
			}
		}

		if (occupiedCount < 3) {
			std::cout << "Selected column must have at least 3 occupied positions.\n";
			return;
		}

		std::cout << "Enter the direction of the cascade (U for up, D for down): ";
		std::cin >> direction;

		if (direction != 'U' && direction != 'D') {
			std::cout << "Invalid direction. Try again.\n";
			return;
		}

		std::stack<Card> finalStack;
		if (direction == 'U') {
			for (size_t row = 0; row < board.GetIndexMax(); ++row) {
				if (board[{static_cast<int>(row), col}].has_value()) {
					auto& currentStack = board[{static_cast<int>(row), col}].value();
					while (!currentStack.empty()) {
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{static_cast<int>(row), col}].reset();
				}
			}
			board[{0, col}] = finalStack;
		}
		else if (direction == 'D') {
			for (int row = static_cast<int>(board.GetIndexMax() - 1); row >= 0; --row) {
				if (board[{row, col}].has_value()) {
					auto& currentStack = board[{row, col}].value();
					while (!currentStack.empty()) {
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, col}].reset();
				}
			}
			board[{static_cast<int>(board.GetIndexMax() - 1), col}] = finalStack;
		}
	}
	else {
		std::cout << "Invalid choice. Choose 'R' for row or 'C' for column.\n";
	}
}

void elementalPowerCards::activateWhirlpool(Board& board, Player& player)
{
	int row1, col1, row2, col2;
	std::cout << "Enter the coordinates for the first card (row, column): ";
	std::cin >> row1 >> col1;

	std::cout << "Enter the coordinates for the second card (row, column): ";
	std::cin >> row2 >> col2;

	if ((abs(row1 - row2) == 1 && col1 == col2) || (abs(col1 - col2) == 1 && row1 == row2))
	{
		if (board[{row1, col1}].has_value() && board[{row2, col2}].has_value())
		{
			auto& stack1 = board[{row1, col1}].value();
			auto& stack2 = board[{row2, col2}].value();
			if (stack1.size() == 1 && stack2.size() == 1)
			{
				Card card1 = stack1.top();
				Card card2 = stack2.top();

				stack1.pop();
				stack2.pop();
				if (card1.GetValue() < card2.GetValue())
				{
					board[{row1, col1}].value().push(card1);
					board[{row2, col2}].value().push(card2);
				}
				else if (card1.GetValue() > card2.GetValue())
				{
					board[{row1, col1}].value().push(card2);
					board[{row2, col2}].value().push(card1);
				}
				else
				{
					char choice;
					std::cout << "The cards have equal values. Do you want card1 or card2 on top? (1/2): ";
					std::cin >> choice;
					if (choice == '1')
					{
						board[{row1, col1}].value().push(card1);
						board[{row2, col2}].value().push(card2);
					}
					else if (choice == '2')
					{
						board[{row1, col1}].value().push(card2);
						board[{row2, col2}].value().push(card1);
					}
					else
					{
						std::cout << "Invalid choice. No change made.\n";
						return;
					}
				}
			}
			else 
			{
				std::cout << "Both positions must contain exactly one card!\n";
				return;
			}
		}
		else
		{
			std::cout << "One or both positions do not contain any cards!\n";
			return;
		}
	}
	else
		std::cout << "The positions are not adjacent. Please select adjacent positions.\n";
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
			player.AddCardToHand(card);
		}
		else {
			opponent.AddCardToHand(card);
		}
	}

	std::cout << "The " << (isRow ? "row" : "column") << " has been shifted successfully." << std::endl;
}



void eter::elementalPowerCards::activateMirage(Board& board, Player& player)
{
	for (size_t row = 0; row < board.GetIndexMax(); ++row) {
		for (size_t col = 0; col < board.GetIndexMax(); ++col) {
			auto& cell = board[{row, col}];

			if (cell.has_value() && !cell->empty()) 
			{
				Card& topCard = cell->top();
				if (topCard.GetColor() == player.GetColor() && !topCard.GetPosition()) 
				{
					cell->pop();
					player.AddCardToHand(topCard);
					
					std::vector<Card>& cardsInHand = player.GetCardsInHand();
					int selectedCardIndex = -1;

					std::cout << "Select a new illusion from your hand:\n";
					for (size_t i = 0; i < cardsInHand.size(); ++i) 
						std::cout << i << ": " << cardsInHand[i] << "\n";
					std::cin >> selectedCardIndex;

					if (selectedCardIndex < 0 || selectedCardIndex >= cardsInHand.size()) {
						std::cout << "Invalid selection. Mirage cancelled.\n";
						return;
					}

					Card newIllusion = cardsInHand[selectedCardIndex];
					player.useIllusion(row, col, board, newIllusion);
					player.AddPlayedCard(newIllusion);
					player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);
					return;
				}
			}
		}
	}

	std::cout << "No illusion found on the board to replace.\n";
}

void eter::elementalPowerCards::activateBlizzard(Board& board, Player& player, Player& opponent)
{
	bool hasFreeSpace = false;
	for (size_t row = 0; row < board.GetIndexMax(); ++row)
	{
		for (size_t col = 0; col < board.GetIndexMax(); ++col)
		{
			if (!board[{row, col}].has_value())
			{
				hasFreeSpace = true;
				break;
			}
		}
		if (hasFreeSpace) break;
	}

	if (!hasFreeSpace) {
		std::cout << "Opponent does not have any free space to play a card. Blizzard cannot be activated.\n";
		return;
	}

	int x, y;
	std::cout << "Enter the position (row and column) to place the Blizzard card: ";
	std::cin >> x >> y;

	if (x < 0 || x >= board.GetIndexMax() || y < 0 || y >= board.GetIndexMax())
	{
		std::cout << "Invalid position. Blizzard cancelled.\n";
		return;
	}

	if (board[{x, y}].has_value()) 
	{
		std::cout << "Position is already occupied. Blizzard cancelled.\n";
		return;
	}
	Card blizzardCard('X', player.GetColor(),true); 
	board[{x, y}].emplace().push(blizzardCard);
	player.AddPlayedCard(blizzardCard);

	int blockedRow = -1, blockedCol = -1;
	char choice;
	std::cout << "Do you want to block a row (R) or a column (C)? ";
	std::cin >> choice;
	if (choice == 'R' || choice == 'r') 
	{
		blockedRow = x;
		std::cout << "Row " << blockedRow << " will be blocked.\n";
	}
	else if (choice == 'C' || choice == 'c') 
	{
		blockedCol = y;
		std::cout << "Column " << blockedCol << " will be blocked.\n";
	}
	//continuare pentru a face oponentul sa nu poata plasa o carte in urmatoarea tura
}

void eter::elementalPowerCards::activateSupport(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the row and column of the card to boost (1/2/3): ";
	std::cin >> row >> col;

	if (row < 0 || row >= board.GetIndexMax() || col < 0 || col >= board.GetIndexMax()) {
		std::cout << "Invalid position on the board.\n";
		return;
	}

	auto& cell = board[{row, col}];
	if (!cell.has_value() || cell->empty()) {
		std::cout << "No cards at the specified position.\n";
		return;
	}

	Card& topCard = cell->top();

	if (topCard.GetColor() == player.GetColor() && (topCard.GetValue() >= 1 && topCard.GetValue() <= 3))
	{
		int originalValue = topCard.GetValue(); 
		topCard.SetValue(topCard.GetValue() + 1); 
	}
	//continuare
}

void eter::elementalPowerCards::activateCrumble(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the row and column of the card to boost (1/2/3): ";
	std::cin >> row >> col;

	if (row < 0 || row >= board.GetIndexMax() || col < 0 || col >= board.GetIndexMax()) {
		std::cout << "Invalid position on the board.\n";
		return;
	}

	auto& cell = board[{row, col}];
	if (!cell.has_value() || cell->empty()) {
		std::cout << "No cards at the specified position.\n";
		return;
	}

	Card& topCard = cell->top();

	if (topCard.GetColor() == player.GetColor() && (topCard.GetValue() >= 1 && topCard.GetValue() <= 3))
	{
		int originalValue = topCard.GetValue();
		topCard.SetValue(topCard.GetValue() -1);
	}
	//continuare
}

void eter::elementalPowerCards::activateRock(Board& board, Player& player)
{
	std::vector<std::pair<int, int>> illusionPositions;

	for (size_t row = 0; row < board.GetIndexMax(); ++row)
	{
		for (size_t col = 0; col < board.GetIndexMax(); ++col)
		{
			auto& cell = board[{row, col}];
			if (cell.has_value() && !cell->empty()) 
			{
				Card& topCard = cell->top();
				if (topCard.GetPosition()==0) 
					illusionPositions.push_back({ row, col });
			}
		}
	}

	if (illusionPositions.empty())
	{
		std::cout << "No Illusion cards found on the board. ROCK action cancelled.\n";
		return;
	}

	std::cout << "Select an Illusion card to cover from the following positions:\n";
	for (size_t i = 0; i < illusionPositions.size(); ++i)
		std::cout << i << ": Row " << illusionPositions[i].first << ", Column " << illusionPositions[i].second << "\n";

	uint8_t selectedPositionIndex;
	std::cin >> selectedPositionIndex;

	uint8_t selectedRow = illusionPositions[selectedPositionIndex].first;
	uint8_t selectedCol = illusionPositions[selectedPositionIndex].second;

	std::vector<Card>& cardsInHand = player.GetCardsInHand();
	uint8_t selectedCardIndex ;

	std::cout << "Select a card from your hand to cover the Illusion card:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i) 
		std::cout << i << ": " << cardsInHand[i] << "\n";

	std::cin >> selectedCardIndex;

	Card coverCard = cardsInHand[selectedCardIndex];
	player.AddPlayedCard(coverCard); 
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);
	auto& cell = board[{selectedRow, selectedCol}];
	cell->push(coverCard); 
}
void elementalPowerCards::activateAvalanche(Board& board) //DE VERIFICAT!!
{
	int row1, col1, row2, col2;
	std::cout << "Enter the coordinates of the first stack (row col): ";
	std::cin >> row1 >> col1;
	std::cout << "Enter the coordinates of the second stack (row col): ";
	std::cin >> row2 >> col2;

	if ((row1 == row2 && abs(col1 - col2) == 1) || (col1 == col2 && abs(row1 - row2) == 1))
	{

		std::vector<std::pair<int, int>> emptyPositions;

		if (row1 == row2)
		{ 
			if (col1 > 0 && !board[{row1, col1 - 1}].has_value()) 
				emptyPositions.push_back({ row1, col1 - 1 });
			if (col1 + 1 < board.GetIndexMax() && !board[{row1, col1 + 1}].has_value())
				emptyPositions.push_back({ row1, col1 + 1 });
			if (col2 > 0 && !board[{row2, col2 - 1}].has_value()) 
				emptyPositions.push_back({ row2, col2 - 1 });
			if (col2 + 1 < board.GetIndexMax() && !board[{row2, col2 + 1}].has_value())
				emptyPositions.push_back({ row2, col2 + 1 });
		}
		else if (col1 == col2) 
		{ 
			if (row1 > 0 && !board[{row1 - 1, col1}].has_value())
				emptyPositions.push_back({ row1 - 1, col1 });
			if (row1 + 1 < board.GetIndexMax() && !board[{row1 + 1, col1}].has_value())
				emptyPositions.push_back({ row1 + 1, col1 });
			if (row2 > 0 && !board[{row2 - 1, col1}].has_value()) 
				emptyPositions.push_back({ row2 - 1, col1 });
			if (row2 + 1 < board.GetIndexMax() && !board[{row2 + 1, col1}].has_value())
				emptyPositions.push_back({ row2 + 1, col1 });
		}
		if (!emptyPositions.empty()) 
		{
			int selectedPosition;
			std::cout << "Select the position to shift both stacks to:\n";
			for (size_t i = 0; i < emptyPositions.size(); ++i)
			{
				std::cout << i << ": (" << emptyPositions[i].first << ", " << emptyPositions[i].second << ")\n";
			}
			std::cin >> selectedPosition;

			if (selectedPosition < 0 || selectedPosition >= emptyPositions.size())
			{
				std::cout << "Invalid selection. Avalanche cancelled.\n";
				return;
			}

			auto newPos = emptyPositions[selectedPosition];

			board[{newPos.first, newPos.second}] = board[{row1, col1}];
			board[{row1, col1}].reset();
			board[{newPos.first, newPos.second + 1}] = board[{row2, col2}];
			board[{row2, col2}].reset();
		}
		else 
			std::cout << "No valid empty positions to move the stacks. Avalanche cancelled.\n";
	}
	else 
		std::cout << "The stacks are not adjacent. Avalanche cancelled.\n";
}

 
 

};








