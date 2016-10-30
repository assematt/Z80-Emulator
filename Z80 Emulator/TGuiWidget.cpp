#include "TGuiWidget.h"

namespace nne
{
	namespace tgui
	{
		TGuiWidget::TGuiWidget()
		{
			Init();
		}

		void TGuiWidget::Init()
		{
			AddComponent<TTexture>();
			AddComponent<TTransformable>();
			AddComponent<TFont>();
			GetComponentAsPtr<TTexture>()->LoadTextureFromFile("resources/images/font.png");
			InitComponents();
		}
	}
}

