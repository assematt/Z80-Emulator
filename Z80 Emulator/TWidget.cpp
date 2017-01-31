#include "TWidget.h"

#include "TGuiManager.h"

namespace nne
{
	namespace tgui
	{

		TWidget::TWidget() :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsEnabled(true),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(nullptr),
			mParent(nullptr),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>())
		{
			mName = "widget_" + std::to_string(mID);
		}

		TWidget::TWidget(TGuiManager& GuiManager) :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsEnabled(true),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(&GuiManager),
			mParent(nullptr),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>())
		{
			mName = "widget_" + std::to_string(mID);
		}
		
		TWidget::TWidget(const std::string& WidgetName) :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsEnabled(true),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(nullptr),
			mParent(nullptr),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>()),
			mName(WidgetName)
		{
		}

		TWidget::TWidget(TGuiManager& GuiManager, TWidget& Parent) :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsEnabled(true),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(&GuiManager),
			mParent(&Parent),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>())
		{
			mName = "widget_" + std::to_string(mID);
		}

		TWidget::TWidget(TGuiManager& GuiManager, const std::string& WidgetName) :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(&GuiManager),
			mParent(nullptr),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>()),
			mName(WidgetName)
		{
		}

		TWidget::TWidget(TGuiManager& GuiManager, TWidget& Parent, const std::string& WidgetName) :
			mTexture(nullptr),
			mVertices(sf::Quads, 4),
			mState(TState::NORMAL),
			mIsHovered(false),
			mInputEnable(true),
			mIsToggleable(false),
			mIsSelected(false),
			mIsEnabled(true),
			mIsVisible(true),
			mIsAlive(true),
			mGuiManager(&GuiManager),
			mParent(&Parent),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>()),
			mName(WidgetName)
		{
		}

		TWidget::TWidget(const TWidget& Copy) :
			mVertices(Copy.mVertices),
			mState(Copy.mState),
			mIsHovered(Copy.mIsHovered),
			mInputEnable(Copy.mInputEnable),
			mIsToggleable(Copy.mIsToggleable),
			mIsSelected(Copy.mIsSelected),
			mIsEnabled(Copy.mIsEnabled),
			mIsVisible(Copy.mIsVisible),
			mIsAlive(Copy.mIsAlive),
			mTexture(Copy.mTexture),
			mGuiManager(Copy.mGuiManager),
			mParent(Copy.mParent),
			mID(idgenerator::GenerateByType::getUniqueID<ID, TWidget>())
		{
			mName = Copy.mName + "_copy";
		}

		TWidget::TWidget(TWidget&& Move) :
			mVertices(std::move(Move.mVertices)),
			mState(std::move(Move.mState)),
			mIsHovered(std::move(Move.mIsHovered)),
			mInputEnable(std::move(Move.mInputEnable)),
			mIsToggleable(std::move(Move.mIsToggleable)),
			mIsSelected(std::move(Move.mIsSelected)),
			mIsEnabled(std::move(Move.mIsEnabled)),
			mIsVisible(std::move(Move.mIsVisible)),
			mIsAlive(std::move(Move.mIsAlive)),
			mTexture(std::move(Move.mTexture)),
			mGuiManager(std::move(Move.mGuiManager)),
			mParent(std::move(Move.mParent)),
			mID(std::move(Move.mID)),
			mName(std::move(Move.mName))
		{
		}

		const nne::tgui::TWidget::ID& TWidget::getID() const
		{
			return mID;
		}

		sf::Transform TWidget::getParentTransform() const
		{
			if (mParent)
				return getTransform() * mParent->getParentTransform();

			return getTransform();
		}

		void TWidget::enableInput(const bool& Enabled /*= true*/)
		{
			mInputEnable = Enabled;
		}

		const bool& TWidget::isEnabled() const
		{
			return mIsEnabled && mInputEnable;
		}

		void TWidget::setTexture(const sf::Texture* Texture, bool UpdateBounds /*= true*/)
		{
			mTexture = Texture;

			// Update the texture bound if we have a valid texture and we choose to do it
			if (Texture && UpdateBounds)
			{
				mTextureRect = { { 0, 0 }, static_cast<sf::Vector2i>(Texture->getSize()) };

				updateSpriteBounds(Texture->getSize());
				updateTextureBounds(mTextureRect);
			}
		}

		const sf::Texture* TWidget::getTexture() const
		{
			return mTexture;
		}

		void TWidget::setTextureRect(const sf::IntRect& Rectangle)
		{
			mTextureRect = Rectangle;

			updateTextureBounds(mTextureRect);
		}

		const sf::IntRect& TWidget::getTextureRect() const
		{
			return mTextureRect;
		}

		void TWidget::setColor(const sf::Color& Color)
		{
			mVertices[0].color = Color;
			mVertices[1].color = Color;
			mVertices[2].color = Color;
			mVertices[3].color = Color;
		}

		const sf::Color& TWidget::getColor() const
		{
			return mVertices[0].color;
		}

		void TWidget::setOpacity(const sf::Uint8& Opacity)
		{
			mOpacity = Opacity;

			mVertices[0].color.a = Opacity;
			mVertices[1].color.a = Opacity;
			mVertices[2].color.a = Opacity;
			mVertices[3].color.a = Opacity;
		}

		const sf::Uint8& TWidget::getOpacity() const
		{
			return mOpacity;
		}

		void TWidget::setZIndex(const std::size_t& ZIndex)
		{
			mZIndex = ZIndex;
		}

		const std::size_t& TWidget::getZIndex() const
		{
			return mZIndex;
		}

		void TWidget::setVisible(const bool& Visible)
		{
			mIsVisible = Visible;
		}

		bool TWidget::isVisible() const
		{
			if (mParent)
				return mIsVisible & mParent->isVisible();

			return mIsVisible;
		}

		void TWidget::kill()
		{
			mIsAlive = false;
		}

		const bool& TWidget::isAlive()
		{
			return mIsAlive;
		}

		void TWidget::setName(const std::string& WidgetName)
		{
			mName = WidgetName;
		}

		const std::string& TWidget::getName() const
		{
			return mName;
		}

		void TWidget::setParent(const TWidget* WidgetParent)
		{
			mParent = WidgetParent;
		}

		const TWidget* TWidget::getParent() const
		{
			return mParent;

		}

		void TWidget::setManager(const TGuiManager& WidgetManager)
		{
			mGuiManager = &WidgetManager;
		}

		const TGuiManager& TWidget::getManager() const
		{
			return *mGuiManager;
		}

		void TWidget::setSize(const sf::Vector2u& Size)
		{
			updateSpriteBounds(Size);
		}

		sf::Vector2u TWidget::getSize()
		{
			return { static_cast<unsigned int>(mVertices[2].position.x), static_cast<unsigned int>(mVertices[2].position.y) };
		}

		sf::Vector2f TWidget::getWidgetReferencePointPosition(const TReferencePoint& ReferencePoint)
		{
			sf::Vector2f& WidgetSize = static_cast<sf::Vector2f>(getSize());

			switch (ReferencePoint)
			{
			case TReferencePoint::LEFT_TOP:
				return{ 0.f, 0.f };
			case TReferencePoint::CENTER_TOP:
				return{ WidgetSize.x / 2, 0.f };
			case TReferencePoint::RIGHT_TOP:
				return{ WidgetSize.x, 0.f };

			case TReferencePoint::LEFT_CENTER:
				return{ 0.f, WidgetSize.y / 2 };
			case TReferencePoint::CENTER:
				return{ WidgetSize.x / 2, WidgetSize.y / 2 };
			case TReferencePoint::RIGHT_CENTER:
				return{ 0.f, WidgetSize.y / 2 };

			case TReferencePoint::LEFT_BOTTOM:
				return{ 0.f, WidgetSize.y };
			case TReferencePoint::CENTER_BOTTOM:
				return{ WidgetSize.x / 2, WidgetSize.y };
			case TReferencePoint::RIGHT_BOTTOM:
				return{ WidgetSize.x, WidgetSize.y };

			default:
				return{ WidgetSize.x / 2, WidgetSize.y / 2 };
			}
		}

		void TWidget::draw(sf::RenderTarget& Target, sf::RenderStates States) const
		{
			// Skip the rendering if we are not showing the widget
			if (!isVisible() || (mParent && !mParent->isVisible()))
				return;
			
			// Apply the widget transform
			States.transform *= getParentTransform();

			// Apply the texture
			States.texture = mTexture;

			// Render the base target
			Target.draw(mVertices, States);
		}

		void TWidget::update(const sf::Time& ElapsedTime)
		{
		}

		void TWidget::changeState(const TState& NewState)
		{
			mState = NewState;
		}

		void TWidget::resetState()
		{
			// If we have a toogleable widget
			if (mIsToggleable)
			{
				if (mIsSelected)
				{
					bool Flag = true;
				}

				mState = mIsSelected ? TState::SELECTED : TState::NORMAL;
			}

			else if (mState != TState::DISABLED)
				mState = TState::NORMAL;
		}

		void TWidget::updateTextureBounds(const sf::IntRect& TextureRect)
		{
			sf::FloatRect TextureBound = static_cast<sf::FloatRect>(TextureRect);

			mVertices[0].texCoords = { TextureBound.left,  TextureBound.top };
			mVertices[1].texCoords = { TextureBound.left,  TextureBound.top + TextureBound.height };
			mVertices[2].texCoords = { TextureBound.left + TextureBound.width, TextureBound.top + TextureBound.height };
			mVertices[3].texCoords = { TextureBound.left + TextureBound.width, TextureBound.top };
		}

		void TWidget::updateSpriteBounds(const sf::Vector2u& SpriteSize)
		{
			mVertices[0].position = { 0.f, 0.f };
			mVertices[1].position = { 0.f, static_cast<float>(SpriteSize.y) };
			mVertices[2].position = { static_cast<float>(SpriteSize.x), static_cast<float>(SpriteSize.y) };
			mVertices[3].position = { static_cast<float>(SpriteSize.x), 0.f };
		}

		sf::FloatRect TWidget::getLocalBound()
		{
			float width = static_cast<float>(getSize().x);
			float height = static_cast<float>(getSize().y);

			return sf::FloatRect(0.f, 0.f, width, height);
		}

		sf::FloatRect TWidget::getGlobalBound()
		{			
			return getParentTransform().transformRect(getLocalBound());
		}

		void TWidget::copyLayout(const TWidget& WidgetLayout)
		{
			mVertices = WidgetLayout.mVertices;
			mState = WidgetLayout.mState;
			mInputEnable = WidgetLayout.mInputEnable;
			mTexture = WidgetLayout.mTexture;
			mVertices = WidgetLayout.mVertices;
		}

		void TWidget::setSelected(const bool& Select)
		{
			mIsSelected = Select;

			mIsSelected ? changeState(TWidget::SELECTED) : resetState();
		}

		const bool& TWidget::isSelected() const
		{
			return mIsSelected && mIsToggleable;
		}

		void TWidget::setToggleable(const bool& Toggle)
		{
			mIsToggleable = Toggle;
		}

		const bool& TWidget::isToggleable() const
		{
			return mIsToggleable;
		}

		void TWidget::setHovered(const bool& Hovered)
		{
			mIsHovered = true;

			mIsHovered ? changeState(TWidget::HOVER) : resetState();
		}

		const bool& TWidget::isHovered() const
{
			return mIsHovered;
		}

		const nne::tgui::TWidget::TState& TWidget::getState() const
		{
			return mState;
		}

		const nne::tgui::events::TEventSlot& TWidget::attachEvent(const events::List& EventType, const events::TEvent& EventToAttach)
		{
			// Insert the event in his slot and get a pair of the inserted iterator and whatever it's valid or not
			auto NewIt = mEventsList.emplace(EventType, EventToAttach);

			// If we added the element in the array return the iterator to the currently added element otherwise return end()
			return NewIt.second ? NewIt.first : mEventsList.end();
		}

		void TWidget::detachEvent(const events::List& EventType)
		{
			mEventsList.erase(EventType);
		}

		void TWidget::fireEvent(const events::List& EventToFire, TWidget* Sender, const sf::Event& EventData)
		{
			auto It = mEventsList.find(EventToFire);

			if (It != mEventsList.end())
			{
				It->second(Sender, EventData);
			}
		}

		void TWidget::addToManager(const TWidget::Ptr& Widget, TGuiManager* Manager, const std::size_t& ZIndex /*= 0*/)
		{
			Manager->addWidget(Widget, ZIndex);
		}

		void TWidget::disableWidget()
		{
			mIsEnabled = false;

			changeState(TState::DISABLED);
		}

		void TWidget::enableWidget()
		{
			mIsEnabled = true;

			changeState(TState::NORMAL);
		}

	}
}