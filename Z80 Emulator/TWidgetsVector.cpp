#include "TWidgetsVector.h"

namespace nne
{
	namespace tgui
	{

		TWidgetsVector::TWidgetsVector() :
			mLastAddedPosition(0),
			mContainerPos(0.f, 0.f)
		{
		}

		void TWidgetsVector::removeWidget(std::size_t Index)
		{
			mWidgetsContainer.erase(mWidgetsContainer.begin() + Index);
		}

		const nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::getWidget(const std::size_t Index) const
		{
			return mWidgetsContainer[Index];
		}

		const nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::getLastAdded()
		{
			return mWidgetsContainer[mLastAddedPosition];
		}

		const nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::getFrontWidget()
		{
			return mWidgetsContainer.back();
		}

		const nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::getBackWidget()
		{
			return mWidgetsContainer.front();
		}

		std::vector<TGuiWidget::UniquePtr>::iterator TWidgetsVector::begin()
		{
			return mWidgetsContainer.begin();
		}

		std::vector<TGuiWidget::UniquePtr>::iterator TWidgetsVector::end()
		{
			return mWidgetsContainer.end();
		}

		std::vector<nne::tgui::TGuiWidget::UniquePtr>::const_iterator TWidgetsVector::cbegin()
		{
			return mWidgetsContainer.cbegin();
		}

		std::vector<nne::tgui::TGuiWidget::UniquePtr>::const_iterator TWidgetsVector::cend()
		{
			return mWidgetsContainer.cend();
		}

		std::vector<TGuiWidget::UniquePtr>::reverse_iterator TWidgetsVector::rbegin()
		{
			return mWidgetsContainer.rbegin();
		}

		std::vector<TGuiWidget::UniquePtr>::reverse_iterator TWidgetsVector::rend()
		{
			return mWidgetsContainer.rend();
		}

		std::vector<nne::tgui::TGuiWidget::UniquePtr>::const_reverse_iterator TWidgetsVector::crbegin()
		{
			return mWidgetsContainer.crbegin();
		}

		std::vector<nne::tgui::TGuiWidget::UniquePtr>::const_reverse_iterator TWidgetsVector::crend()
		{
			return mWidgetsContainer.crend();
		}

		nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::operator[](const int Index)
		{
			return mWidgetsContainer[Index];
		}

		const nne::tgui::TGuiWidget::UniquePtr& TWidgetsVector::operator[](const int Index) const
		{
			return mWidgetsContainer[Index];
		}

	}
}