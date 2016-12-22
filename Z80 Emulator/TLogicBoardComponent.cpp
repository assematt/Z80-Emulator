#include "TLogicBoardComponent.h"
#include "TSceneManager.h"
#include "TCacheManager.h"
#include <SFML/Graphics.hpp>

namespace nne
{

	TLogicBoardComponent::TLogicBoardComponent() :
		mSelectedChip(nullptr),
		mFormerSelectedChip(nullptr),
		mFormerSelectedTrack(nullptr),
		mSelectedTrack(nullptr)
	{
	}

	void TLogicBoardComponent::update(const sf::Time& ElapsedTime)
	{
		
	}

	void TLogicBoardComponent::placeChip(TChipComponent* Component)
	{
		mComponentVector.push_back(Component);
	}


	void TLogicBoardComponent::placeChip(TEntity* Entity)
	{
		//Entity->replaceComponent<TLogicBoardComponent>(this);
		Entity->addComponent<TLogicBoardComponent>(this);

		placeChip(Entity->getComponentAsPtr<TChipComponent>());
	}

	void TLogicBoardComponent::placeTrack(TConductiveTracks* Track)
	{
		mTrackVector.push_back(Track);
	}

	void TLogicBoardComponent::placeTrack(TEntity* Entity)
	{
		//Entity->replaceComponent<TLogicBoardComponent>(this);
		Entity->addComponent<TLogicBoardComponent>(this);

		placeTrack(Entity->getComponentAsPtr<TConductiveTracks>());
	}

	void TLogicBoardComponent::setLogicBoard(TEntity* Entity)
	{

	}

	void TLogicBoardComponent::setSelectedChip(TChipComponent* Chip)
	{
		// Check if is the first time we are assigning the selected chip, if yes also check if have selected a different chip
		if (mSelectedChip && mSelectedChip != Chip)
			mFormerSelectedChip = mSelectedChip;

		// Set the selected chip
		mSelectedChip = Chip;
	}

	TChipComponent* TLogicBoardComponent::getSelectedChip() const
	{
		return mSelectedChip;
	}

	TChipComponent* TLogicBoardComponent::getFormerSelectedChip() const
	{
		return mFormerSelectedChip;
	}

	void TLogicBoardComponent::deselectChip(bool DisableFormerChipToo /*= false*/)
	{
		mSelectedChip = nullptr;

		if (DisableFormerChipToo)
			mFormerSelectedChip = nullptr;
	}

	void TLogicBoardComponent::setSelectedTrack(TConductiveTracks* Track)
	{
		// Check if is the first time we are assigning the selected track, if yes also check if have selected a different track
		if (mSelectedTrack && mSelectedTrack != Track)
			mFormerSelectedTrack = mSelectedTrack;

		// Set the selected track
		mSelectedTrack = Track;
	}

	TConductiveTracks* TLogicBoardComponent::getSelectedTrack() const
	{
		return mSelectedTrack;
	}

	TConductiveTracks* TLogicBoardComponent::getFormerSelectedTrack() const
	{
		return mFormerSelectedTrack;
	}

	void TLogicBoardComponent::deselectTrack(bool DisableFormerTrackToo /*= false*/)
	{
		mSelectedTrack = nullptr;
		
		if (DisableFormerTrackToo)
			mFormerSelectedTrack = nullptr;
	}

	void TLogicBoardComponent::refresh(const sf::Time& ElapsedTime)
	{
		
	}

	void TLogicBoardComponent::init()
	{
		
	}

}