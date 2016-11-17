#include "TDrawableComponent.h"

namespace nne
{

	TDrawableComponent::TDrawableComponent() :
		mExternalTexture(nullptr)
	{
	}

	void TDrawableComponent::init()
	{
		mVertexArray = std::make_shared<sf::VertexArray>(sf::Quads, 4);
		mTexture = std::make_shared<sf::Texture>();

		//mParent->getComponentAsPtr<TDrawableVector>()->pushdrawableObject({ mVertexArray, mTexture.get() });
	}

	void TDrawableComponent::setTexture(const sf::Texture& Texture)
	{
		*mTexture = Texture;

		updateSpriteBounds(Texture.getSize());

		updateTextureBounds(sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(Texture.getSize())));
	}

	void TDrawableComponent::setTexture(const sf::Texture* Texture)
	{
		//mTexture.reset(const_cast<sf::Texture*>(Texture));
		mExternalTexture = Texture;
	}

	void TDrawableComponent::setOpacity(sf::Uint8 Opacity)
	{
		auto& VertexArray = *mVertexArray;

		VertexArray[0].color.a = Opacity;
		VertexArray[1].color.a = Opacity;
		VertexArray[2].color.a = Opacity;
		VertexArray[3].color.a = Opacity;
	}

	const sf::Texture& TDrawableComponent::getTexture() const
	{
		return *mTexture;
	}

	void TDrawableComponent::setColor(const sf::Color& Color)
	{
		auto& VertexArray = *mVertexArray;

		VertexArray[0].color = Color;
		VertexArray[1].color = Color;
		VertexArray[2].color = Color;
		VertexArray[3].color = Color;
	}

	const sf::Color& TDrawableComponent::getColor() const
	{
		return (*mVertexArray)[0].color;
	}

	const sf::Uint8& TDrawableComponent::getOpacity() const
	{
		return (*mVertexArray)[0].color.a;
	}

	void TDrawableComponent::setSize(const sf::Vector2u& Size)
	{
		updateSpriteBounds(Size);
	}

	sf::Vector2u TDrawableComponent::getSize()
{
		if (mVertexArray->getVertexCount() == 4)
			return static_cast<sf::Vector2u>((*mVertexArray)[3].position);

		auto Bound = static_cast<sf::Rect<unsigned int>>(computeComplexLocalBound());

		return { Bound.width, Bound.height };
	}

	sf::VertexArray& TDrawableComponent::getVertexArray()
	{
		return *mVertexArray;
	}

	const sf::VertexArray& TDrawableComponent::getVertexArray() const
	{
		return *mVertexArray;
	}

	sf::FloatRect TDrawableComponent::getLocalBounds()
	{
		auto& Position = getPosition();
		sf::Vector2f Size = (*mVertexArray)[2].position;

		return mVertexArray->getVertexCount() == 4 ? sf::FloatRect(Position, Size) : computeComplexLocalBound();
	}

	sf::FloatRect TDrawableComponent::getGlobalBounds()
	{
		return getTransform().transformRect(getLocalBounds());
	}

	void TDrawableComponent::updateTextureBounds(const sf::IntRect& TextureRect)
	{
		auto& VertexArray = *mVertexArray;
		sf::FloatRect TextureBound = static_cast<sf::FloatRect>(TextureRect);

		VertexArray[0].texCoords = { TextureBound.left,  TextureBound.top };
		VertexArray[1].texCoords = { TextureBound.left,  TextureBound.top + TextureBound.height };
		VertexArray[2].texCoords = { TextureBound.left + TextureBound.width, TextureBound.top + TextureBound.height };
		VertexArray[3].texCoords = { TextureBound.left + TextureBound.width, TextureBound.top };
	}

	void TDrawableComponent::updateSpriteBounds(const sf::Vector2u& SpriteSize)
	{
		auto& VertexArray = *mVertexArray;

		VertexArray[0].position = { 0.f, 0.f };
		VertexArray[1].position = { 0.f, static_cast<float>(SpriteSize.y) };
		VertexArray[2].position = { static_cast<float>(SpriteSize.x), static_cast<float>(SpriteSize.y) };
		VertexArray[3].position = { static_cast<float>(SpriteSize.x), 0.f };
	}

	sf::FloatRect TDrawableComponent::computeComplexLocalBound()
{
		float Width = 0.f, Height = 0.f;

		for (std::size_t Index = 0; Index < mVertexArray->getVertexCount(); ++Index)
		{
			auto& VertexPos = (*mVertexArray)[Index].position;

			Width = std::max(Width, VertexPos.x);
			Height = std::max(Height, VertexPos.y);
		}

		return sf::FloatRect(0.f, 0.f, Width, Height);
	}

	void TDrawableComponent::draw(sf::RenderTarget& Target, sf::RenderStates States) const
	{
		// Get the sprite transformation matrix
		States.transform *= getTransform();

		// Set the sprite texture (if we have one)
		if (mExternalTexture)
		{
			States.texture = mExternalTexture;
		}
		else if (mTexture)
		{
			States.texture = mTexture.get();
		}			

		Target.draw(*mVertexArray, States);
	}

}
