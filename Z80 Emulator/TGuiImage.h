#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"

namespace nne
{
	namespace tgui
	{
		class TGuiImage : public TGuiWidget
		{
		public:
			TGuiImage();

			using UniquePtr = std::unique_ptr<TGuiImage>;
			using SharedPtr = std::shared_ptr<TGuiImage>;

			/// Init function
			void init();

			virtual void refresh(const sf::Time& ElapsedTime) override;

			virtual void update(const sf::Time& ElapsedTime) override;

			/// Functions to change the widget property
			void SetImage(const sf::Texture& Image);
			const sf::Texture& GetImage() const;

			/// Functions to get/set the widget size
			virtual void setSize(const sf::Vector2u& Size) override;
			virtual const sf::Vector2u& getSize() const override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}