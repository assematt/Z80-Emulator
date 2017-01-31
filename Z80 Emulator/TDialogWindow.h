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
		
		class TDialogWindow : public TWidget
		{
		public:
			using Ptr = std::shared_ptr<TDialogWindow>;

			TDialogWindow(TGuiManager& GuiManager);
			~TDialogWindow();

			/// Set the widget position
			void setPosition(const float& X, const float& Y);
			void setPosition(const sf::Vector2f& Position);

			/// Get the size of the DialogWindow
			sf::Vector2f getSize() const;

			/// Set/Get the title
			void setTitleString(const std::string& Title);
			const std::string& getTitleString() const;

			/// Set/Get the message
			void setMessageString(const std::string& Message);
			const std::string& getMessageString() const;

			void show(const sf::RenderWindow& ReferenceWindow, const TReferencePoint& Position = TReferencePoint::CENTER);
			void show(const sf::Vector2f& Position);

			void close(const bool& RemoveAfterClosing = false);

		private:
			void draw(sf::RenderTarget& Target, sf::RenderStates States) const;

			/// Make sure the text fits within the bound of the rectangle
			void adjustText(sf::Text& Text, sf::FloatRect& Bound);

			/// Make sure that all the letters are in Uppercase
			std::string transformText(const std::string& TextToTransform);


		private:
			sf::Text			mDialogTitleText;		// sf::Text object that renders the DialogWindow title
			sf::Text			mDialogMessageText;		// sf::Text object that renders the DialogWindow message
			std::string			mDialogTitleString;		// std::string object that stores the original DialogWindow title (since the sf::Text string it's transformed to all uppercase)
			std::string			mDialogMessageString;	// std::string object that stores the original DialogWindow message (since the sf::Text string it's transformed to all uppercase)
			TImageButton::Ptr	mExitButton;

			sf::RectangleShape	mDialogMainBackground;
			sf::RectangleShape	mDialogHeaderBackground;
			sf::RectangleShape	mDialogFooterBackground;
		};
	}
}