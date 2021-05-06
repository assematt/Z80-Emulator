#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>

#include "TValues.h"
#include INCLUDE_COMPONENT_CLASS
#include "TDrawableComponent.h"
#include INCLUDE_ENTITY_CLASS

namespace nne
{
	class TGridComponent : BASE_COMPONENT_CLASS
	{
	public:
		TGridComponent();

		TGridComponent(const sf::Vector2f& Size, const float& ColSize, const float& RowSize);

		void setCellSize(const sf::Vector2f& CellSize);
		const sf::Vector2f& getCellSize() const;

		void setSize(const sf::Vector2f& NewSize);
		const sf::Vector2f& getSize() const;
		
		void setView(const sf::View& AttachedView);

		virtual void update(REFRESH_UPDATE_PARAMETER) override;

		virtual void refresh(REFRESH_UPDATE_PARAMETER) override;

		virtual void init() override;

		sf::Vector2i mouseCoordsToWindowCellCoords(const sf::Vector2i& MousePos);

		sf::Vector2i mouseCoordsToGridCellCoords(const sf::Vector2i& MousePos);

		sf::Vector2f transformCellCoords(const sf::Vector2i& GridCoords);


		sf::Vector2f convertCoordinate(const sf::RenderTarget& Target, const sf::Vector2f& InitialCoor);

		sf::Vector2i getColsRowsNumber();

		sf::Vector2i getColsRowsNumber(const sf::Vector2f& Size);

		void forceRefresh();

	private:
		bool			mNeedsUpdate;
		sf::Uint8		mBuffer;
		const sf::View*	mView;
		sf::Vector2f	mCellSize;
		sf::Vector2f	mSize;
		TDrawableComponent*	mDrawableComponent;
	};
}