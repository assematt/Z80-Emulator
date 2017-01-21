#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TWidget.h"
#include "TImageButton.h"

namespace nne
{
	namespace tgui
	{

		class TDebugWindow : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TDebugWindow>;

			TDebugWindow();
			~TDebugWindow();

			/// Set the widget position
			void setPosition(const float& X, const float& Y);
			void setPosition(const sf::Vector2f& Position);

			/// Get the size of the DialogWindow
			virtual void setSize(const sf::Vector2u& Size) override;

			/// Set/Get the debug message 
			void setDebugText(const std::string& Message);
			std::string getDebugText();

			/// Set/Get the title
			void setTitleString(const std::string& Title);
			const std::string& getTitleString() const;

			/// Show the dialog window
			void show(const sf::RenderWindow& ReferenceWindow, const TReferencePoint& Position = TReferencePoint::CENTER);
			void show(const sf::Vector2f& Position);

			void close(const bool& RemoveAfterClosing = false);

		private:
			void draw(sf::RenderTarget& Target, sf::RenderStates States) const;
					
			/// Make sure that all the letters are in Uppercase
			std::string transforText(const std::string& TextToTransform);

		private:
			sf::Text			mDialogTitleText;		// sf::Text object that renders the DialogWindow title
			sf::Text			mDebugText;				// sf::Text object that renders the DialogWindow debug message
			std::string			mDialogTitleString;		// std::string object that stores the original DialogWindow title (since the sf::Text string it's transformed to all uppercase)

			sf::RectangleShape	mDialogMainBackground;
			sf::RectangleShape	mDialogHeaderBackground;
		};
	}
}