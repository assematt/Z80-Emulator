#include "TDebugWindow.h"

#include <SFML/Graphics/Texture.hpp>
#include <locale>

#include "TCacheManager.h"
#include "TGuiManager.h"

namespace nne
{

	namespace tgui
	{

		TDebugWindow::TDebugWindow() :
			mDialogHeaderBackground({ 500.f, 35.f }),
			mDialogMainBackground({ 500.f, 330.f })
		{
			TWidget::setSize({ 223u, 300u });
			TWidget::setPosition(0.f, 0.f);
			TWidget::setColor({ 128, 128, 191 });

			// Load the text font
			mDialogTitleText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));
			mDebugText.setFont(TCacheManager::getInstance().getResource<sf::Font>("font_1"));

			// Sample title text
			mDialogTitleText.setCharacterSize(12u);
			mDialogTitleText.setFillColor(sf::Color::White);
			setTitleString("Title");

			// Sample message text
			mDebugText.setCharacterSize(16u);
			mDebugText.setFillColor({ 191, 191, 191 });
			mDebugText.setString("AF:0300    AF':0300\nBC:0000    BC':0000\nDE:0000    DE':0000\nHL:0000    HL':0000\nIX:0000     IY:0000\n I:00        R:00\nSP:4000     PC:0006\n\nA:00 B:00 C:00 D:00\nE:00 F:00 H:00 L:00");

			// Window background
			auto DialogWindowSize = TWidget::getSize();
						
			// Header/Footer 
			mDialogHeaderBackground.setPosition(1.f, 2.f);
			mDialogHeaderBackground.setFillColor({ 64, 68, 102 });
			mDialogHeaderBackground.setSize({ DialogWindowSize.x - 2.f, 20.f });

			// Main text background
			mDialogMainBackground.setFillColor({ 0, 21, 39 });
			mDialogMainBackground.setPosition(1.f, 2.f + DialogWindowSize.y);
			mDialogMainBackground.setSize({ DialogWindowSize.x - 2.f, DialogWindowSize.y - mDialogHeaderBackground.getSize().y - 3.f });
		}

		TDebugWindow::~TDebugWindow()
		{

		}

		void TDebugWindow::setPosition(const sf::Vector2f& Position)
		{
			// Update background position
			TWidget::setPosition(Position);
			mDialogHeaderBackground.setPosition(1.f, 2.f);
			mDialogMainBackground.setPosition(1.f, 2.f + mDialogHeaderBackground.getSize().y);

			// Update text position
			mDialogTitleText.setPosition(23.f, 6.f);
			mDebugText.setPosition(25.f, 40.f);
		}

		void TDebugWindow::setPosition(const float& X, const float& Y)
		{
			setPosition({ X, Y });
		}
		
		void TDebugWindow::setTitleString(const std::string& Title)
		{
			mDialogTitleString = Title;

			mDialogTitleText.setString(transforText(Title));
		}

		const std::string& TDebugWindow::getTitleString() const
		{
			return mDialogTitleString;
		}

		void TDebugWindow::show(const sf::RenderWindow& ReferenceWindow, const TReferencePoint& Position /*= TReferencePoint::CENTER*/)
		{
			auto WindowSize = ReferenceWindow.getSize();
			auto DialogSize = static_cast<sf::Vector2f>(getSize());

			TWidget::setSize(WindowSize);

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

		void TDebugWindow::show(const sf::Vector2f& Position)
		{
			setPosition(Position);
			TWidget::setVisible(true);
		}

		void TDebugWindow::close(const bool& RemoveAfterClosing /*= false*/)
		{
			TWidget::setVisible(false);

			if (RemoveAfterClosing)
			{
				kill();
			}
		}

		void TDebugWindow::setSize(const sf::Vector2u& Size)
		{
			TWidget::setSize(Size);
			mDialogHeaderBackground.setSize({ Size.x - 2.f, 20.f });
			mDialogMainBackground.setSize({ Size.x - 2.f, Size.y - mDialogHeaderBackground.getSize().y - 3.f });
		}

		void TDebugWindow::setDebugText(const std::string& Message)
		{
			mDebugText.setString(transforText(Message));
		}

		std::string TDebugWindow::getDebugText()
		{
			return mDebugText.getString().toAnsiString();
		}

		void TDebugWindow::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// Skip the rendering if we are not showing the widget
			if (!isVisible())
				return;

			TWidget::draw(Target, States);
			
			// Apply the widget transform
			States.transform *= getParentTransform();

			// Draw background
			Target.draw(mDialogHeaderBackground, States);
			Target.draw(mDialogMainBackground, States);

			// Draw text
			Target.draw(mDialogTitleText, States);
			Target.draw(mDebugText, States);
		}

		std::string TDebugWindow::transforText(const std::string& TextToTransform)
		{
			std::string TempStr;
			for (auto& Char : TextToTransform)
				TempStr += std::toupper(Char, std::locale());

			return TempStr;
		}

	}
}