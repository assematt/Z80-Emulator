#include "TNewGameScene.h"

namespace nne
{

	void TNewGameScene::init()
	{
		// Create a Z80 and RAM entity
		mLogicEntity.addEntity(TFactory::makeZ80(), "Z80");
		mLogicEntity.addEntity(TFactory::makeRam(), "Ram");
		mLogicEntity.initEntities();

		// Get the Z80 and the ram entity
		auto Z80 = mLogicEntity.getEntityByKey("Z80");
		auto Ram = mLogicEntity.getEntityByKey("Ram");

		Z80->getComponentAsPtr<tcomponents::TZ80Component>()->connectRam(Ram);
		if (!Z80->getComponentAsPtr<tcomponents::TZ80Component>()->loadProgram("resources/programs/SUB.A01"))
		{
			std::cout << "Error! Could not open the file" << std::endl;

			// Something went bad :(
			return;
		}

		// Create a temp value the z80 and the ram
		auto& Z80Chip = TFactory::makeChip(Z80.get());
		auto& RamChip = TFactory::makeChip(Ram.get());
		auto& ConductiveRack = TFactory::makeConductiveTrack();

		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setPosition(250.f, 100.f);
		Z80Chip->getComponentAsPtr<TDrawableComponent>()->setScale(.5f, .5f);
		RamChip->getComponentAsPtr<TDrawableComponent>()->setPosition(900.f, 100.f);
		RamChip->getComponentAsPtr<TDrawableComponent>()->setScale(.5f, .5f);

		mGraphicEntity.addEntity(Z80Chip, "Z80Chip", mParent);
		mGraphicEntity.addEntity(RamChip, "RamChip", mParent);
		mGraphicEntity.addEntity(ConductiveRack, "ConductiveRack", mParent);
		mGraphicEntity.initEntities();
	}

	nne::IScene::ID TNewGameScene::eventLoop()
	{
		while (mRenderSurface->pollEvent(mAppEvent))
		{
			if (mAppEvent.type == sf::Event::Closed)
				mRenderSurface->close();

			if (mAppEvent.type == sf::Event::KeyPressed && mAppEvent.key.alt == true && mAppEvent.key.code == sf::Keyboard::F4)
				mRenderSurface->close();
		}

		return IScene::Same;
	}

	void TNewGameScene::refresh(sf::Time ElapsedTime)
	{
		mLogicEntity.refresh(ElapsedTime);

		mGraphicEntity.refresh(ElapsedTime);
	}

	void TNewGameScene::update(sf::Time ElapsedTime)
	{
		mLogicEntity.update(ElapsedTime);

		mGraphicEntity.update(ElapsedTime);
	}

	void TNewGameScene::draw()
	{
		// Clear the back buffered window
		mRenderSurface->clear();

		// Render all the entity in the the entity manager
		mGraphicEntity.draw(*mRenderSurface);

		// Display the back buffered window
		mRenderSurface->display();
	}

}