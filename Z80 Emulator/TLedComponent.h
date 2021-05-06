#pragma once

#include <SFML/Graphics/Color.hpp>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	class TLedComponent : BASE_COMPONENT_CLASS
	{
	public:

		TLedComponent();

		///
		virtual void update(REFRESH_UPDATE_PARAMETER) override;

		///
		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;

		///
		virtual void init() override;

		/// Return whatever the LED it's on or off
		const bool& isOn() const;

	private:

		/// Check the status of the LED (if it is ON or OFF)
		void checkLedStatus();

	private:
		bool		mIsOn;
		sf::Color	mOnColor;
		sf::Color	mOffColor;
	};
}