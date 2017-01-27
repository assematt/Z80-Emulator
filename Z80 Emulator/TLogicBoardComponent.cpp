#include "TLogicBoardComponent.h"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "TFactory.h"
#include "TManager.h"
#include "TSceneManager.h"
#include "TCacheManager.h"
#include "TDrawableComponent.h"
#include "TPinComponent.h"

#include "TXMLFile.h"

namespace nne
{

	TLogicBoardComponent::TLogicBoardComponent() :
		mSelectedChip(nullptr),
		mFormerSelectedChip(nullptr),

		mFormerSelectedWire(nullptr),
		mSelectedWire(nullptr),

		mFormerSelectedBus(nullptr),
		mSelectedBus(nullptr),

		mInsertionMethod(TInsertionMethod::NONE),
		mLastAddedChip("")
	{
	}

	void TLogicBoardComponent::update(const sf::Time& ElapsedTime)
	{
	}

	bool TLogicBoardComponent::saveBoard(const std::string& Path)
	{
		// 
		std::ofstream OutputFile;

		// Tries to create a file
		OutputFile.open(Path.c_str());

		// Check if there was a mistake in opening the file
		if (!OutputFile.is_open())
			return false;

		// Start outputting the file
		// Example file
		/*
		<board>
			<integrated_circuits>
				<chip>
					<pins>
						<number>28</number>
						<pin>
							<mode>INPUT</mode>
							<name>A0</name>
							<status>LOW</status>
							<pin_number>10</pin_number>
							<group>0</group>
							<group_number>0</group_number>
						</pin>
					</pins>
					<format>DIP</format>
				</chip>
			</integrated_circuits>
			<wires>
				<wire>
					<points>
						<point>
							<X>0.f</X>
							<Y>0.f</Y>
						</point>
						<point>
							<X>50.f</X>
							<Y>50.f</Y>
						</point>
					</point>
					<junctions>
						<junction>
							<X>100.f</X>
							<Y>0.f</Y>
						</junction>
					</junctions>
				</wire>
			</wires>
		</board>
		*/

		// Start constructing the XMLNode that will contain all the information

		// Start with the head node <board>
		xml::TXMLNode::Ptr HeadNode = new xml::TXMLNode("board");

#pragma region CHIP
		// Add the <integrated_circuits> node
		auto IntegratedCircuitsNode = HeadNode->addChildNode("integrated_circuits");

		// Add all the chip 
		for (auto& Chip : mChipVector)
		{
			// Create the chip node
			auto ChipNode = IntegratedCircuitsNode->addChildNode("chip");

			// Add the chip format
			ChipNode->addChildNode("format", "DIP");

			// Add the chip name
			ChipNode->addChildNode("name", Chip->getName());

			// Add the chip format
			auto PositionNode = ChipNode->addChildNode("position");
			auto Position = Chip->getParent()->getComponent<TDrawableComponent>().getPosition();

			// Set the X and Y position
			PositionNode->addChildNode("x", std::to_string(Position.x));
			PositionNode->addChildNode("y", std::to_string(Position.y));
		}
#pragma endregion

#pragma region WIRES
		// Add the <wires> node
		auto WiresNode = HeadNode->addChildNode("wires");

		// Add all the wires
		for (auto& Wire : mWireVector)
		{
			// Create the wire node
			auto WireNode = WiresNode->addChildNode("wire");

			// Create the wire points node
			auto PointsNode = WireNode->addChildNode("points");

			// Add all the wire points
			for (auto& WireVertex : Wire->getVerticesVector())
			{
				// Add a point node
				auto PointNode = PointsNode->addChildNode("point");

				// Add the x and y position
				PointNode->addChildNode("x", std::to_string(WireVertex.x));
				PointNode->addChildNode("y", std::to_string(WireVertex.y));
			}

			// Wire junctions
			auto& Junctions = Wire->getJunctionsVector();
			if (!Junctions.empty())
			{
				auto JunctionsNode = WireNode->addChildNode("junctions");

				for (auto& WireJunction : Junctions)
				{
					// Add a point node
					auto JunctionNode = PointsNode->addChildNode("junction");

					// Add the x and y position
					JunctionNode->addChildNode("x", std::to_string(WireJunction.x));
					JunctionNode->addChildNode("y", std::to_string(WireJunction.y));
				}
			}
		}
#pragma endregion

#pragma region PINS
		// Add the <pins> node
		auto PinsNode = HeadNode->addChildNode("pins");

		// Add all the pins
		for (auto Pin : TPin::getGlobalPinVector())
		{
			// Output the pin only if we have some connections, so if it doesn't have any skip this loop cycle
			if (!Pin->hasConnections())
				continue;

			// Add the pin node
			auto PinNode = PinsNode->addChildNode("pin");

			// Add the pin parent entity
			PinNode->addChildNode("pin_parent_entity", Pin->getPinParent());

			// Add the pin name
			PinNode->addChildNode("pin_name", Pin->mPinName);

			// Add all the pin connections
			for (auto PinConnection : Pin->getPinConnections())
			{
				// Add a connection node
				auto ConnectionNode = PinNode->addChildNode("connection");

				// Add the x and y position
				ConnectionNode->addChildNode("pin_parent_entity", PinConnection->getPinParent());
				ConnectionNode->addChildNode("pin_name", PinConnection->mPinName);
			}
		}
#pragma endregion

		xml::TXMLFile Document;

		Document.writeFile(Path, HeadNode);

		delete HeadNode;

		return true;
	}

