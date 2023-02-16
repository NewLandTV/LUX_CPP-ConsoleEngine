#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

#include "LUX.h"

class ExampleGame : public LUX::Game
{
private:
	LUX::GameObject* character;
	LUX::String characterName;
	float characterMoveSpeed = 8.0f;

protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;

public:
	ExampleGame(LUX::Console* console);
	~ExampleGame();
};

#endif