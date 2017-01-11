#pragma once

#include <SFML/Graphics/Color.hpp>

#include "IComponent.h"
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

	private:

		/// Render a chip in the DIP format
		void renderDipChip();

		/// Check the status of the package (if it is ON or OFF)
		void checkPowerStatus();

	private:
		bool		mIsPowered;
		sf::Color	mPackageColor;
	};
}
