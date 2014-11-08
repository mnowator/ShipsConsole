#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <list>
#include <cctype>
#include <conio.h> // just for kbhit

Game::Game() : gs(IN_MENU_1), gen(rd()), dis0to9(0, 9), dis0to1(0, 1)
{
	maxNumberOfShips.push_back(2); // single
	maxNumberOfShips.push_back(2); // double
	maxNumberOfShips.push_back(2); // triple
	maxNumberOfShips.push_back(1); // quadro
	maxNumberOfShips.push_back(1); // pento

}


Game::~Game()
{
}

void Game::setUpShipsAuto( Player*& player)
{
	const unsigned num2retry = 5000;
	unsigned numTry = 0;

	while (true)
	{
		Position pos(dis0to9(gen), dis0to9(gen));

		if (player->setShipElement(curentlySetingShip, pos))
		{
			++numElementsOfCurrentShip;

			if (numElementsOfCurrentShip == static_cast<unsigned>(curentlySetingShip)-48)
			{
				if (curentlySetingShip == PENTO)
				{
					gs = IN_PROGRES;
					return;
				}

				numElementsOfCurrentShip = 0;
				++numOfCurentTypeShip;

				if (numOfCurentTypeShip == maxNumberOfShips[static_cast<unsigned>(curentlySetingShip)-49])
				{
					numOfCurentTypeShip = 0;
					curentlySetingShip = static_cast<SHIP_TYPE>(static_cast<unsigned>(curentlySetingShip)+1);
				}
			}
		}
		else
		{
			++numTry;
			
			if (numTry == num2retry)
			{
				std::string name = player->getName();

				delete player;

				player = new Player(name);
				numTry = 0;
			}
		}			
	}
}

void Game::menu1()
{
	char choose;

	std::system("cls");
	std::cout << "~~ MNowator - Ships console game ~~~\n\n"
		<< "\t1. Game with CPU.\n"
		<< "\t2. Game via network.\n"
		<< "\t3. Exit\n";
	
	while (!_kbhit());

	choose = _getch();
	if (choose == '1') // game with cpu
	{
		std::string name;

		std::system("cls");
		std::cout << "Please eneter your name: ";
		std::cin >> name;

		player1 = new Player(name);
		player2 = new AIPlayer(std::string("CPU"));

		curentlySetingShip = SINGLE;
		numElementsOfCurrentShip = 0;
		numOfCurentTypeShip = 0;
		setUpShipsAuto(player2);

		gs = IN_SHIP_PREPARING;
		curentlySetingShip = SINGLE;
		numElementsOfCurrentShip = 0;
		numOfCurentTypeShip = 0;
	}
	else if (choose == '2')
	{

	}
	else if (choose == '3') // exit
	{
		gs = IN_QUIT;
	}
}

void Game::shipPreparing()
{
	static bool errorWrongPosition = false;
	Position pos;
	char row, column;

	std::system("cls");
	std::cout << "~~~ PREPARING SHIPS ~~~\n\n";
	std::cout << player1->displayMaps();
	std::cout << "To quit type 'q', to set up ship automaticly type 'au'.\n";
	std::cout << "If you want to reset map type 'rm'.\n\n";

	if (errorWrongPosition)
	{
		std::cout << "Coordinates, that you entered are not valid.\n";
		errorWrongPosition = false;
	}

	std::cout << static_cast<unsigned>(curentlySetingShip)-48 << "-segment ship, element #" << numElementsOfCurrentShip+1 << " is setting now.\n";
	std::cout << "Enter coordinetes ( i.e A3 ): ";

	std::cin >> column;

	if (column == 'q')
	{
		gs = IN_MENU_1;
		delete player1;
		delete player2;
		return;
	}

	std::cin >> row;

	if (column == 'a' && row == 'u') setUpShipsAuto(player1);
	if (column == 'r' && row == 'm')
	{
		std::string name = player1->getName();
		delete player1;
		player1 = new Player(name);
		numElementsOfCurrentShip = numOfCurentTypeShip = 0;
		curentlySetingShip = SINGLE;
		return;
	}


	try { pos = signs2position(row, column); }
	catch (WrongPosition)
	{
		errorWrongPosition = true;
		return;
	}
	
	if (player1->setShipElement(curentlySetingShip, pos))
	{
		++numElementsOfCurrentShip;

		if (numElementsOfCurrentShip == static_cast<unsigned>(curentlySetingShip)-48)
		{
			if (curentlySetingShip == PENTO)
			{
				gs = IN_PROGRES;
				return;
			}

			numElementsOfCurrentShip = 0;
			++numOfCurentTypeShip;

			if (numOfCurentTypeShip == maxNumberOfShips[static_cast<unsigned>(curentlySetingShip)-49])
			{
				numOfCurentTypeShip = 0;
				curentlySetingShip = static_cast<SHIP_TYPE>(static_cast<unsigned>(curentlySetingShip)+1);
			}
		}
	}
}