	std::string removeTag(const std::string& Node)
	{
		auto StartTag = Node.find_first_of('<') + 1;
		auto EndTag = Node.find_first_of('>');

		// See what the Node type
		return Node.substr(StartTag, EndTag - StartTag);
	}

	std::string getNodeContent(const std::string& Node)
	{
		auto StartTag = Node.find_first_of('>') + 1;
		auto EndTag = Node.find_last_of('<');

		// See what the Node type
		return Node.substr(StartTag, EndTag - StartTag);
	}

	std::string extractName(const std::string& Name)
	{
		auto EndTag = Name.find_first_of('_');

		// See what the Node type
		return Name.substr(0, EndTag);
	}

	bool TLogicBoardComponent::loadBoard(const std::string& Path, TManager& EntityManager, IScene* Scene)
	{
		// 
		std::ifstream InputFile;

		std::string WhatReading = "";

		sf::Uint32	ChipCounter = 0;
		sf::Uint32	WireCounter = 0;

		// Tries to create a file
		InputFile.open(Path.c_str());

		// Check if there was a mistake in opening the file
		if (!InputFile.is_open())
			return false;

		xml::TXMLFile Document;
		xml::TXMLNode::Ptr HeadNode = new xml::TXMLNode();
		Document.readFile(Path, HeadNode);
		
#pragma region CHIPS
		// Get all chip in the file
		auto ChipVector = HeadNode->getChildrenNodes("chip", 0);

		// Add the chips to the entity manager
		for (auto& Chip : ChipVector)
		{
			// Increment the chip counter
			++ChipCounter;

			std::function<TEntity::EntityPtr()> FactoryFunction;
			std::string	NewChipID;

			// Extract the name of the chip
			std::string ChipName = Chip->getChildNode("name")->getContent();
			std::string ChipToCreate = extractName(ChipName);

			// Extract the position node of the chip
			float PositionX = Chip->getChildNode("position")->getChildNode("x")->getContent<float>();
			float PositionY = Chip->getChildNode("position")->getChildNode("y")->getContent<float>();

			// If we are creating a z80 chip and we didn't do it before
			if (ChipToCreate == "Z80")
			{
				FactoryFunction = TFactory::makeZ80;
				NewChipID = "Z80";
			}
			// If we are creating a RAM chip
			else if (ChipToCreate == "RAM")
			{
				FactoryFunction = TFactory::makeRam;
				NewChipID = "RAM";
			}
			// If we are creating a NAND chip
			else if (ChipToCreate == "NAND")
			{
				FactoryFunction = TFactory::makeNandChip;
				NewChipID = "NAND_" + std::to_string(ChipCounter);
			}
			// If we are creating a LED
			else if (ChipToCreate == "LED")
			{
				FactoryFunction = TFactory::makeLed;
				NewChipID = "LED_" + std::to_string(ChipCounter);
			}
			// If we are creating a VCC
			else if (ChipToCreate == "VCC")
			{
				FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::POWER);
				NewChipID = "VCC_" + std::to_string(ChipCounter);
			}
			// If we are creating a GND
			else if (ChipToCreate == "GND")
			{
				FactoryFunction = std::bind(TFactory::makePowerConnector, TPowerComponent::Type::GROUND);
				NewChipID = "GND_" + std::to_string(ChipCounter);
			}

			// Create a new graphic chip
			EntityManager.addEntity(FactoryFunction(), NewChipID, Scene);

			// Get the newly added CHIP
			auto NewChip = EntityManager.getEntityByKey(NewChipID);
			NewChip->init();
			NewChip->getComponent<TChipComponent>().setPlacedStatus(true);
			NewChip->getComponent<TDrawableComponent>().setPosition(PositionX, PositionY);
			NewChip->getComponent<TChipComponent>().setChipName(ChipName);

			// And adds it to the logic board
			placeChip(NewChip.get());
		}
#pragma endregion

#pragma region WIRES
		// Get all wire in the file
		auto WireVector = HeadNode->getChildrenNodes("wire", 0);

