#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include <string>
#include <memory>
#include <map>

namespace nne
{
	template <class Type>
	using __TResource = std::unique_ptr<Type>;
	using _TResourceBase = __TResource<void*>;

	using _TResourceID = std::string;

	template <class T>
	class _TResourceLoader
	{

	public:
		using _TLoadFunction = std::function<__TResource<T>()>;

	public:
		_TResourceLoader(_TLoadFunction ResourceLoader, std::string ResourceID)
			: mResourceLoader(std::move(ResourceLoader))
			, mResourceID(std::move(ResourceID))
		{
		}

		__TResource<T> LoadResource() const
		{
			return mResourceLoader();
		}

		std::string	getResourceID() const
		{
			return mResourceID;
		}

	private:
		std::string mResourceID;
		_TLoadFunction mResourceLoader;
	};

	/// Texture loader
	struct _SFTextureLoader
	{
		_SFTextureLoader(const std::string& Path) :
			mPath(Path)
		{
		}

		__TResource<sf::Texture> operator() ()
		{
			std::unique_ptr<sf::Texture> TempPtr = std::make_unique<sf::Texture>();
			TempPtr->loadFromFile(mPath);
			return TempPtr;
		}

	private:
		std::string mPath;
	};

	/// Resource type Ptr


	/// Resource type
	template <class Type>
	struct _TResource
	{
		typename typedef std::unique_ptr<Type> _TResourcePtr;

		_TResource(typename _TResourceLoader<Type>& LoadFunction) :
			mLoader(LoadFunction)
		{
		}

		void Load()
		{
			mResource = std::move(mLoader.LoadResource());
			mResourceID = std::move(mLoader.getResourceID());
		}

		Type* GetData()
		{
			return mResource.get();
		}

		template <typename... TArgs>
		static _TResourcePtr MakeResource(TArgs&&... mArgs)
		{
			return std::make_unique<Type>(std::forward<TArgs>(mArgs)...);
		}

	private:
		std::string				mResourceID;
		_TResourcePtr			mResource;
		_TResourceLoader<Type>	mLoader;
	};

	struct _IResourceVectorBase
	{
		std::map<std::string, _TResourceBase> mResources;
	};

	template <class _Type>
	class _TResourceVector : public _IResourceVectorBase
	{
	public:
		using ResourcePtr = std::unique_ptr<_Type>;

		virtual ~_TResourceVector() {}

		void AddResource(ResourcePtr& Resource, const std::string& Key)
		{
			void* TempPtr = static_cast<void*>(Resource.release());

			auto UniquePtr = std::make_unique<void*>(TempPtr);

			mResources.insert(std::pair<std::string, _TResourceBase>(Key, std::move(UniquePtr)));
		}

		ResourcePtr& getResource(const std::string& Key)
		{
			return static_cast<_Type>(mResources[Key]);
		}
	};

	struct _TCacheManager
	{
		using _TResourceTypeID = std::size_t;
		using Ptr = _IResourceVectorBase*;

		template <class Type>
		void AddResource(typename _TResourceVector<Type>::ResourcePtr& Resource, const std::string& Key)
		{
			_TResourceTypeID ID;// = TUtility::getTypeID<_TResourceTypeID, Type>();

			if (mResourcesVectors.find(ID) == mResourcesVectors.end())
			{
				mResourcesVectors.emplace(ID, _IResourceVectorBase());
			}

			(static_cast<_TResourceVector<Type>*>(&mResourcesVectors[ID]))->AddResource(Resource, Key);
		}

		// 		template <class Type>
		// 		ResourcePtr& getResource(const std::string& Key)
		// 		{
		// 			_TResourceTypeID ID = TUtility::getTypeID<_TResourceTypeID, Type>();
		// 
		// 			return ((static_cast<_TResourceVector<Type>*>(&mResourcesVectors[ID]))->getResource(Key));
		// 		}

		std::map<_TResourceTypeID, _IResourceVectorBase> mResourcesVectors;
	};
}



/*

/// TEST CODE

sf::Texture Texture1, Texture2;
Texture1.loadFromFile("resources/images/crt_monitor_effect.png");
Texture2.loadFromFile("resources/images/crt_monitor_frame.png");

nne::_TResourceLoader<sf::Texture> TextureLoader(nne::_SFTextureLoader("resources/images/crt_monitor_effect.png"), "sprite_1");
nne::_TResourceLoader<sf::Texture> TextureLoader2(nne::_SFTextureLoader("resources/images/crt_monitor_frame.png"), "sprite_2");

nne::_TResource<sf::Texture> TextureResource1(TextureLoader);
nne::_TResource<sf::Texture> TextureResource2(TextureLoader2);
nne::_TResource<sf::Texture> TextureResource3(nne::_TResourceLoader<sf::Texture>(nne::_SFTextureLoader("resources/images/font.png"), "sprite_3"));
TextureResource1.Load();
TextureResource2.Load();
TextureResource3.Load();

std::unique_ptr<sf::Sprite> Sprite1 = std::make_unique<sf::Sprite>();
std::unique_ptr<sf::Sprite> Sprite2 = std::make_unique<sf::Sprite>();
std::unique_ptr<sf::Sprite> Sprite3 = std::make_unique<sf::Sprite>();

Sprite1->setTexture(*TextureLoader.LoadResource().release());
Sprite2->setTexture(*TextureResource2.GetData());
Sprite3->setTexture(*TextureResource3.GetData());

sf::Font Font;
Font.loadFromFile("resources/fonts/font.ttf");

nne::_TResourceLoader<sf::Texture> LoadFunction(nne::_SFTextureLoader("resources/images/crt_monitor_effect.png"), "Load Function");

std::unique_ptr<sf::Text> Text1 = std::make_unique<sf::Text>("Text 1", Font, 50);
std::unique_ptr<sf::Text> Text2 = std::make_unique<sf::Text>("Text 2", Font, 50);
Text1->setPosition(250.f, 50.f);
Text1->setFillColor(sf::Color::Red);

Text1->setPosition(450.f, 500.f);
Text1->setFillColor(sf::Color::Yellow);

nne::_TCacheManager TextureVector;
TextureVector.AddResource<sf::Sprite>(Sprite1, "Sprite1");
TextureVector.AddResource<sf::Sprite>(Sprite2, "Sprite2");
TextureVector.AddResource<sf::Sprite>(Sprite3, "Sprite3");
TextureVector.AddResource<sf::Text>(Text1, "Text1");
TextureVector.AddResource<sf::Text>(Text2, "Text2");

sf::RenderWindow Window(sf::VideoMode(1024, 768), "Test");

// run the program as long as the window is open
while (Window.isOpen())
{
// check all the window's events that were triggered since the last iteration of the loop
sf::Event Events;
while (Window.pollEvent(Events))
{
// "close requested" event: we close the window
if (Events.type == sf::Event::Closed)
Window.close();
}

Window.clear();

// draw everything here...
// window.draw(...);
for (auto& ResourceVector : TextureVector.mResourcesVectors)
{
for (auto& Resource : ResourceVector.second.mResources)
{
sf::Drawable* TexturePtr = static_cast<sf::Drawable*>(*(Resource.second));

Window.draw(*TexturePtr);
}
}

// end the current frame
Window.display();
}

Window.close();

*/