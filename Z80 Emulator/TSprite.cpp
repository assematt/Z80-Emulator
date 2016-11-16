#include "TSprite.h"

namespace nne
{

	TSprite::TSprite() :
		mOpacity(255)
	{
	}

	void TSprite::init()
{
		mVertexArray = std::make_shared<sf::VertexArray>(sf::TriangleStrip, 4);
		mTexture = std::make_shared<sf::Texture>();

		mParent->getComponentAsPtr<TdrawableVector>()->pushdrawableObject({ mVertexArray, mTexture.get() });
	}

	void TSprite::setTexture(const sf::Texture& Texture)
	{
		*mTexture = Texture;

		updateTextureBounds(static_cast<sf::Vector2f>(Texture.getSize()));
	}

	void TSprite::setOpacity(sf::Uint8 Opacity)
	{
		mOpacity = Opacity;

		(*mVertexArray)[0].color *= { 255, 255, 255, Opacity };
		(*mVertexArray)[1].color *= { 255, 255, 255, Opacity };
		(*mVertexArray)[2].color *= { 255, 255, 255, Opacity };
		(*mVertexArray)[3].color *= { 255, 255, 255, Opacity };
	}

	const sf::Texture& TSprite::getTexture() const
	{
		return *mTexture;
	}

	const sf::Uint8& TSprite::getOpacity() const
	{
		return mOpacity;
	}

	void TSprite::setSize(const sf::Vector2u& Size)
	{
		(*mVertexArray)[0].position = { 0.f, 0.f };
		(*mVertexArray)[1].position = { 0.f, static_cast<float>(Size.y) };
		(*mVertexArray)[2].position = { static_cast<float>(Size.x), 0.f };
		(*mVertexArray)[3].position = { static_cast<float>(Size.x), static_cast<float>(Size.y) };
	}

	const sf::Vector2u& TSprite::getSize() const
	{
		return static_cast<sf::Vector2u>((*mVertexArray)[3].position);
	}

	void TSprite::updateTextureBounds(const sf::Vector2f& NewTextureSize)
	{
		(*mVertexArray)[0].texCoords = { 0.f, 0.f };
		(*mVertexArray)[0].position = { 0.f, 0.f };

		(*mVertexArray)[1].texCoords = { 0.f, NewTextureSize.y };
		(*mVertexArray)[1].position = { 0.f, NewTextureSize.y };

		(*mVertexArray)[2].texCoords = { NewTextureSize.x, 0.f };
		(*mVertexArray)[2].position = { NewTextureSize.x, 0.f };

		(*mVertexArray)[3].texCoords = { NewTextureSize.x, NewTextureSize.y };
		(*mVertexArray)[3].position = { NewTextureSize.x, NewTextureSize.y };
	}

}
