#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget() :
			mName("Widget" + std::to_string(GetEntityID())),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true)
		{
			Init();
		}

		TGuiWidget::TGuiWidget(const std::string WidgetName) :
			mName(WidgetName),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true),
			mAcceptInput(true)
		{
			Init();
		}

		TGuiWidget::~TGuiWidget()
		{

		}

		void TGuiWidget::Init()
		{
			
		}

		void TGuiWidget::Update(const sf::Time& ElapsedTime)
		{
			for (auto& Component : mComponents)
				Component->Update();
		}

		void TGuiWidget::SetName(const std::string& WidgetName)
		{
			mName = WidgetName;
		}

		const std::string& TGuiWidget::GetName() const
		{
			return mName;
		}

		void TGuiWidget::SetSize(const sf::Vector2u& WidgetSize)
		{
			mSize = WidgetSize;
		}

		const sf::Vector2u& TGuiWidget::GetSize() const
		{
			return mSize;
		}

		void TGuiWidget::SetPosition(const sf::Vector2f& WidgetSize)
		{
			GetComponentAsPtr<TTransformable>()->SetPosition(WidgetSize);
			mPosition = WidgetSize;
		}

		const sf::Vector2f& TGuiWidget::GetPosition() const
		{
			return mPosition;
		}

		void TGuiWidget::SetVisibility(bool Show /*= true*/)
		{
			mVisible = Show;
		}

		bool TGuiWidget::GetVisibility()
		{
			return mVisible;
		}

		void TGuiWidget::EnableInput()
		{
			mAcceptInput = true;
		}

		void TGuiWidget::DisableInput()
		{
			mAcceptInput = false;
		}

		bool TGuiWidget::IsInputEnabled()
		{
			return mAcceptInput;
		}

		void TGuiWidget::ConnectSignal(const tevent::BaseEvent& Function, const tevent::TEventTypes& SignalToConnect)
		{
			mSignals[SignalToConnect] = Function;
		}

		const sf::FloatRect& TGuiWidget::GetWidgetBound() const
		{
			return GetComponentAsPtr<TTransformable>()->GetBounds();
		}

		void TGuiWidget::Refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Component : mComponents)
				Component->Refresh();
		}

	}
}

