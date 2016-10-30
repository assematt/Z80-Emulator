#pragma once

namespace nne
{
	namespace tcomponents
	{
		namespace TPower
		{
			struct TVoltage
			{
				TVoltage(float Voltage) :
					mVoltage(Voltage)
				{
				}

				float mVoltage;
			};

			struct TCurrent
			{
				TCurrent(float Current) :
					mCurrent(Current)
				{
				}

				float mCurrent;
			};

			struct TResistence
			{
				TResistence(float Resistence) :
					mResistence(Resistence)
				{
				}

				float mResistence;
			};
		}
	}
}