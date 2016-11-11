#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

#include "IComponent.h"
#include "TEntity.h"

namespace nne
{
	class TDrawableVector : public IComponent
	{
	public:
		virtual void Update() override
		{
		}


		virtual void Refresh() override
		{
			/// Remove dead entity
			for (std::size_t Index = 0; Index < mDrawablesVector.size(); ++Index)
			{
				if (mDrawablesVector[Index].expired())
					mDrawablesVector.erase(mDrawablesVector.begin() + Index);
			}
		}

		void PushDrawableObject(std::shared_ptr<sf::Drawable> Drawable)
		{
			mDrawablesVector.emplace_back(Drawable);
		}

		virtual void Init() override
		{
		}

		const std::size_t& GetVectorSize() const
		{
			return mDrawablesVector.size();
		}

		/// Helper function for c++11 foreach use
		std::vector<std::weak_ptr<sf::Drawable>>::iterator& begin()
		{
			return mDrawablesVector.begin();
		}
		std::vector<std::weak_ptr<sf::Drawable>>::iterator& end()
		{
			return mDrawablesVector.end();
		}

		/// Subscript operator to access an entity by index
		std::weak_ptr<sf::Drawable>& operator[] (const int Index)
		{
			return mDrawablesVector[Index];
		}
		const std::weak_ptr<sf::Drawable>& operator[] (const int Index) const
		{
			return mDrawablesVector[Index];
		}

	private:
		std::vector<std::weak_ptr<sf::Drawable>> mDrawablesVector;
		std::size_t mAliveComponets;
	};
}