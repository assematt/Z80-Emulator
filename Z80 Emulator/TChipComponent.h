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

		static const std::size_t None;
		static const sf::Color PinColorNormal;
		static const sf::Color PinColorHover;
		static const sf::Color PinColorSelected;

		static const sf::Color PinColorStatusLow;
		static const sf::Color PinColorStatusHigh;
		static const sf::Color PinColorStatusHighZ;

		TChipComponent(TEntity* ManagedObject);

		void init() override;

		void update(const sf::Time& ElapsedTime) override;

		void refresh(const sf::Time& ElapsedTime) override;

		/// Function to set the color for all the pins in the chip
		void setPinsColor(const sf::Color& Color);

		/// Function to set the color for one specific pin in the chip
		void setPinColor(const sf::Color& Color, const std::size_t& PinIndex);

		/// Return the selected pin color
		const sf::Color& getPinColor(const std::size_t& PinIndex) const;

		/// Return the selected pin color as an unsigned 32 bit integer for fast comparison
		sf::Uint32 getPinColor(const std::size_t& PinIndex);

		sf::FloatRect getPinLocalBounds(const std::size_t& PinIndex);
		sf::FloatRect getPinGlobalBounds(const std::size_t& PinIndex);

		void deselectPin();
		const std::size_t& getSelectedPinNumber() const;

		// Get the selected pin
		tcomponents::TPin& getSelectedPin();
		const tcomponents::TPin& getSelectedPin() const;

	private:
		/// Render a chip in the DIP format
		void renderDipChip();

		/// Because the pin size can be negative due to the fact vertex array data is relative to the main we have to do some math to figure out the pin real size
		sf::Vector2f computePinSize(const std::size_t& PinIndex);

		/// Check if we clicked on a pin and return that pin index
		bool checkMouseClickOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos);

		/// Check if we clicked on a pin and return that pin index
		bool checkMouseOverOnPin(const sf::FloatRect& PinBound, const sf::Vector2f& MousePos);

		/// Create an array of 4 vertices with the appropriate size, position and color based on the passed argument
		const std::array<sf::Vertex, 4> createPin(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Color& Color);

	private:
		std::size_t			mPreviousOverPin;
		std::size_t			mOverPin;
		std::size_t			mPreviousSelectedPin;
		std::size_t			mSelectedPin;
		nne::TEntity*		mManagedObject;
		sf::Vector2u		mChipSize;
		TTextComponent*		mLabels;
		TDrawableComponent*	mDrawableComponent;
	};
}