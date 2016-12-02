#include "TWidget.h"
#include "TBasePanel.h"
#include "TDrawableComponent.h"

namespace nne
{
	namespace tgui
	{
		TWidget::TWidget() :
			mName("Widget" + std::to_string(getEntityID())),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true),
			mZIndex(0),
			mParentPanel(nullptr),
			mParentPanelPosition(0)
		{
		}

		TWidget::TWidget(const std::string& WidgetName) :
			mName(WidgetName),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true),
			mZIndex(0),
			mParentPanel(nullptr),
			mParentPanelPosition(0)
		{
		}

		TWidget::TWidget(const TWidget& Copy) :
			mName("Widget" + std::to_string(getEntityID())),
			mPosition(Copy.mPosition),
			mSize(Copy.mSize),
			mVisible(Copy.mVisible),
			mAcceptInput(Copy.mAcceptInput),
			mZIndex(Copy.mZIndex),
			mSignals(Copy.mSignals)
		{
			// When we copy a widget, don't copy the mParentPanel and mParentPanelPosition values
			// but add *this widget to the panel of the object to copy
			// that will set both values inside the addWidget function
			Copy.mParentPanel->addWidget(this);
		}

		TWidget::TWidget(TWidget&& Move) :
			mName(std::move(Move.mName)),
			mPosition(std::move(Move.mPosition)),
			mSize(std::move(Move.mSize)),
			mVisible(std::move(Move.mVisible)),
			mAcceptInput(std::move(Move.mAcceptInput)),
			mZIndex(std::move(Move.mZIndex)),
			mParentPanel(std::move(Move.mParentPanel)),
			mParentPanelPosition(std::move(Move.mParentPanelPosition)),
			mSignals(std::move(Move.mSignals))
		{
		}

		TWidget::~TWidget()
		{

		}

		void TWidget::init()
		{
			
		}
		
		void TWidget::setPanelParent(TBasePanel* WidgetParent)
		{
			mParentPanel = WidgetParent;

			mParentPanel->updateChildWidgetTransformation();
		}

		const TBasePanel* TWidget::getPanelParent() const
		{
			return mParentPanel;
		}

		void TWidget::setName(const std::string& WidgetName)
		{
			mName = WidgetName;
		}

		const std::string& TWidget::getName() const
		{
			return mName;
		}

		void TWidget::setSize(const sf::Vector2u& WidgetSize)
		{
			getComponentAsPtr<TDrawableComponent>()->setSize(WidgetSize);
			mSize = WidgetSize;
		}

		sf::Vector2u TWidget::getSize()
		{
			return mSize;
		}

		void TWidget::setPosition(const sf::Vector2f& Position)
		{
			getComponentAsPtr<TDrawableComponent>()->setPosition(Position);
			mPosition = Position;
		}

		const sf::Vector2f& TWidget::getPosition() const
		{
			return mPosition;
		}

		void TWidget::setColor(const sf::Color& Color)
		{
			getComponentAsPtr<TDrawableComponent>()->setColor(Color);
		}

		const sf::Color& TWidget::getColor() const
		{
			return getComponentAsPtr<TDrawableComponent>()->getColor();
		}

		void TWidget::setZIndex(const ZIndex& WidgetZIndex /*= 0*/)
		{
			mZIndex = WidgetZIndex;
		}

		const nne::tgui::TWidget::ZIndex& TWidget::getZIndex() const
		{
			return mZIndex;
		}

		void TWidget::setVisibility(bool Show /*= true*/)
		{
			mVisible = Show;
		}

		bool TWidget::isVisible()
		{
			return mVisible;
		}

		void TWidget::enableInput()
		{
			mAcceptInput = true;
		}

		void TWidget::disableInput()
		{
			mAcceptInput = false;
		}

		bool TWidget::isInputEnabled()
		{
			return mAcceptInput;
		}

		void TWidget::connectSignal(const tevent::BaseEvent& Function, const tevent::TEventTypes& SignalToConnect)
		{
			mSignals[SignalToConnect] = Function;
		}

		sf::FloatRect TWidget::getLocalBounds()
		{
			return getComponentAsPtr<TDrawableComponent>()->getLocalBounds();
		}

		sf::FloatRect TWidget::getGlobalBounds()
		{
			return getComponentAsPtr<TDrawableComponent>()->getTransform().transformRect(getLocalBounds());
		}

	}
}

