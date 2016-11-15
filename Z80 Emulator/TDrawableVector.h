#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <utility>
#include <vector>

#include "IComponent.h"
#include "TEntity.h"

namespace nne
{
	class TDrawableVector : public IComponent
	{
	public:	
		
		struct TRenderPair
		{
			TRenderPair(const std::shared_ptr<sf::VertexArray>& Vertices, const sf::Texture* Texture = nullptr);

			const sf::VertexArray& GetVertexArray() const;

			const sf::Texture* GetTexture() const;

			bool IsExpired();

		private:
			std::weak_ptr<sf::VertexArray> mDrawable;
			const sf::Texture* mTexture;
		};

		using Iterator = std::vector<TRenderPair>::iterator;
		using ConstIterator = std::vector<TRenderPair>::const_iterator;

		virtual void Update() override;


		virtual void Refresh() override;

		void PushDrawableObject(const TRenderPair& Drawable);

		virtual void Init() override;

		const std::size_t& GetVectorSize() const;

		/// Helper function for c++11 foreach use
		Iterator& begin();
		Iterator& end();

		/// Subscript operator to access an entity by index
		TRenderPair& operator[] (const int Index);
		const TRenderPair& operator[] (const int Index) const;

	private:
		std::vector<TRenderPair> mDrawablesVector;
		std::size_t mAliveComponets;
	};
}