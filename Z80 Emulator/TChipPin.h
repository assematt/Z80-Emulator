#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>

#include "TGuiWindow.h"

namespace nne
{
	class TChip;

	class TChipPin
	{
	public:

		TChipPin(TChip* ParentChip);
		TChipPin(TChip* ParentChip, const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Color& Color);
		
		void update();

		void refresh();

		/// Set/Get the pin function
		void setPosition(const sf::Vector2f& Position);
		const sf::Vector2f& getPosition() const;

		/// Set/Get the pin size
		void setSize(const sf::Vector2f& Size);
		const sf::Vector2f& getSize() const;

		/// Set/Get the pin color
		void setColor(const sf::Color& Color);
		const sf::Color& getColor() const;

		/// Get the vertex array
		const std::shared_ptr<sf::VertexArray>& getVertexArray() const;

	private:
		void updateVertexArray(const sf::Vector2f& Position, const sf::Vector2f& Size);

	private:
		nne::TChip*		mParentChip;
		sf::Color		mColor;
		sf::Color		mHoverColor;
		sf::Vector2f	mSize;
		sf::Vector2f	mPosition;
		std::shared_ptr<sf::VertexArray> mPin;
	};
}