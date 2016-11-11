#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget() :
			mName("Widget" + std::to_string(GetEntityID())),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true)
		{
			Init();
		}

		TGuiWidget::TGuiWidget(const std::string WidgetName) :
			mName(WidgetName),
			mPosition(0.f, 0.f),
			mSize(0, 0),
			mVisible(true)
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

		void TGuiWidget::SetSize(const sf::Vector2i& WidgetSize)
		{
			mSize = WidgetSize;
		}

		const sf::Vector2i& TGuiWidget::GetSize() const
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

		const sf::FloatRect& TGuiWidget::GetWidgetBound() const
		{
			//return{ 0.f, 0.f, 0.f, 0.f };
			return GetComponentAsPtr<TTransformable>()->GetEntityBounds();
			//return HasComponent<TText>() ? GetComponentAsPtr<TText>()->GetGlobalBounds() : sf::FloatRect(GetComponentAsPtr<TTransformable>()->GetPosition(), GetComponentAsPtr<TTransformable>()->GetSize());
		}

		void TGuiWidget::Refresh(const sf::Time& ElapsedTime)
		{
			for (auto& Component : mComponents)
				Component->Refresh();
		}

	}
}

