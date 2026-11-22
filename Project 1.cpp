#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "RandomNumber.h";
using namespace std;

int RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

string ChoiceName(enGameChoice GameChoice)
{
	switch (GameChoice)
	{
	case enGameChoice::Paper:
		return "Paper";

	case enGameChoice::Rock:
		return "Rock";

	case enGameChoice::Scissors:
		return "Scissors";
	}
}
string WinnerName(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		return "Player";

	case enWinner::Computer:
		return "Computer";

	default:
		return "Draw";
	}
}

short ReadHowManyRounds()
{
	short GameRounds = 0;
	do
	{
		cout << "How many rounds 1 to 10 ?\n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{
		cout << "Your Choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	else {
		switch (RoundInfo.Player1Choice)
		{
		case enGameChoice::Rock:
			if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			{
				return enWinner::Computer;
			}
			break;
		case enGameChoice::Paper:
			if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			{
				return enWinner::Computer;
			}
			break;

		case enGameChoice::Scissors:
			if (RoundInfo.ComputerChoice == enGameChoice::Rock)
			{
				return enWinner::Computer;
			}
			break;
		
		}
	}
	return enWinner::Player;
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else if (ComputerWinTimes > Player1WinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}

}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F"); // Green
		break;

	case enWinner::Computer:
		system("color 4F"); // Red
		cout << "\a";
		break;

	default:
		system("color 6F");// Yellow
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n_____________Round [" << RoundInfo.RoundNumber << "]_____________\n\n";
	cout << "Player1 Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "____________________________________\n\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer2WinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;

	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

void ShowGameOverScreen()
{
	cout << "\t\t________________________________________________________\n\n";
	cout << "\t\t                +++ G a m e   O v e r +++\n";
	cout << "\t\t________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	ShowGameOverScreen();

	cout << "\t\t__________________[Game Results]________________________\n\n";
	cout << "\t\tGame Rounds        : " << GameResults.GameRounds << endl;
	cout << "\t\tPlayer1 Won Times  : " << GameResults.Player1WinTimes << endl;
	cout << "\t\tComputer Won Times : " << GameResults.Computer2WinTimes << endl;
	cout << "\t\tDraw Times         : " << GameResults.DrawTimes << endl;
	cout << "\t\tFinal Winner       : [" << GameResults.WinnerName << "]" << endl;
	cout << "\t\t________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
		{
			Player1WinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}
void ResetScreen()
{
	system("color 0F");
	system("cls");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		
		ShowFinalGameResults(GameResults);

		cout << "\n\t\tDo you want Play again ? Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	//system("pause>0");
	return 0;
}