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

		/// Get the local/global bound of the chip
		sf::FloatRect getLocalBound() const;
		sf::FloatRect getGlobalBound() const;

		/// Check if this chip is overllapping with another chip
		bool checkCollision(const TChipComponent& Chip);
		const bool& isValid() const;

		/// Function to reset the state of the selected PIN
		void deselectPin();

		/// Return the selected PIN number
		const std::size_t& getSelectedPinNumber() const;

		/// Get the selected pin
		tcomponents::TPin& getSelectedPin();
		const tcomponents::TPin& getSelectedPin() const;

	private:
		/// Render a chip in the DIP format
		void renderDipChip();

		/// Render a LED
		void renderLed();
		
	private:
		bool				mIsPlaced;
		bool				mIsValid;
		sf::Vector2u		mChipSize;
		TTextComponent*		mLabels;
		TDrawableComponent*	mDrawableComponent;
	};
}