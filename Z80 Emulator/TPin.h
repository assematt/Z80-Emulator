#pragma once

#include <memory>
#include <vector>
#include "TValues.h"

namespace nne
{
	struct TPinComponent;

	namespace tcomponents
	{

		struct TPin
		{
			using TPinPtr = std::shared_ptr<TPin>;
			using TPinID = std::size_t;
			using TPinName = std::string;
			using TPinNumber = TU8BitValue;
			using TPinGroupID = std::size_t;
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

			/// Empty pin for function the return a PIN value 
			static TPin& NotFound;

			TPin();
			
			TPin(const TMode& PinMode, const TPinName& PinName, const TStatus& PinStatus = TStatus::LOW, const TPinNumber& PinNumber = 0, const TPinGroupID& PinGroupID = 0, const TPinNumber& PinGroupNumber = 0);

			/// Comparison operator
			bool operator ==(TPin const& Right);
			bool operator !=(TPin const& Right);

			/// TStatus cast operator
			operator TStatus();
			operator const TStatus() const;

			/// Function to change the pin status
			void changePinStatus(const TStatus& NewStatus, bool Propagate = false);

			/// Explicit member assignment
			TStatus getPinStatus();
			const TStatus getPinStatus() const;

			/// Get Pin ID
			const TPinID& getPinID();

			/// Return true if the PIN it's connected to at least another PIN
			bool hasConnections();

			/// Check if this PIN it's valid, meaning that is not the "NotFound" PIN
			bool isValid();

		private:
			static TPinID generateID();
			
		private:
			friend TPin::TStatus logicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicOr(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicNot(const TPin::TStatus& Pin);
			friend TPin::TStatus logicNand(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicNor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicXor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right);

		public:
			TMode			mPinMode;
			TPinName		mPinName;
			TPinNumber		mPinNumber;
			TPinNumber		mPinGroupNumber;
			TPinGroupID		mPinGroupID;
			TPinConnections	mPinConnections;

		private:
			TStatus	mPinStatus;
			TPinID mPinID;			
		};
	

		TPin::TStatus logicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus logicOr(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus logicNot(const TPin::TStatus& Pin);
		TPin::TStatus logicNand(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus logicNor(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus logicXor(const TPin::TStatus& Left, const TPin::TStatus& Right);
		TPin::TStatus logicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right);
	}
}