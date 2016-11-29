#include "TWidgetState.h"

namespace nne
{
	namespace tgui
	{

		TWidgetState::TWidgetState() :
			mWidgetState(States::NORMAL)
		{
		}

		void TWidgetState::setWidgetState(const States& WidgetState)
		{
			mWidgetState = WidgetState;

			switch (WidgetState)
			{
			case TWidgetState::States::NORMAL:
				onNormalState();
				break;
			case TWidgetState::States::CLICKED:
				onClickedState();
				break;
			case TWidgetState::States::HOVER:
				onHoverState();
				break;
			case TWidgetState::States::SELECTED:
				onSelectedState();
				break;
			case TWidgetState::States::DISABLED:
				onDisabledState();
				break;
			}
		}

		const TWidgetState::States& TWidgetState::getWidgetState() const
		{
			return mWidgetState;
		}

	}
}