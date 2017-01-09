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

		const bool& isOn() const;

	private:
		/// Render a LED
		void renderLed();

	private:
		bool		mIsOn;
		sf::Color	mOnColor;
	};
}