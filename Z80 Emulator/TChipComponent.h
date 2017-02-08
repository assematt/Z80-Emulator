#pragma once

#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>
#include <array>

#include "IComponent.h"
#include "TPinComponent.h"
#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TEntity.h"

namespace nne
{

	class TChipComponent : public IComponent
	{
	public:
		enum class TPackage
		{
			DIP,
			SOIC,
			LQFP
		};
		
		TChipComponent();

		void init() override;

		void update(const sf::Time& ElapsedTime) override;

		void refresh(const sf::Time& ElapsedTime) override;

		/// Toggle the ability to draw the chip
		void setPlacedStatus(const bool& IsPlaced = true);
		const bool& isPlaced() const;

		/// Set/Get chip name
		void setChipName(const std::string& Name);
		const std::string& getName() const;
		
		/// Get the local/global bound of the chip
		sf::FloatRect getLocalBound() const;
		sf::FloatRect getGlobalBound() const;

		/// Check if this chip is overlapping with another chip
		bool checkCollision(const TChipComponent& Chip);
		const bool& isValid() const;

		/// Function to reset the state of the selected PIN
		void deselectPin();
		
		/// Get the selected pin
		tcomponents::TPin& getSelectedPin();
		const tcomponents::TPin& getSelectedPin() const;

		/// Get the hover pin
		const tcomponents::TPin& getHoverPin() const;
				
	private:
		bool				mIsPlaced;
		bool				mIsValid;
		std::string			mChipName;
		sf::Vector2u		mChipSize;
		TTextComponent*		mLabels;
		TDrawableComponent*	mDrawableComponent;
	};
}