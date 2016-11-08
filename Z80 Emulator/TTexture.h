#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

#include "TTransformable.h"
#include "IComponent.h"
#include "TEntity.h"
#include "TResource.h"
//#include "_TResourceOld.h"

namespace nne
{


	class TTexture : public nne::IComponent
	{
	public:
		TTexture();

		void Init() override {}

		void Update() override {}

		void Refresh() override {}

// 		void Update(const sf::Time& ElapsedTime) override {};
// 
// 		void Refresh(const sf::Time& ElapsedTime) override {};

		void SetTexture(sf::Texture& Texture);

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
		sf::Texture mTexture;
		sf::Uint8 mOpacity;
	};

	struct TTextureLoader
	{
		TTextureLoader(const std::string& Path) :
			mPath(Path)
		{
		}

		TResource<TTexture> operator() ()
		{
			std::unique_ptr<TTexture> TempPtr = std::make_unique<TTexture>();
			TempPtr->LoadTextureFromFile(mPath);
			return TempPtr;
		}

	private:
		std::string mPath;
	};
}