#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget()
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

		void TGuiWidget::Refresh(const sf::Time& ElapsedTime)
		{
			//for (auto& Component : mComponents)
				//Component->();
			for (auto& Component : mComponents)
				Component->Refresh();
		}

	}
}

