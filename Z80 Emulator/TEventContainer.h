#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace nne
{
	class TEventContainer
	{
	public:
		using _Event = std::function<void()>;
		using _EventPtr = std::unique_ptr<_Event>;

		TEventContainer() = default;
		TEventContainer(const TEventContainer& Right) = default;
	
		void pushEvent(_Event Func);
	
		_Event& popEvent();
	
		void processEvent();
	
	private:
		std::vector<_EventPtr> mEventList;
	};
}