void Game::game()
{
	static bool errorWrongPosition = false;
	static std::list< std::string > last2messages;
	static bool justStarted = true;
	bool player1won = false;
	char row, column;
	SHIP_STATE state;
	bool shotPosible = false;
	Position pos;

	system("cls");

	std::cout << "~~~ GAME IN PROGRESS ~~~\n\n";
	std::cout << player1->displayMaps();
	std::cout << "If you want to back to menu type 'q'\n\n";

	if (last2messages.size() > 2) last2messages.pop_front();

	if (justStarted)
	{
		turn = dis0to1(gen) == 0 ? PLAYER1 : PLAYER2;
		justStarted = false;

		if (turn == PLAYER1)
		{
			last2messages.push_back(player1->getName() + " is begining.\n");
		}
		else last2messages.push_back(player2->getName() + " is begining.\n");
	}

	if (turn == PLAYER2)
	{
		do
		{
			pos = Position(dis0to9(gen), dis0to9(gen));
			shotPosible = player2->doShot(pos);
		} while (!shotPosible);

		state = player1->getShot(pos);
		std::tie(row, column) = position2signs(pos);

		if (state == MISSED) turn = PLAYER1;

		last2messages.push_back(player2->getName() + " shoted at " + column + row + ".\n");
		return;
	}

	for ( auto message : last2messages) std::cout << message;

	if (errorWrongPosition)
	{
		std::cout << "Coordinates, that you entered are not valid.\n";
		errorWrongPosition = false;
	}

	std::cout << "Enter coordinates, that where you want to shot ( i.e A3 ): ";

	std::cin >> column;

	if (column == 'q')
	{
		gs = IN_MENU_1;
		delete player1;
		delete player2;
		return;
	}

	std::cin >> row;

	try
	{ 
		std::string message;

		pos = signs2position(row, column); 
		if (!player1->doShot(pos)) throw WrongPosition();

		state = player2->getShot(pos);

		if (state == HITED)
		{
			message += "hited";
			player1->markHited(pos);
		}
		else if (state == SUNKEN)
		{
			message += "sunken";
			player1->markHited(pos);
		}
		else
		{
			message += "missed";
			turn = PLAYER2;
		}

		std::tie(row, column) = position2signs(pos);

		last2messages.push_back(player1->getName() + " " + message + " at field " +column+row +'\n');
	}
	catch (WrongPosition)
	{
		errorWrongPosition = true;
		return;
	}

	if (!player1->areShips())
	{
		system("cls");
		std::cout << "You lose against " + player2->getName() + ".\n";
		std::cout << "Press somethink to return to main menu\n";

		delete player1;
		delete player2;

		gs = IN_MENU_1;

		while (!_kbhit())
		{

		}
	}
	if (!player2->areShips())
	{
		system("cls");
		std::cout << "You won against " + player2->getName() + ".\n";
		std::cout << "Press somethink to return to main menu\n";

		delete player1;
		delete player2;

		gs = IN_MENU_1;

		while (!_kbhit())
		{

		}
	}
}

Position Game::signs2position(char row, char column) const
{
	char upperColumn = std::toupper(column);
	int irow = static_cast<int>(row)-48;

	if (upperColumn >= 65 && upperColumn <= 74 && irow >= 0 && irow <= 57)
	{	
		int icolumn = static_cast<int>(upperColumn)-65;

		return Position(icolumn, irow);
	}
	else throw WrongPosition();
}

std::tuple< char, char> Game::position2signs(Position pos) const
{
	char row, column;

	row = static_cast<char>(pos.posY + 48);
	column = static_cast<char>(pos.posX + 65);

	return std::tuple<char, char>(row, column);
}

void Game::loop()
{
	while (true)
	{
		if (gs == IN_QUIT) break;
		else if (gs == IN_MENU_1) menu1();
		else if (gs == IN_SHIP_PREPARING) shipPreparing();
		else if (gs == IN_PROGRES) game();
	}
}
