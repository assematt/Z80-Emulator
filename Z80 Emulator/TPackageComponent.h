#pragma once

#include <SFML/Graphics/Color.hpp>

#include "IComponent.h"
#include "TTextComponent.h"
#include "TEntity.h"

namespace nne
{
	class TPackageComponent : public IComponent
	{
	public:

		TPackageComponent();

		///
		virtual void update(const sf::Time& ElapsedTime) override;

		///
		virtual void refresh(const sf::Time& ElapsedTime) override;

		///
		virtual void init() override;

		/// Check if the chip is powered on or not
		const bool& isPoweredOn() const;

		void updateChipName();

	private:

		/// Render a chip in the DIP format
		void renderDipChip();

		/// Check the status of the package (if it is ON or OFF)
		void checkPowerStatus();

		/// 
		void renderPins(const sf::Vector2f& PinSize, const sf::Vector2f& ChipPosition, const sf::Vector2f& ChipSize);

		/// 
		void renderPinLabels(const sf::Vector2f& PinSize, const sf::Vector2f& ChipPosition, const sf::Vector2f& ChipSize);

		/// 
		void renderChipName(const std::string& ChipName, const sf::Vector2f& ChipSize);

		/// 
		float getStringLength(const TTextComponent& Text, const sf::String& String);

	private:
		bool		mIsPowered;
		sf::Color	mPackageColor;
	};
}
