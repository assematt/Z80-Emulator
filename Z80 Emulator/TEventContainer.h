#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace TInternals
{
	class TEventContainer
	{
	public:
		using _Event = std::function<void()>;
		using _EventPtr = std::unique_ptr<_Event>;
	
		void PushEvent(_Event Func);
	
		_Event& PopEvent();
	
		void ProcessEvent();
	
	private:
		std::vector<_EventPtr> mEventList;
	};
}