		// Add the wires to the entity manager
		for (auto& Wire : WireVector)
		{
			// Increment the chip counter
			++WireCounter;

			std::vector<sf::Vector2f> Vertices;
			std::vector<sf::Vector2f> Junctions;

			// Get all the wire point
			auto VerticesVector = Wire->getChildrenNodes("point", 0);
			auto JunctionsVector = Wire->getChildrenNodes("junction", 0);

			// Create a wire entity and add it to the manger
			EntityManager.addEntity(TFactory::makeWire(), "Wire_" + std::to_string(WireCounter), Scene);

			// Retrieve the newly added entity
			auto TempWire = EntityManager.getEntityByKey("Wire_" + std::to_string(WireCounter));

			// Init the newly added wire
			TempWire->init();
			TempWire->getComponent<TWireComponent>().toggleDraw();

			for (auto& WireVertex : VerticesVector)
			{
				float PositionX = WireVertex->getChildNode("x")->getContent<float>();
				float PositionY = WireVertex->getChildNode("y")->getContent<float>();

				TempWire->getComponent<TWireComponent>().placePointTemp({ PositionX, PositionY });
				TempWire->getComponent<TWireComponent>().confirmPoints();
			}
			for (auto& WireJunction : JunctionsVector)
			{
				float PositionX = WireJunction->getChildNode("x")->getContent<float>();
				float PositionY = WireJunction->getChildNode("y")->getContent<float>();

				TempWire->getComponent<TWireComponent>().placeJunction({ PositionX, PositionY });
			}

			TempWire->getComponent<TWireComponent>().toggleDraw();

			// And adds it to the logic board
			placeWire(TempWire.get());
		}
#pragma endregion

#pragma region PINS

		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////
		////															////
		////		UGLY MARKER: CHANGE ASAP (25/01/2017 - 20:18)		////
		////															////
		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		// Get all wire in the file
		auto PinVector = HeadNode->getChildNode("pins")->getChildrenNodes("pin", 0);

		// Add the wires to the entity manager
		for (auto PinNode : PinVector)
		{
			// Get the info for the left PIN
			auto LeftParentEntity = PinNode->getChildNode("pin_parent_entity")->getContent();
			auto LeftPinName = PinNode->getChildNode("pin_name")->getContent();

			/// That's the ugly part
			// Look for the chip component in the manager correspondent to the one specified in the XML file
			bool EntityFound = false;
			TEntity::EntityPtr LeftPinEntity;
			for (auto EntityIt = EntityManager.begin(); EntityIt != EntityManager.end() && !EntityFound; ++EntityIt)
			{
				auto Entity = *EntityIt;

				// If the entity doesn't have a chip component we skip this loop cycle
				if (!Entity->hasComponent<TChipComponent>())
					continue;

				if (LeftParentEntity != Entity->getComponent<TChipComponent>().getName())
					continue;

				// 
				LeftPinEntity = Entity;

				EntityFound = true;
			}

			auto& LeftPin = LeftPinEntity->getComponent<TPinComponent>().getPin(LeftPinName);

			// Get the list of all the connections
			auto ConnectionsNodes = PinNode->getChildrenNodes("connection", 0);
			for (auto ConnectionNode : ConnectionsNodes)
			{
				// Get the info for the left PIN
				auto RightParentEntity = ConnectionNode->getChildNode("pin_parent_entity")->getContent();
				auto RightPinName = ConnectionNode->getChildNode("pin_name")->getContent();

				/// That's the ugly part (part 2 :D) :(
				// Look for the chip component in the manager correspondent to the one specified in the XML file
				bool EntityFound = false;
				TEntity::EntityPtr RightPinEntity;
				for (auto EntityIt = EntityManager.begin(); EntityIt != EntityManager.end() && !EntityFound; ++EntityIt)
				{
					auto Entity = *EntityIt;

					// If the entity doesn't have a chip component we skip this loop cycle
					if (!Entity->hasComponent<TChipComponent>())
						continue;

					if (RightParentEntity != Entity->getComponent<TChipComponent>().getName())
						continue;

					// 
					RightPinEntity = Entity;

					EntityFound = true;
				}

				auto& RightPin = RightPinEntity->getComponent<TPinComponent>().getPin(RightPinName);

				// Add the connection
				LeftPin.addConnections(RightPin);

				// Update the status of the connected PINs based on their type
				TPinComponentUtility::updatePinStatus(LeftPin, RightPin);
			}
		}
#pragma endregion
		
