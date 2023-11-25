#include <string>
#include "Game.h"

void MoxGame::Print(LUX::Vector2 position, LUX::String string)
{
	COORD coord = { position.GetX(), position.GetY() };
	DWORD dw;

	SetConsoleCursorPosition(screenHandles[screenIndex], coord);
	WriteFile(screenHandles[screenIndex], string.GetValue(), string.GetLength(), &dw, NULL);
}

void MoxGame::Start()
{
	srand((unsigned int)time(nullptr));

	player->GetPosition()->Set(console->GetWidth() >> 1, console->GetHeight() >> 1);
	box->GetPosition()->Set(rand() % console->GetWidth(), rand() % (console->GetHeight() - 1) + 1);
	destination->GetPosition()->Set(rand() % console->GetWidth(), rand() % (console->GetHeight() - 1) + 1);
}

void MoxGame::Update(float deltaTime)
{
	// Clear screen
	COORD coord = { 0, 0 };
	DWORD dw;

	FillConsoleOutputCharacter(screenHandles[screenIndex], ' ', console->GetWidth() * console->GetHeight(), coord, &dw);

	// Logics
	if (LUX::Input::GetKeyDown(LUX::KeyCode::W) && player->GetPosition()->GetY() - playerMoveSpeed * deltaTime >= 1.0f)
	{
		player->GetPosition()->SetY(player->GetPosition()->GetY() - playerMoveSpeed * deltaTime);
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::A) && player->GetPosition()->GetX() - playerMoveSpeed * deltaTime >= 0.0f)
	{
		player->GetPosition()->SetX(player->GetPosition()->GetX() - playerMoveSpeed * deltaTime);
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::S) && player->GetPosition()->GetY() + playerMoveSpeed * deltaTime < console->GetHeight())
	{
		player->GetPosition()->SetY(player->GetPosition()->GetY() + playerMoveSpeed * deltaTime);
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::D) && player->GetPosition()->GetX() + playerMoveSpeed * deltaTime < console->GetWidth() - 1)
	{
		player->GetPosition()->SetX(player->GetPosition()->GetX() + playerMoveSpeed * deltaTime);
	}
	if (LUX::Input::GetKeyDown((LUX::KeyCode)32))
	{
		// Get or Set
		if (box->GetActive() && (unsigned short)player->GetPosition()->GetX() == (unsigned short)box->GetPosition()->GetX() && (unsigned short)player->GetPosition()->GetY() == (unsigned short)box->GetPosition()->GetY())
		{
			box->SetActive(false);
		}
		else if (!box->GetActive() && (unsigned short)player->GetPosition()->GetX() == (unsigned short)destination->GetPosition()->GetX() && (unsigned short)player->GetPosition()->GetY() == (unsigned short)destination->GetPosition()->GetY())
		{
			box->SetActive(true);
			box->GetPosition()->Set(rand() % console->GetWidth(), rand() % (console->GetHeight() - 1) + 1);
			destination->GetPosition()->Set(rand() % console->GetWidth(), rand() % (console->GetHeight() - 1) + 1);

			score++;
		}
	}

	// Rendering
	if (box->GetActive())
	{
		Print(*box->GetPosition(), "бс");
	}

	Print(*destination->GetPosition(), "бр");
	Print(*player->GetPosition(), "б▄");
	Print(LUX::Vector2(console->GetWidth() >> 1, 0.0f), std::to_string(score).c_str());

	// Screen flipping
	SetConsoleActiveScreenBuffer(screenHandles[screenIndex]);

	screenIndex = !screenIndex;
}

MoxGame::MoxGame(LUX::Console* console) : LUX::Game(console), player(new LUX::GameObject("Mox Player", "Player", true)), box(new LUX::GameObject("Mox Box", "Box", true)), destination(new LUX::GameObject("Mox Destination", "Destination", true))
{
	CONSOLE_CURSOR_INFO consoleCursorInfo;

	screenHandles[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenHandles[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	SetConsoleCursorInfo(screenHandles[0], &consoleCursorInfo);
	SetConsoleCursorInfo(screenHandles[1], &consoleCursorInfo);
}

MoxGame::~MoxGame()
{
	// Handles
	CloseHandle(screenHandles[0]);
	CloseHandle(screenHandles[1]);

	// Game objects
	if (player != nullptr)
	{
		delete player;
	}

	if (box != nullptr)
	{
		delete box;
	}

	if (destination != nullptr)
	{
		delete destination;
	}
}