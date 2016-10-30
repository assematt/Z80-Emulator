#include "TEventContainer.h"


namespace nne
{	
	void TEventContainer::PushEvent(_Event Func)
	{
		mEventList.push_back(std::make_unique<_Event>(Func));
	}
	
	TEventContainer::_Event& TEventContainer::PopEvent()
	{
		auto Temp = mEventList.back().release();
		mEventList.pop_back();
	
		return *Temp;
	}
	
	void TEventContainer::ProcessEvent()
	{
		for (auto& Event : mEventList)
		{
			(*Event)();
		}
	}
}
