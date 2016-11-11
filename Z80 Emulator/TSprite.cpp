#include "TSprite.h"

namespace nne
{

	TSprite::TSprite()
	{
		mTexture.setSmooth(true);
	}

	void TSprite::Init()
	{
		mSprite = std::make_shared<sf::Sprite>();

		mParent->GetComponentAsPtr<TDrawableVector>()->PushDrawableObject(mSprite);
	}

	void TSprite::SetTexture(sf::Texture& Texture)
	{
		//mTexture = Texture;
		mSprite->setTexture(Texture);
	}

	void TSprite::SetOpacity(sf::Uint8 Opacity)
	{
		mSprite->setColor({ 255, 255, 255, Opacity });
	}

	const sf::Texture& TSprite::GetTexture() const
	{
		return mTexture;
	}

	const sf::Uint8& TSprite::GetOpacity() const
	{
		return mOpacity;
	}

}
