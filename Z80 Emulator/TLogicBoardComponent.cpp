#include "TLogicBoardComponent.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "TFactory.h"
#include "TManager.h"
#include "TSceneManager.h"
#include "TCacheManager.h"
#include "TDrawableComponent.h"
#include "TPinComponent.h"

#include "TXMLFile.h"

namespace nne
{
	
	TLogicBoardComponent::TLogicBoardComponent() :
		mPlacedBoard(nullptr)
	{

	}

	void TLogicBoardComponent::setBoard(TBoard& Board)
	{
		mPlacedBoard = &Board;
	}

	nne::TBoard& TLogicBoardComponent::getBoard() const
	{
		return *mPlacedBoard;
	}

	bool TLogicBoardComponent::hasBoard() const
	{
		return mPlacedBoard ? true : false;
	}

	void TLogicBoardComponent::update(const sf::Time& ElapsedTime)
	{
	}

	void TLogicBoardComponent::refresh(const sf::Time& ElapsedTime)
	{
	}

	void TLogicBoardComponent::init()
	{
	}

}