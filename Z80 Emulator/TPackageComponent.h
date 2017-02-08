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

		enum class TPackageType
		{
			DIP,
			LED,
			POWER_CONNECTOR,
			CUSTOM
		};

		TPackageComponent();

		///
		virtual void update(const sf::Time& ElapsedTime) override;

		///
		virtual void refresh(const sf::Time& ElapsedTime) override;

		///
		virtual void init() override;

		/// Set the type of package used in this component (will change the look of the component)
		void setPackageType(const TPackageType& PackageType);

		/// Get the type of package currently used to render the component
		const TPackageType& getPackageType() const;

		/// Set/Get the package color
		void setPackageColor(const sf::Color& PackageColor);
		const sf::Color& getPackageColor() const;

		/// Check if the chip is powered on or not
		const bool& isPoweredOn() const;

		/// Update the chip name
		void updateChipName();

		/// Get the local bound with the options to include the bound of the pins instead of just the DIP package
		const sf::FloatRect& getLocalBound(const bool& IncludePinsBound = false) const;

		/// Get the global bound with the options to include the bound of the pins instead of just the DIP package
		sf::FloatRect getGlobalBound(const bool& IncludePinsBound = false) const;

	private:

		/// Compute the size of the package based on the format
		void computeChipSize(const TPackageType& PackageType, const std::size_t& PinsNumber);

		/// Render a chip in the DIP format
		void renderDipChip();

		/// Render a led
		void renderLed();

		/// Render a power connector
		void renderPowerConnector();

		/// Check the status of the package (if it is ON or OFF)
		void checkPowerStatus();

		/// 
		void renderPins(const sf::Vector2f& ChipPosition);

		/// 
		void renderPinLabels(const sf::Vector2f& ChipPosition);

		/// 
		void renderChipName(const std::string& ChipName);

		/// 
		float getStringLength(const TTextComponent& Text, const sf::String& String);

	private:
		bool			mIsPowered;
		sf::Color		mPackageColor;
		TPackageType	mPackageType;
		sf::Vector2f	mPinSize;
		sf::Vector2f	mChipSize;
		sf::FloatRect	mChipBound;
		sf::FloatRect	mChipAndPinsBound;
	};
}