		delete HeadNode;

		return true;
	}

	void TLogicBoardComponent::refresh(const sf::Time& ElapsedTime)
	{
	}

	void TLogicBoardComponent::init()
	{
	}

	/// Chip function
	void TLogicBoardComponent::placeChip(TChipComponent* ChipToPlace)
	{
		mChipVector.push_back(ChipToPlace);
	}

	void TLogicBoardComponent::placeChip(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeChip(Entity->getComponentAsPtr<TChipComponent>());
	}

	void TLogicBoardComponent::removeChip(TChipComponent* ChipToRemove)
	{
		// Number of chip in the chip vector
		auto Chips = mChipVector.size();
		
		// Iterate the vector
		for (auto Index = 0u; Index < Chips; ++Index)
		{
			// If we found the CHip to remove, remove it from the vector and return early
			if (mChipVector[Index] == ChipToRemove)
			{
				fastDelete(mChipVector, Index);

				// If the chip we are removing it's the one selected it, deselect it
				if (ChipToRemove == mSelectedChip)
					deselectChip();

				return;
			}
		}

		// TODO
		// Remove the logic board component from the parent entity to avoid unwanted deletion
	}

	void TLogicBoardComponent::removeChip(TEntity* Entity)
	{
		removeChip(Entity->getComponentAsPtr<TChipComponent>());

		// Remove the logic board component from the parent entity to avoid unwanted deletion
		Entity->softRemoveComponent<TLogicBoardComponent>();
	}

	/// Wire function
	void TLogicBoardComponent::placeWire(TWireComponent* Wire)
	{
		mWireVector.push_back(Wire);
	}

	void TLogicBoardComponent::placeWire(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeWire(Entity->getComponentAsPtr<TWireComponent>());
	}
		
	void TLogicBoardComponent::removeWire(TWireComponent* WireToRemove)
	{
		// Number of chip in the wire vector
		auto Wires = mWireVector.size();

		// Iterate the vector
		for (auto Index = 0u; Index < Wires; ++Index)
		{
			// If we found the wire to remove, remove it from the vector and return early
			if (mWireVector[Index] == WireToRemove)
			{
				fastDelete(mWireVector, Index);

				// If the wire we are removing it's the one selected it, deselect it
				if (WireToRemove == mSelectedWire)
					deselectWire();

				return;
			}
		}

		// TODO
		// Remove the logic board component from the parent entity to avoid unwanted deletion
	}

	void TLogicBoardComponent::removeWire(TEntity* Entity)
	{
		removeWire(Entity->getComponentAsPtr<TWireComponent>());

		// Remove the logic board component from the parent entity to avoid unwanted deletion
		Entity->softRemoveComponent<TLogicBoardComponent>();
	}

	/// Bus function
	void TLogicBoardComponent::placeBus(TBusComponent* Bus)
	{
		mBusVector.push_back(Bus);
	}

	void TLogicBoardComponent::placeBus(TEntity* Entity)
	{
		// Add the logic-board component to the entity
		Entity->addComponent<TLogicBoardComponent>(this);

		placeBus(Entity->getComponentAsPtr<TBusComponent>());
	}
	
	void TLogicBoardComponent::removeBus(TBusComponent* BusToRemove)
	{
		// Number of chip in the wire vector
		auto Busses = mBusVector.size();

		// Iterate the vector
		for (auto Index = 0u; Index < Busses; ++Index)
		{
			// If we found the wire to remove, remove it from the vector and return early
			if (mBusVector[Index] == BusToRemove)
			{
				fastDelete(mBusVector, Index);

				// If the bus we are removing it's the one selected it, deselect it
				if (BusToRemove == mSelectedBus)
					deselectBus();

				return;
			}
		}

		// TODO
		// Remove the logic board component from the parent entity to avoid unwanted deletion
	}

	void TLogicBoardComponent::removeBus(TEntity* Entity)
	{
		removeBus(Entity->getComponentAsPtr<TBusComponent>());

		// Remove the logic board component from the parent entity to avoid unwanted deletion
		Entity->softRemoveComponent<TLogicBoardComponent>();
	}

	/// Set/Get insertion mode
	void TLogicBoardComponent::setInsertionMethod(const TInsertionMethod& Method)
	{
		mInsertionMethod = Method;
	}

	const TLogicBoardComponent::TInsertionMethod& TLogicBoardComponent::getInsertionMethod() const
	{
		return mInsertionMethod;
	}

	//////////////////////////////////////////////////////////////////////////
	bool TLogicBoardComponent::checkCollisions(TChipComponent* Chip)
	{
		bool CollisionFound = false;
		auto ChipsNumber = mChipVector.size();
		auto Index = 0u;

		while (Index < ChipsNumber && CollisionFound == false)
		{
			if (Chip != mChipVector[Index])
				CollisionFound = !Chip->checkCollision(*mChipVector[Index]);

			++Index;
		}

		return CollisionFound;
	}

	void TLogicBoardComponent::setSelectedChip(TChipComponent* Chip)
	{
		// Check if is the first time we are assigning the selected chip, if yes also check if have selected a different chip
		if (mSelectedChip && mSelectedChip != Chip)
			mFormerSelectedChip = mSelectedChip;

		// Set the selected chip
		mSelectedChip = Chip;

		// 
		if (mFormerSelectedChip && mInsertionMethod == TInsertionMethod::NONE)
			mFormerSelectedChip->deselectPin();
	}

	TChipComponent* TLogicBoardComponent::getSelectedChip() const
	{
		return mSelectedChip;
	}

	TChipComponent* TLogicBoardComponent::getFormerSelectedChip() const
	{
		return mFormerSelectedChip;
	}

	void TLogicBoardComponent::deselectChip(bool DisableFormerChipToo /*= false*/)
	{
		if (mSelectedChip)
		{
			mSelectedChip->deselectPin();

			mSelectedChip = nullptr;
		}		

		if (DisableFormerChipToo && mFormerSelectedChip)
		{
			mFormerSelectedChip->deselectPin();
			mFormerSelectedChip = nullptr;
		}
	}

	void TLogicBoardComponent::setSelectedWire(TWireComponent* Wire)
	{
		// Check if is the first time we are assigning the selected wire, if yes also check if have selected a different wire
		if (mSelectedWire && mSelectedWire != Wire)
			mFormerSelectedWire = mSelectedWire;

		// Set the selected wire
		mSelectedWire = Wire;

		// 
		if (mFormerSelectedWire && mInsertionMethod == TInsertionMethod::NONE)
			mFormerSelectedWire->setSelectedStatus(false);
	}

	TWireComponent* TLogicBoardComponent::getSelectedWire() const
	{
		return mSelectedWire;
	}

	TWireComponent* TLogicBoardComponent::getFormerSelectedWire() const
	{
		return mFormerSelectedWire;
	}

	void TLogicBoardComponent::deselectWire(bool DisableFormerWireToo /*= false*/)
	{
		if (mSelectedWire)
		{
			mSelectedWire->setSelectedStatus(false);
			mSelectedWire = nullptr;
		}
		
		if (DisableFormerWireToo && mFormerSelectedWire)
		{
			mFormerSelectedWire->setSelectedStatus(false);
			mFormerSelectedWire = nullptr;
		}
	}

	void TLogicBoardComponent::setSelectedBus(TBusComponent* Bus)
	{
		// Check if is the first time we are assigning the selected bus, if yes also check if have selected a different bus
		if (mSelectedWire && mSelectedBus != Bus)
			mFormerSelectedBus = mSelectedBus;

		// Set the selected bus
		mSelectedBus = Bus;
	}

	nne::TBusComponent* TLogicBoardComponent::getSelectedBus() const
{
		return mSelectedBus;
	}

	nne::TBusComponent* TLogicBoardComponent::getFormerSelectedBus() const
{
		return mFormerSelectedBus;
	}

	void TLogicBoardComponent::deselectBus(bool DisableFormerBusToo /*= false*/)
	{
		if (mSelectedBus)
		{
			mSelectedBus->setSelectedStatus(false);
			mSelectedBus = nullptr;
		}		

		if (DisableFormerBusToo && mFormerSelectedBus)
		{
			mFormerSelectedBus->setSelectedStatus(false);
			mFormerSelectedBus = nullptr;
		}
	}	

	void TLogicBoardComponent::deselectEverything()
	{
		deselectBus(true);
		deselectChip(true);
		deselectWire(true);
	}

	const std::vector<TChipComponent*>& TLogicBoardComponent::getChipVector() const
	{
		return mChipVector;
	}

	const std::vector<TBusComponent*>& TLogicBoardComponent::getBusVector() const
	{
		return mBusVector;
	}

	const std::vector<TWireComponent*>& TLogicBoardComponent::getWireVector() const
	{
		return mWireVector;
	}

}