#pragma once
#include "BaseGameState.h"
class InstructionState :
	public BaseGameState
{
public:
	InstructionState(Application &);
	~InstructionState();

	void Back();
};

