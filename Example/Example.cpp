#include <WIndows.h>
#include "Example.h"

void ExampleGame::Start()
{
	std::cout << "What's your name? ";
	std::cin >> characterName;
	std::cout << "Hello " << characterName << "." << std::endl;

	console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

	std::cout << "@";
}

void ExampleGame::Update(float deltaTime)
{
	if (LUX::Input::GetKeyDown(LUX::KeyCode::W) && character->GetPosition()->GetY() - characterMoveSpeed * deltaTime >= 0)
	{
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << " ";

		character->GetPosition()->SetY(character->GetPosition()->GetY() - characterMoveSpeed * deltaTime);
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << "@";
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::A) && character->GetPosition()->GetX() - characterMoveSpeed * deltaTime >= 0)
	{
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << " ";

		character->GetPosition()->SetX(character->GetPosition()->GetX() - characterMoveSpeed * deltaTime);
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << "@";
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::S) && character->GetPosition()->GetY() + characterMoveSpeed * deltaTime < console->GetHeight())
	{
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << " ";

		character->GetPosition()->SetY(character->GetPosition()->GetY() + characterMoveSpeed * deltaTime);
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << "@";
	}
	if (LUX::Input::GetKeyDown(LUX::KeyCode::D) && character->GetPosition()->GetX() + characterMoveSpeed * deltaTime < console->GetWidth())
	{
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << " ";

		character->GetPosition()->SetX(character->GetPosition()->GetX() + characterMoveSpeed * deltaTime);
		console->Gotoxy(character->GetPosition()->GetX(), character->GetPosition()->GetY());

		std::cout << "@";
	}
}

ExampleGame::ExampleGame(LUX::Console* console) : LUX::Game(console), character(new LUX::GameObject("My Character", "Character", true))
{
	std::cout << console->GetTitle() << " initialized." << std::endl;

	character->GetPosition()->Set(11.0f, 6.0f);
}

ExampleGame::~ExampleGame()
{
	if (character != nullptr)
	{
		delete character;
	}
}