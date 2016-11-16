#include "TEventContainer.h"


namespace nne
{	
	void TEventContainer::pushEvent(_Event Func)
	{
		mEventList.push_back(std::make_unique<_Event>(Func));
	}
	
	TEventContainer::_Event& TEventContainer::popEvent()
	{
		auto Temp = mEventList.back().release();
		mEventList.pop_back();
	
		return *Temp;
	}
	
	void TEventContainer::processEvent()
	{
		for (auto& Event : mEventList)
		{
			(*Event)();
		}
	}
}
