#pragma once

#include <SFML/Graphics/Color.hpp>
#include "IComponent.h"
#include "TEntity.h"

namespace nne
{
	class TLedComponent : public IComponent
	{
	public:

		TLedComponent();

		///
		virtual void update(const sf::Time& ElapsedTime) override;

		///
		virtual void refresh(const sf::Time& ElapsedTime) override;

		///
		virtual void init() override;

		/// Return whatever the LED it's on or off
		const bool& isOn() const;

	private:
		/// Render a LED
		void renderLed();

		/// Check the status of the LED (if it is ON or OFF)
		void checkLedStatus();

	private:
		bool		mIsOn;
		sf::Color	mOnColor;
		sf::Color	mOffColor;
	};
}