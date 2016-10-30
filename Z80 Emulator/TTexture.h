#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

#include "IComponent.h"
#include "TTransformable.h"
#include "TEntity.h"

namespace nne
{
	struct TTexture : nne::IComponent
	{
	public:
		TTexture();

		void Init() override {}

		void Update() override {}

// 		void Update(const sf::Time& ElapsedTime) override {};
// 
// 		void Refresh(const sf::Time& ElapsedTime) override {};

		void SetTexture(std::unique_ptr<sf::Texture>& Texture);

		void SetOpacity(sf::Uint8 Opacity);

		bool LoadTextureFromFile(const std::string& Filename);

		const sf::Texture& GetTexture() const;

		const sf::Uint8& GetOpacity() const;

		const sf::VertexArray& GetVertexArray() const;
		sf::VertexArray& GetVertexArray();

	private:
		void SetVertices(float X, float Y, float Width, float Height);

		void SetVertices(const sf::FloatRect& Rect);

	private:
		sf::VertexArray mVertices;
		std::unique_ptr<sf::Texture> mTexture;
		sf::Uint8 mOpacity;
	};
}