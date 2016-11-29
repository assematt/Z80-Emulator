#include "TLogicBoardComponent.h"
#include "TSceneManager.h"

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
		Entity->replaceComponent<TLogicBoardComponent>(this);

		placeChip(Entity->getComponentAsPtr<TChipComponent>());
	}

	void TLogicBoardComponent::placeTrack(TConductiveTracks* Track)
	{
		mTrackVector.push_back(Track);
	}

	void TLogicBoardComponent::placeTrack(TEntity* Entity)
	{
		Entity->replaceComponent<TLogicBoardComponent>(this);

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
		// Copy the pointer to the drawable component
// 		mDrawableComponent = mParent->getComponentAsPtr<TDrawableComponent>();
// 
// 		// Get a ref to the vertex array
// 		auto& VertexArray = mDrawableComponent->getVertexArray();
// 
// 		// Get a ref to the window size
// 		auto& WindowSize = static_cast<sf::Vector2f>(mParent->getSceneManager().getRenderWindow().getSize());
// 
// 		VertexArray.resize(4);
// 		VertexArray[0] = sf::Vertex({ 0.f, 0.f }, sf::Color::Blue);
// 		VertexArray[1] = sf::Vertex({ WindowSize.x, 0.f }, sf::Color::Blue);
// 		VertexArray[2] = sf::Vertex({ WindowSize.x, WindowSize.y }, sf::Color::Blue);
// 		VertexArray[3] = sf::Vertex({ 0.f, WindowSize.y }, sf::Color::Blue);
	}

}