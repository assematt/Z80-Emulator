#include "TTexture.h"

namespace nne
{

	TTexture::TTexture() :
		mVertices(sf::Quads, 4)
	{
		mTexture = std::make_unique<sf::Texture>();
		mTexture->setSmooth(true);
	}

	void TTexture::SetTexture(std::unique_ptr<sf::Texture>& Texture)
	{
		mTexture = std::move(Texture);
	}

	void TTexture::SetOpacity(sf::Uint8 Opacity)
	{
		mOpacity = Opacity;

		auto NumOfVertices = mVertices.getVertexCount();

		for (int Index = 0; Index < NumOfVertices; ++Index)
		{
			mVertices[Index].color.a = mOpacity;
		}
	}

	bool TTexture::LoadTextureFromFile(const std::string& Filename)
	{
		if (!mTexture->loadFromFile(Filename))
		{
			return false;
		}

		SetVertices(0, 0, mTexture->getSize().x, mTexture->getSize().y);

		return true;
	}

	const sf::Texture& TTexture::GetTexture() const
	{
		return *mTexture.get();
	}

	const sf::Uint8& TTexture::GetOpacity() const
	{
		return mOpacity;
	}

	const sf::VertexArray& TTexture::GetVertexArray() const
	{
		return mVertices;
	}

	sf::VertexArray& TTexture::GetVertexArray()
	{
		return mVertices;
	}

	void TTexture::SetVertices(float X, float Y, float Width, float Height)
	{
		SetVertices({ X, Y, Width, Height });
	}

	void TTexture::SetVertices(const sf::FloatRect& Rect)
	{
		mVertices[0].position = { Rect.left, Rect.top };
		mVertices[1].position = { Rect.left + Rect.width, Rect.top };
		mVertices[2].position = { Rect.left + Rect.width, Rect.top + Rect.height };
		mVertices[3].position = { Rect.left, Rect.top + Rect.height };

		mVertices[0].texCoords = { Rect.left, Rect.top };
		mVertices[1].texCoords = { Rect.left + Rect.width, Rect.top };
		mVertices[2].texCoords = { Rect.left + Rect.width, Rect.top + Rect.height };
		mVertices[3].texCoords = { Rect.left, Rect.top + Rect.height };
	}
}
