#pragma once
#include "Brick.h"

template<class T>
class Factory
{
public:
	Factory();
	~Factory();

	virtual void CreateInstance();
	
};

class BrickFactory
	: Factory<Brick>
{
	virtual void CreateInstance() override;
};
