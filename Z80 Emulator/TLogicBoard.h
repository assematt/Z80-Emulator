#pragma once

#include <vector>

#include "TEntity.h"
#include "IComponent.h"

namespace nne
{
	class TLogicBoard
	{
	public:
		void PlaceIntegratedCircuit(TEntity* IntegratedCircuit)
		{
			mIntegratedCircuits.push_back(IntegratedCircuit);
		}
		
		void RemoveIntegratedCircuit(TEntity* IntegratedCircuit)
		{

		}

	private:
		std::vector<TEntity*> mIntegratedCircuits;
	};
}