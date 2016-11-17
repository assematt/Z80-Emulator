#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget() :
			mName("Widget" + std::to_string(getEntityID())),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true)
		{
			init();
		}

		TGuiWidget::TGuiWidget(const std::string WidgetName) :
			mName(WidgetName),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true)
		{
			init();
		}

		TGuiWidget::~TGuiWidget()
		{

		}

		void TGuiWidget::init()
		{
			
		}

		void TGuiWidget::update(const sf::Time& ElapsedTime)
		{
			for (auto& Component : mComponents)
				Component->update();
		}

		void TGuiWidget::setName(const std::string& WidgetName)
		{
			mName = WidgetName;
		}

		const std::string& TGuiWidget::getName() const
		{
			return mName;
		}

		void TGuiWidget::setSize(const sf::Vector2u& WidgetSize)
		{
			mSize = WidgetSize;
		}

		const sf::Vector2u& TGuiWidget::getSize() const
		{
			return mSize;
		}

		void TGuiWidget::setPosition(const sf::Vector2f& WidgetSize)
		{
			getComponentAsPtr<TDrawableComponent>()->setPosition(WidgetSize);
			mPosition = WidgetSize;
		}

		const sf::Vector2f& TGuiWidget::getPosition() const
		{
			return mPosition;
		}

		void TGuiWidget::setVisibility(bool Show /*= true*/)
		{
			mVisible = Show;
		}

		bool TGuiWidget::isVisible()
		{
			return mVisible;
		}

		void TGuiWidget::enableInput()
		{
			mAcceptInput = true;
		}

		void TGuiWidget::disableInput()
		{
			mAcceptInput = false;
		}

		bool TGuiWidget::isInputEnabled()
		{
			return mAcceptInput;
		}

		void TGuiWidget::connectSignal(const tevent::BaseEvent& Function, const tevent::TEventTypes& SignalToConnect)
		{
			mSignals[SignalToConnect] = Function;
		}

		sf::FloatRect TGuiWidget::getLocalBounds()
		{
			return getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
		}

		sf::FloatRect TGuiWidget::getGlobalBounds()
		{
			return getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getLocalBounds());
		}

		void TGuiWidget::refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Component : mComponents)
				Component->refresh();
		}

	}
}

