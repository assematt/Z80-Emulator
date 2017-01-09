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

	private:

		/// Render a chip in the DIP format
		void renderDipChip();

	};
}
