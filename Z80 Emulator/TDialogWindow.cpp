#include "TDialogWindow.h"

#include <SFML/Graphics/Texture.hpp>
#include <locale>

#include "TCacheManager.h"
#include "TGuiManager.h"

namespace nne
{
	
	namespace tgui
	{

		TDialogWindow::TDialogWindow(TGuiManager& GuiManager) :
			mDialogHeaderBackground({ 500.f, 35.f }),
			mDialogFooterBackground({ 500.f, 35.f }),
			mDialogMainBackground({ 500.f, 330.f }),
			TWidget(GuiManager)
		{
			TWidget::setPosition(0.f, 0.f);
			TWidget::setSize({ 1600u, 900u });
			TWidget::setColor({ 0u, 0u, 0u, 191 });
			TWidget::setVisible(false);

			// Load the text font
			mDialogTitleText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mDialogMessageText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));

			// Sample title text
			mDialogTitleText.setCharacterSize(16u);
			mDialogTitleText.setFillColor(sf::Color::White);
			setTitleString("Title");
			
			// Sample message text
			mDialogMessageText.setCharacterSize(15u);
			mDialogMessageText.setFillColor(sf::Color::Black);
			setMessageString("Message");

			// Footer button
			mExitButton = std::make_shared<TImageButton>();
			mExitButton->setName("DIALOG_EXIT_BUTTON");
			mExitButton->setCaption("EXIT");
			mExitButton->setCharacterSize(16u);
			mExitButton->setColor(sf::Color::Transparent);
			mExitButton->addImage(TCacheManager::getInstance().getResource<sf::Texture>("exit_dialog"), { -30.f, 3.f });
			mExitButton->setFillColor(sf::Color::White);
			mExitButton->setParent(this);
			mExitButton->attachEvent(events::onMouseUp, [&](TWidget* Sender, const sf::Event& EventData) {
				close(true);
			});
			mExitButton->addToManager(mExitButton, &GuiManager, 20);
			
			// Header/Footer 
			mDialogHeaderBackground.setFillColor({ 170u, 0u, 0u });
			mDialogFooterBackground.setFillColor({ 170u, 0u, 0u });

