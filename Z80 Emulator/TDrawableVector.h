#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <utility>
#include <vector>

#include "IComponent.h"
#include "TEntity.h"

namespace nne
{
	class TdrawableVector : public IComponent
	{
	public:	
		
		struct TRenderPair
		{
			TRenderPair(const std::shared_ptr<sf::VertexArray>& Vertices, const sf::Texture* Texture = nullptr);

			const sf::VertexArray& getVertexArray() const;

			const sf::Texture* getTexture() const;

			bool isExpired();

		private:
			std::weak_ptr<sf::VertexArray> mdrawable;
			const sf::Texture* mTexture;
		};

		using Iterator = std::vector<TRenderPair>::iterator;
		using ConstIterator = std::vector<TRenderPair>::const_iterator;

		virtual void update() override;
		
		virtual void refresh() override;

		void pushdrawableObject(const TRenderPair& drawable);

		virtual void init() override;

		const std::size_t& getVectorSize() const;

		/// Helper function for c++11 foreach use
		Iterator& begin();
		Iterator& end();

		/// Subscript operator to access an entity by index
		TRenderPair& operator[] (const int Index);
		const TRenderPair& operator[] (const int Index) const;

	private:
		std::vector<TRenderPair> mdrawablesVector;
		std::size_t mAliveComponets;
	};
}