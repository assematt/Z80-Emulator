#include "TText.h"

namespace nne
{

	TText::TText() :
		mNeedsUpdate(false)
	{
		mText = std::make_shared<sf::Text>();
	}

	void TText::Init()
	{
		//mFont = std::make_shared<_TFont>();
		mFont = mParent->GetComponentAsPtr<TFont>();

		if ((mFont->GetFontType() == TFont::TFontType::STANDARD) && (&mFont->mStandardFont))
		{
			mText->setFont(mFont->mStandardFont);
			mParent->GetComponentAsPtr<TDrawableVector>()->PushDrawableObject(mText);
		}
		else
		{

		}
	}

	void TText::Update()
	{

	}

	void TText::Refresh()
	{
		if (!mNeedsUpdate)
			return;

		mNeedsUpdate = false;
		mFont->UpdateTextGeometry(GetString(), GetCharacterSize());
	}

	void TText::SetString(const std::string& String)
	{
		if (GetString() == String)
			return;

		mText->setString(String);
		mString = String;
		mNeedsUpdate = true;
	}

	void TText::SetFont(const TFont& Font)
	{
		if (GetFont() == &Font)
			return;

		//mFont = std::move(Font);
		mNeedsUpdate = true;
	}

	void TText::SetCharacterSize(unsigned int Size)
	{
		if (GetCharacterSize() == Size)
			return;

		mText->setCharacterSize(Size);
		mNeedsUpdate = true;
	}

	void TText::SetStyle(sf::Uint32 Style)
	{
		if (GetStyle() == Style)
			return;

		mText->setStyle(Style);
		mNeedsUpdate = true;
	}

	const sf::Text& TText::GetDrawableText() const
	{
		return *mText;
	}

	void TText::SetFillColor(const sf::Color& Color)
	{
		if (GetFillColor() == Color)
			return;

		mText->setFillColor(Color);
		mNeedsUpdate = true;
	}

	void TText::SetOutlineColor(const sf::Color& Color)
	{
		if (GetOutlineColor() == Color)
			return;

		mText->setOutlineColor(Color);
		mNeedsUpdate = true;
	}

	void TText::SetOutlineThickness(float Thickness)
	{
		if (GetOutlineThickness() == Thickness)
			return;

		mText->setOutlineThickness(Thickness);
		mNeedsUpdate = true;
	}

	const std::string& TText::GetString() const
	{
		return mString;
	}

	const nne::TFont* TText::GetFont() const
	{
		return mFont.get();
	}

	unsigned int TText::GetCharacterSize() const
	{
		return mText->getCharacterSize();
	}

	sf::Uint32 TText::GetStyle() const
	{
		return mText->getStyle();
	}

	const sf::Color& TText::GetFillColor() const
	{
		return mText->getFillColor();
	}

	const sf::Color& TText::GetOutlineColor() const
	{
		return mText->getOutlineColor();
	}

	float TText::GetOutlineThickness() const
	{
		return mText->getOutlineThickness();
	}

	sf::Vector2f TText::findCharacterPos(std::size_t Index) const
	{
		return mText->findCharacterPos(Index);
	}

	sf::FloatRect TText::GetLocalBounds() const
	{
		return { 0.f, 0.f, 0.f, 0.f };
		//return mParent->GetComponentAsPtr<TFont>()->GetFontType() == TFont::TFontType::STANDARD ? mText->getLocalBounds() : sf::FloatRect({ .0f, 0.f }, mParent->GetComponentAsPtr<TTransformable>()->GetSize());
	}

	sf::FloatRect TText::GetGlobalBounds() const
	{
		return{ 0.f, 0.f, 0.f, 0.f };
		//return mParent->GetComponentAsPtr<TFont>()->GetFontType() == TFont::TFontType::STANDARD ? mText->getGlobalBounds() : sf::FloatRect(mParent->GetComponentAsPtr<TTransformable>()->GetPosition(), mParent->GetComponentAsPtr<TTransformable>()->GetSize());
	}

}