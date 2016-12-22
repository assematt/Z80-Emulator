#include "TDrawableComponent.h"
#include "TTextComponent.h"
#include "TLogicBoardComponent.h"
#include "IScene.h"

namespace nne
{

	TDrawableComponent::TDrawableComponent()
	{
	}

	void TDrawableComponent::init()
	{
		mVertexArray = std::make_shared<sf::VertexArray>(sf::Quads, 4);
		mTexture = std::make_shared<sf::Texture>();
	}

	void TDrawableComponent::setTexture(const sf::Texture& Texture, bool UpdateBounds /*= true*/)
	{
		*mTexture = Texture;

		if (UpdateBounds)
		{
			updateSpriteBounds(Texture.getSize());

			updateTextureBounds(sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(Texture.getSize())));
		}		
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

	void TDrawableComponent::setTextureRect(const sf::IntRect& rectangle)
	{
		updateTextureBounds(rectangle);
	}

	const sf::IntRect& TDrawableComponent::getTextureRect() const
	{
		return sf::IntRect();
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

	sf::FloatRect TDrawableComponent::getLocalBounds() const
{
		auto& Position = getPosition();
		sf::Vector2f Size = (*mVertexArray)[2].position;

		return mVertexArray->getVertexCount() == 4 ? sf::FloatRect(Position, Size) : computeComplexLocalBound();
	}

	sf::FloatRect TDrawableComponent::getGlobalBounds() const
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

	sf::FloatRect TDrawableComponent::computeComplexLocalBound() const
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
		auto OldStates = States;
		States.transform *= getTransform();
		
		if (mTexture)
		{
			States.texture = mTexture.get();
		}

		// Draw the basic drawable object
		Target.draw(*mVertexArray, States);

		// If this entity has a Text component draws it on top 
		if (mParent->hasComponent<TTextComponent>())
		{
			States.texture = mParent->getComponentAsPtr<TTextComponent>()->getTexture();

			Target.draw(mParent->getComponentAsPtr<TTextComponent>()->getVertexArray(), States);
		}
	}

}
