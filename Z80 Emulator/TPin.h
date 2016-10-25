#pragma once

#include <memory>
#include <vector>
#include "TValues.h"

namespace TGame
{
	namespace TComponents
	{
		struct TPinComponent;

		struct TPin
		{
			using TPinPtr = std::shared_ptr<TPin>;
			using TPinNumber = TU8BitValue;
			using TPinGroupID = TU8BitValue;
			using TPinConnections = std::vector<TPin*>;
			
			enum TStatus : TU8BitValue
			{
				LOW,
				HIGH,
				HIGH_Z
			};

			enum class TMode : TU8BitValue
			{
				INPUT,
				OUTPUT,
				INPUT_OUTPUT,
				POWER,
				CLOCK
			};

			TPin();

			TPin(const TMode& PinMode, const TStatus& PinStatus = TStatus::LOW, const TPinNumber& PinNumber = 0, const TPinGroupID& PinGroupID = 0, const TPinNumber& PinGroupNumber = 0);

			/// Comparison operator
			bool operator ==(TPin const& Right);
			bool operator !=(TPin const& Right);

			/// Masked member assignment
			TPin& TPin::operator =(const TStatus& Right);

			/// Explicit member assignment
			TStatus GetPinStatus();
			const TStatus GetPinStatus() const;

		private:
			friend TPin::TStatus LogicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus LogicOr(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus LogicNot(const TPin::TStatus& Pin);
			friend TPin::TStatus LogicNand(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus LogicNor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus LogicXor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus LogicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right);

		public:
			TMode	mPinMode;
			TPinNumber mPinNumber;
			TPinNumber mPinGroupNumber;
			TPinGroupID mPinGroupID;
			TPinConnections mPinConnections;

		private:
			TStatus	mPinStatus;
		};
	
		TPin::TStatus LogicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus LogicOr(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus LogicNot(const TPin::TStatus& Pin);
		TPin::TStatus LogicNand(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus LogicNor(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus LogicXor(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus LogicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right);
	}
}