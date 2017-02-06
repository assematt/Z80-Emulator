#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <map>

#include "TValues.h"

namespace nne
{
	namespace tcomponents
	{
		struct TPin;
	}

	using namespace tcomponents;

	using TPinBusIndex = std::size_t;
	using TPinList = std::vector<TPin>;
	using TPinBus = std::pair<TPinList::iterator, TPinList::iterator>;

	namespace TPinComponentUtility
	{
		void connectPins(TPin& LeftPin, TPin& RightPin);
		void connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
		void connectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

		void detachPins(TPin& LeftPin, TPin& RightPin);
		void detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
		void detachPins(const TPinBus& LeftBus, const TPinBus& RightBus);

		/// Update the status of the connected PINs based on their type
		void updatePinStatus(TPin& LeftPin, TPin& RightPin);
	}

	namespace tcomponents
	{

		struct TPin
		{
			using TPinPtr = std::shared_ptr<TPin>;
			using TPinID = std::size_t;
			using TPinName = std::string;
			using TPinNumber = TU8BitValue;
			using TPinGroupID = std::size_t;
			/// OLD
			//using TPinConnections = std::vector<TPin*>;
			using TPinConnections = std::unordered_set<TPin*>;
			
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

			// Copy constructor
			TPin(const TPin& Copy);

			// Move constructor
			TPin(TPin&& Move);

			~TPin();

			/// Comparison operator
			bool operator ==(const TPin& Right);
			bool operator !=(const TPin& Right);

			/// Comparison operator
			bool operator ==(const TStatus& Right);
			bool operator !=(const TStatus& Right);

			/// TStatus cast operator
			operator TStatus();
			operator const TStatus() const;

			/// Function to change the pin status
			void changePinStatus(const TStatus& NewStatus, bool Propagate = false);

			/// Function to update the pin owner name
			void setPinParent(const std::string& ParentName);
			const std::string& getPinParent() const;

			/// Explicit member assignment
			TStatus getPinStatus();
			const TStatus getPinStatus() const;

			/// Get Pin ID
			const TPinID& getPinID() const;

			/// create a connection between this pin and another Pin
			void addConnections(TPin& RightPin);

			/// Return true if the PIN it's connected to at least another PIN
			bool hasConnections() const;

			/// Remove a connection between this pin and another PIN
			void removeConnection(TPin& RightPin);

			/// Return the vector with all the connections
			const TPinConnections& getPinConnections() const;

			/// Check if this PIN it's valid, meaning that is not the "NotFound" PIN
			bool isValid();

			/// STATIC FUNCTIONS
			/// Connect a single Pin to another single pin or multiple pin
			friend void TPinComponentUtility::connectPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::connectPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::connectPins(const TPinBus& LeftBus, const TPinBus& RightBus);

			/// Function to detach pin
			friend void TPinComponentUtility::detachPins(TPin& LeftPin, TPin& RightPin);
			friend void TPinComponentUtility::detachPins(TPin& LeftPin, std::initializer_list<TPin>& RightPins);
			friend void TPinComponentUtility::detachPins(const TPinBus& LeftBus, const TPinBus& RightBus);


		public:
			/// Get a pin by ID
			static TPin& getPinByID(const TPinID& ID);
			static TPin& getPinByName(const std::string& PinName, const std::string& ParentEntity);

			static const std::vector<TPin*> getGlobalPinVector();

		private:
			static TPinID generateID();

		private:
			static std::vector<TPin*> mPinVectors;
			
		private:
			friend TPin::TStatus logicAnd(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicOr(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicNot(const TPin::TStatus& Pin);
			friend TPin::TStatus logicNand(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicNor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicXor(const TPin::TStatus& Left, const TPin::TStatus& Right);
			friend TPin::TStatus logicXnor(const TPin::TStatus& Left, const TPin::TStatus& Right);

		public:
			TMode				mPinMode;
			TPinName			mPinName;
			TPinNumber			mPinNumber;
			TPinNumber			mPinGroupNumber;
			TPinGroupID			mPinGroupID;

		private:
			TPinID				mPinID;			
			TStatus				mPinStatus;
			TPinConnections		mPinConnections;
			mutable std::string	mParentName;
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