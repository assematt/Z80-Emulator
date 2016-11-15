#pragma once

#include "TGuiWidget.h"
#include "IComponent.h"
#include "TFont.h"
#include "TTransformable.h"
#include "TText.h"

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
			void Init();

			virtual void Refresh(const sf::Time& ElapsedTime) override;

			virtual void Update(const sf::Time& ElapsedTime) override;

			/// Functions to change the widget property
			void SetImage(const sf::Texture& Image);
			const sf::Texture& GetImage() const;

			/// Functions to get/set the widget size
			virtual void SetSize(const sf::Vector2u& Size) override;
			virtual const sf::Vector2u& GetSize() const override;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}