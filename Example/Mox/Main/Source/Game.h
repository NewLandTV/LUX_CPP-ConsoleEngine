#ifndef __GAME_H__
#define __GAME_H__

#include <Windows.h>
#include "Engine/LUX.h"

class MoxGame : public LUX::Game
{
private:
	// Handles
	HANDLE screenHandles[2];

	// Game objects
	LUX::GameObject* player = nullptr;
	LUX::GameObject* box = nullptr;
	LUX::GameObject* destination = nullptr;

	// Variables
	float playerMoveSpeed = 10.0f;
	unsigned int score = 0;
	bool screenIndex = 0;

	void Print(LUX::Vector2 position, LUX::String string);

protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;

public:
	MoxGame(LUX::Console* console);
	~MoxGame();
};

#endif