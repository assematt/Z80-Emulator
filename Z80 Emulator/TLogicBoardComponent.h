#pragma once

#include <memory>
#include <vector>

#include "IComponent.h"
#include "TDrawableComponent.h"
#include "TChipComponent.h"
#include "TConductiveTracks.h"
#include "TEntity.h"

namespace nne
{

	class TLogicBoardComponent : public IComponent, public std::enable_shared_from_this<TLogicBoardComponent>
	{
	public:

		TLogicBoardComponent();

		virtual void init() override;

		virtual void refresh(const sf::Time& ElapsedTime) override;

		virtual void update(const sf::Time& ElapsedTime) override;

		/// Function to place a component in the board
		void placeChip(TChipComponent* Component);
		void placeChip(TEntity* Entity);

		/// Function to place a track in the board
		void placeTrack(TConductiveTracks* Track);
		void placeTrack(TEntity* Entity);

		void setLogicBoard(TEntity* Entity);

		/// Function to set/get the currently selected component
		void setSelectedChip(TChipComponent* Chip);
		TChipComponent* getSelectedChip() const;
		TChipComponent* getFormerSelectedChip() const;
		void deselectChip(bool DisableFormerChipToo = false);

		/// Function to set/get the currently selected track
		void setSelectedTrack(TConductiveTracks* Track);
		TConductiveTracks* getSelectedTrack() const;
		TConductiveTracks* getFormerSelectedTrack() const;
		void deselectTrack(bool DisableFormerTrackToo = false);

	private:
		TChipComponent*					mSelectedChip;
		TChipComponent*					mFormerSelectedChip;
		TConductiveTracks*				mSelectedTrack;
		TConductiveTracks*				mFormerSelectedTrack;
		std::vector<TChipComponent*>	mComponentVector;
		std::vector<TConductiveTracks*>	mTrackVector;
	};
}