			// Main text background
			mDialogMainBackground.setFillColor({ 170u, 170u, 170u });
			mDialogMainBackground.setOutlineColor({ 170u, 0u, 0u });
			mDialogMainBackground.setOutlineThickness(-11.f);
		}

		TDialogWindow::~TDialogWindow()
		{
			
		}

		void TDialogWindow::setPosition(const sf::Vector2f& Position)
		{
			// Update background position
			mDialogHeaderBackground.setPosition(Position.x, Position.y + 0.f);
			mDialogMainBackground.setPosition(Position.x, Position.y + mDialogHeaderBackground.getSize().y - 11.f);
			mDialogFooterBackground.setPosition(Position.x, Position.y + mDialogHeaderBackground.getSize().y + mDialogMainBackground.getSize().y - 22.f);

			// Update text position
			mDialogTitleText.setPosition(Position.x + 10.f, Position.y + 8.f);
			mDialogMessageText.setPosition(Position.x + 24.f, Position.y + 46.f);
			mExitButton->setPosition(Position.x + 453.f, Position.y + mDialogMainBackground.getSize().y + mDialogFooterBackground.getSize().y - 12.f);
		}

		void TDialogWindow::setPosition(const float& X, const float& Y)
		{
			setPosition({ X, Y });
		}

		sf::Vector2f TDialogWindow::getSize() const
		{
			float Width = mDialogHeaderBackground.getSize().x;
			float Height = mDialogHeaderBackground.getSize().y + mDialogMainBackground.getSize().y + mDialogFooterBackground.getSize().y;

			return{ Width, Height };
		}

		void TDialogWindow::setTitleString(const std::string& Title)
		{
			mDialogTitleString = Title;

			mDialogTitleText.setString(transforText(Title));
			adjustText(mDialogTitleText, sf::FloatRect(0.f, 0.f, 450.f, 350.f));
		}

		const std::string& TDialogWindow::getTitleString() const
		{
			return mDialogTitleString;
		}

		void TDialogWindow::setMessageString(const std::string& Message)
		{
			mDialogMessageString = Message;

			mDialogMessageText.setString(transforText(Message));
			adjustText(mDialogMessageText, sf::FloatRect(0.f, 0.f, 450.f, 350.f));

			// Update the size of the dialog background
			auto MessegeHeight = mDialogMessageText.getLocalBounds().height;
			mDialogMainBackground.setSize({ 500.f, MessegeHeight + 28.f + 22.f });
		}

		const std::string& TDialogWindow::getMessageString() const
		{
			return mDialogMessageString;
		}

		void TDialogWindow::show(const sf::RenderWindow& ReferenceWindow, const TReferencePoint& Position /*= TReferencePoint::CENTER*/)
		{
			auto WindowSize = ReferenceWindow.getSize();
			auto DialogSize = getSize();

			switch (Position)
			{
			case TReferencePoint::LEFT_TOP:
				show({ 0.f, 0.f });
				break;
			case TReferencePoint::CENTER_TOP:
				show({ WindowSize.x / 2.f - DialogSize.x / 2.f, 0.f });
				break;
			case TReferencePoint::RIGHT_TOP:
				show({ WindowSize.x - DialogSize.x, 0.f });
				break;

			case TReferencePoint::LEFT_CENTER:
				show({ 0.f, WindowSize.y / 2.f - DialogSize.y / 2.f });
				break;
			case TReferencePoint::CENTER:
				show({ WindowSize.x / 2.f - DialogSize.x / 2.f, WindowSize.y / 2.f - DialogSize.y / 2.f });
				break;
			case TReferencePoint::RIGHT_CENTER:
				show({ WindowSize.x - DialogSize.x, WindowSize.y / 2.f - DialogSize.y / 2.f });
				break;

			case TReferencePoint::LEFT_BOTTOM:
				show({ 0.f, WindowSize.y - DialogSize.y });
				break;
			case TReferencePoint::CENTER_BOTTOM:
				show({ WindowSize.x / 2.f - DialogSize.x / 2.f, WindowSize.y - DialogSize.y });
				break;
			case TReferencePoint::RIGHT_BOTTOM:
				show({ WindowSize.x - DialogSize.x, WindowSize.y - DialogSize.y });
				break;
			}
		}

		void TDialogWindow::show(const sf::Vector2f& Position)
		{
			setPosition(Position);
			TWidget::setVisible(true);
		}

		void TDialogWindow::close(const bool& RemoveAfterClosing /*= false*/)
		{
			TWidget::setVisible(false);

			if (RemoveAfterClosing)
			{
				kill();
				mExitButton->kill();
			}
		}

		void TDialogWindow::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// Skip the rendering if we are not showing the widget
			if (!isVisible())
				return;
			
			TWidget::draw(Target, States);

			// Apply the widget transform
			States.transform *= getParentTransform();

			// Draw background
			Target.draw(mDialogMainBackground, States);
			Target.draw(mDialogHeaderBackground, States);
			Target.draw(mDialogFooterBackground, States);

			// Draw text
			Target.draw(mDialogTitleText, States);
			Target.draw(mDialogMessageText, States);
		}

		void TDialogWindow::adjustText(sf::Text& Text, sf::FloatRect& Bound)
		{
			// Lenght of the string
			auto StrLenght = Text.getString().getSize();

			// If the string it's empty skip the rest of the function
			if (StrLenght == 0)
				return;

			// Get the string stored by sf::Text
			auto StrData = Text.getString();

			float LineWidth = 0.f;

			for (auto Index = 0u; Index < StrLenght - 1; ++Index)
			{
				char CurrentChar = StrData[Index];

				// If the char it's a new line char reset the linewidth value (since we are gonna start from scratch) and skip the rest of this loop cycle
				if (CurrentChar == '\n')
				{
					LineWidth = 0.f;
					
					continue;
				}
								
				// Add the char size to the line total
				LineWidth += Text.getFont()->getGlyph(CurrentChar, Text.getCharacterSize(), Text.getStyle() == sf::Text::Bold).advance;

				// If the char will make the line overflow put a newline character
				if (LineWidth > Bound.width)
				{
					// Put a new line char in the string
					StrData.insert(Index + 1, "\n");

					// Update the string lentgh
					++StrLenght;

					// Reset the value of the linewidth
					LineWidth = 0.f;
					
					// Increment index to avoid referring to the newly added '\n' char
					++Index;

					// If the next char it's a space remove it
					if (StrData[Index + 1] == ' ')
					{
						StrData.erase(Index + 1);
						--StrLenght;
					}
						
				}

			}

			Text.setString(StrData);
		}

		std::string TDialogWindow::transforText(const std::string& TextToTransform)
		{
			std::string TempStr;
			for (auto& Char : TextToTransform)
				TempStr += std::toupper(Char, std::locale());

			return TempStr;
		}

	}
}