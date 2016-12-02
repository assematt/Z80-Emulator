#include "TWidgetsContainer.h"
#include "TBasePanel.h"

namespace nne
{
	namespace tgui
	{

		TWidgetsContainer::TWidgetsContainer() :
			mLastAddedPosition(0),
			mContainerPos(0.f, 0.f)
		{
		}

		void TWidgetsContainer::removeWidget(std::size_t Index)
		{
			// If the widget we want to delete is part of a TGuiPanel remove the pointer to the widget we want to delete in there
			auto Parent = mWidgetsContainer[Index]->getPanelParent();
			if (Parent)
			{
				//dynamic_cast<TGuiPanel*>(const_cast<TGuiWidget*>(Parent))->removeWidget(Index);
			}

			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const nne::tgui::TWidget::UniquePtr& TWidgetsContainer::getLastAdded()
		{
			return mWidgetsContainer[mLastAddedPosition];
		}

		const nne::tgui::TWidget::UniquePtr& TWidgetsContainer::getFrontWidget()
		{
			return mWidgetsContainer.back();
		}

		const nne::tgui::TWidget::UniquePtr& TWidgetsContainer::getBackWidget()
		{
			return mWidgetsContainer.front();
		}

		std::vector<TWidget::UniquePtr>::iterator TWidgetsContainer::begin()
		{
			return mWidgetsContainer.begin();
		}

		std::vector<TWidget::UniquePtr>::iterator TWidgetsContainer::end()
		{
			return mWidgetsContainer.end();
		}

		std::vector<nne::tgui::TWidget::UniquePtr>::const_iterator TWidgetsContainer::cbegin()
		{
			return mWidgetsContainer.cbegin();
		}

		std::vector<nne::tgui::TWidget::UniquePtr>::const_iterator TWidgetsContainer::cend()
		{
			return mWidgetsContainer.cend();
		}

		std::vector<TWidget::UniquePtr>::reverse_iterator TWidgetsContainer::rbegin()
		{
			return mWidgetsContainer.rbegin();
		}

		std::vector<TWidget::UniquePtr>::reverse_iterator TWidgetsContainer::rend()
		{
			return mWidgetsContainer.rend();
		}

		std::vector<nne::tgui::TWidget::UniquePtr>::const_reverse_iterator TWidgetsContainer::crbegin()
		{
			return mWidgetsContainer.crbegin();
		}

		std::vector<nne::tgui::TWidget::UniquePtr>::const_reverse_iterator TWidgetsContainer::crend()
		{
			return mWidgetsContainer.crend();
		}

		nne::tgui::TWidget::UniquePtr& TWidgetsContainer::operator[](const int Index)
		{
			return mWidgetsContainer[Index];
		}

		const nne::tgui::TWidget::UniquePtr& TWidgetsContainer::operator[](const int Index) const
		{
			return mWidgetsContainer[Index];
		}

	}
}