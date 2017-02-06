#include "TBoard.h"

#include <Windows.h>

#include "TFactory.h"
#include "TManager.h"
#include "TEventComponent.h"
#include "TLogicBoardComponent.h"


namespace nne
{
	
	std::string extractName(const std::string& Name)
	{
		auto EndTag = Name.find_first_of('_');

		// See what the Node type
		return Name.substr(0, EndTag);
	}

	bool TBoard::saveBoard(const std::string& Path)
	{
		// Start constructing the XMLNode that will contain all the information

		// Start with the head node <board>
		xml::TXMLNode::Ptr HeadNode = new xml::TXMLNode("board");

		// Save all the chips, add the <integrated_circuits> node
		saveChips(HeadNode->addChildNode("integrated_circuits"));

		// Save all the wires, add the <wires> node
		saveWires(HeadNode->addChildNode("wires"));

		// Save all the pins, add the <pins> node
		savePins(HeadNode->addChildNode("pins"));

		xml::TXMLFile Document;

		auto Result = Document.writeFile(Path, HeadNode);

		delete HeadNode;

		return Result;
	}

	bool TBoard::loadBoard(const std::string& Path, TBoard& Board, TManager& EntityManager, IScene* Scene)
	{
		std::string WhatReading = "";

		sf::Uint32	ChipCounter = 0;
		sf::Uint32	WireCounter = 0;

		xml::TXMLFile Document;
		xml::TXMLNode::Ptr HeadNode = new xml::TXMLNode();
		auto Result = Document.readFile(Path, HeadNode);

		// Load all the chips
		loadChips(HeadNode->getChildrenNodes("chip"), Board, EntityManager, Scene);

		// Load all the wires
		loadWires(HeadNode->getChildrenNodes("wire"), Board, EntityManager, Scene);

		// Load all the pins
		loadPins(HeadNode->getChildrenNodes("pins")[0]->getChildrenNodes("pin"), Board, EntityManager, Scene);

		delete HeadNode;

		return Result;
	}

	std::pair<IComponent*, std::string> TBoard::getLastSelectedItem(const sf::Vector2f& MousePos) const
	{
		// If we last selected a chip
		if (mLastSelectedItem == "CHIP" && mSelectedChip)
			return{ mSelectedChip, mLastSelectedItem };
		// If we last selected a wire
		else if (mLastSelectedItem == "WIRE" && mSelectedWire)
			return{ mSelectedWire, mLastSelectedItem };
		// If we last selected a bus
		else if (mLastSelectedItem == "BUS" && mSelectedBus)
			return{ mSelectedBus, mLastSelectedItem };

		return { nullptr, "" };
	}

	void TBoard::deselectEverything()
	{
		deselectComponent<TChipComponent>(true);
		deselectComponent<TWireComponent>(true);
		deselectComponent<TBusComponent>(true);
	}

	bool TBoard::checkCollisions(TChipComponent* Chip)
	{
		// By default we assume that we didn't find any collision
		bool CollisionFound = false;

		// Get the number of placed chips
		auto ChipsNumber = mPlacedChips.size();
		
		// Look for all the placed chip until a collision it's found
		for (auto Index = 0u; Index < ChipsNumber && CollisionFound == false; ++Index)
		{
			// Only look of course if the chip we are checking it's different that the one in the array
			if (Chip != mPlacedChips[Index])
				CollisionFound = !Chip->checkCollision(*mPlacedChips[Index]);
		}

		// Return wahtever result we found
		return CollisionFound;
	}

	void TBoard::setInsertionMethod(const TInsertionMethod& Method)
	{
		mInsertionMethod = Method;
	}

	const TBoard::TInsertionMethod& TBoard::getInsertionMethod() const
	{
		return mInsertionMethod;
	}

	void TBoard::loadChips(const xml::TXMLNode::TChildren ChipVector, TBoard& Board, TManager& EntityManager, IScene* Scene)
	{
		// Wire counter
		auto ChipCounter = 0u;

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
			NewChip->getComponent<TLogicBoardComponent>().setBoard(Board);
			NewChip->getComponent<TChipComponent>().setPlacedStatus(true);
			NewChip->getComponent<TDrawableComponent>().setPosition(PositionX, PositionY);
			NewChip->getComponent<TChipComponent>().setChipName(ChipName);

			NewChip->getComponent<TEventComponent>().attachEvent(tcomponents::events::onMouseUp, [&](const TEntity* Sender, const sf::Event& EventData) {

				if (Board.getInsertionMethod() != TBoard::TInsertionMethod::NONE)
					return;

				auto& SelectedPin = Sender->getComponent<TPinComponent>().getSelectedPin();

				if (SelectedPin != TPin::NotFound)
				{
					// Message 
					std::string Message =
					"Pin ID:   " + std::to_string(SelectedPin.getPinID()) + "\n" +
					"Pin Mode: " + std::to_string(static_cast<int>(SelectedPin.mPinMode)) + "\n" +
					"Pin Name: " + SelectedPin.mPinName + "\n" +
					"Pin Numb: " + std::to_string(SelectedPin.mPinNumber) + "\n" +
					"Pin GNum: " + std::to_string(SelectedPin.mPinGroupNumber) + "\n" +
					"Pin GrID: " + std::to_string(SelectedPin.mPinGroupID) + "\n" +
					"--------------------" + "\n";

					for (auto& Pin : SelectedPin.getPinConnections())
						Message += "Connection ID" + std::to_string(Pin->getPinID()) + "\n";

					::MessageBoxA(NULL, Message.c_str(), "PinSelected", MB_OK);
				}

			});

			// And adds it to the logic board
			placeComponent<TChipComponent>(NewChip);
		}
	}

	void TBoard::loadWires(const xml::TXMLNode::TChildren WireVector, TBoard& Board, TManager& EntityManager, IScene* Scene)
	{
		// Wire counter
		auto WireCounter = 0u;

		// Add the wires to the entity manager
		for (auto& Wire : WireVector)
		{
			// Increment the chip counter
			++WireCounter;

			// Create a wire entity and add it to the manger
			EntityManager.addEntity(TFactory::makeWire(), "Wire_" + std::to_string(WireCounter), Scene);

			// Retrieve the newly added entity
			auto TempWire = EntityManager.getEntityByKey("Wire_" + std::to_string(WireCounter));

			// Init the newly added wire
			TempWire->init();
			TempWire->getComponent<TLogicBoardComponent>().setBoard(Board);
			TempWire->getComponent<TEventComponent>().attachEvent(tcomponents::events::onMouseUp, [&](const TEntity* Sender, const sf::Event& EventData) {

				if (Board.getInsertionMethod() == TBoard::TInsertionMethod::NONE)
				{
					// Get the wire ID
					auto WireID = Sender->getEntityID();

					// Get the wire connections
					auto WireConnections = Sender->getComponent<TWireComponent>().getConnectedPins();

					// Dialog title
					std::string DialogTitle = "Entity ID: " + std::to_string(WireID);

					// Dialog message
					std::string DialogMessage = "";
					for (auto& Pin : WireConnections)
						DialogMessage += "Connection PIN id: " + std::to_string(Pin->getPinID()) + "\n";

					::MessageBoxA(NULL, DialogMessage.c_str(), DialogTitle.c_str(), MB_OK);
				}

			});

			// Get the wire component
			auto& WireComponent = TempWire->getComponent<TWireComponent>();

			// Set the wire name
			WireComponent.setWireName(Wire->getChildNode("name")->getContent());

			// Load the vertices
			auto VerticesVector = Wire->getChildrenNodes("point", 0);
			for (auto& WireVertex : VerticesVector)
			{
				float PositionX = WireVertex->getChildNode("x")->getContent<float>();
				float PositionY = WireVertex->getChildNode("y")->getContent<float>();

				// Add the vertices in the vertices vector
				WireComponent.mVertices.push_back({ PositionX, PositionY });
			}

			// Load the pin connections
			auto ConnectionVector = Wire->getChildrenNodes("connection", 0);
			for (auto& WireConnection : ConnectionVector)
			{
				auto& ParentEntity = WireConnection->getChildNode("pin_parent_entity")->getContent();
				auto& PinName = WireConnection->getChildNode("pin_name")->getContent();
				auto& Pin = TPin::getPinByName(PinName, ParentEntity);

				// Add the PIN in the connection vector
				/// OLD
				/*WireComponent.mPins.push_back(&Pin);*/
				WireComponent.mConnectedPins.insert(&Pin);
			}

			// Render the wire
			WireComponent.renderWire();

			// And adds it to the logic board
			placeComponent<TWireComponent>(TempWire);
		}

		// Now that we loaded all the wire add the connection between wire
		for (auto& Wire : WireVector)
		{
			// Get the wire name
			auto WireName = Wire->getChildNode("name")->getContent();

			// Get the TWireComponent
			auto WireComponent = TWireComponent::getWireByName(WireName);

			// Skip this cycle if we can't find this wire
			if (!WireComponent)
				continue;

			// Load all the junction if we have any
			auto JunctionsVector = Wire->getChildrenNodes("junction", 0);
			for (auto& WireJunction : JunctionsVector)
			{
				auto PositionX = WireJunction->getChildNode("x")->getContent<float>();
				auto PositionY = WireJunction->getChildNode("y")->getContent<float>();
				auto JunctionName = WireJunction->getChildNode("junction_name")->getContent();

				// Add the vertices in the junction vector
				WireComponent->mJunctions.push_back({ { PositionX, PositionY }, TWireComponent::getWireByName(JunctionName) });

				// Re-render the wire
				WireComponent->renderWire();
			}

			// Load all the wire connection if we have any
			auto ConnectionsWires = Wire->getChildrenNodes("wire_name");
			for (auto ConnectedWire : ConnectionsWires)
			{
				// Get the pointer of the connected wire
				auto ConnectedWireName = ConnectedWire->getContent();
				auto ConnectedWireComponent = TWireComponent::getWireByName(ConnectedWireName);

				// Add the wire and the connection
				WireComponent->connectWire(ConnectedWireComponent);
			}
		}
	}

	void TBoard::loadPins(const xml::TXMLNode::TChildren PinVector, TBoard& Board, TManager& EntityManager, IScene* Scene)
	{
		// Add the wires to the entity manager
		for (auto PinNode : PinVector)
		{
			// Get the info for the left PIN
			auto& LeftParentEntity = PinNode->getChildNode("pin_parent_entity")->getContent();
			auto& LeftPinName = PinNode->getChildNode("pin_name")->getContent();
			auto& LeftPin = TPin::getPinByName(LeftPinName, LeftParentEntity);

			// Get the list of all the connections
			auto ConnectionsNodes = PinNode->getChildrenNodes("connection", 0);
			for (auto ConnectionNode : ConnectionsNodes)
			{
				auto& RightParentEntity = ConnectionNode->getChildNode("pin_parent_entity")->getContent();
				auto& RightPinName = ConnectionNode->getChildNode("pin_name")->getContent();
				auto& RightPin = TPin::getPinByName(RightPinName, RightParentEntity);

				// Add the connection
				LeftPin.addConnections(RightPin);

				// Update the status of the connected PINs based on their type
				TPinComponentUtility::updatePinStatus(LeftPin, RightPin);
			}

		}
	}

	void TBoard::saveChips(const xml::TXMLNode::Ptr IntegratedCircuitsNode)
	{
		// Add all the chip 
		for (auto& Chip : mPlacedChips)
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
	}

	void TBoard::saveWires(const xml::TXMLNode::Ptr WiresNode)
	{
		// Add all the wires
		for (auto& Wire : mPlacedWires)
		{
			// Create the wire node
			auto WireNode = WiresNode->addChildNode("wire");

			// Save the wire name
			WireNode->addChildNode("name", Wire->getWireName());

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
					auto JunctionNode = JunctionsNode->addChildNode("junction");

					// Add the x and y position
					JunctionNode->addChildNode("x", std::to_string(WireJunction.first.x));
					JunctionNode->addChildNode("y", std::to_string(WireJunction.first.y));

					// Add the junction name
					JunctionNode->addChildNode("junction_name", WireJunction.second->mWireName);
				}
			}

			// Wire pin connections
			auto& PinConnections = Wire->getConnectedPins();
			if (!PinConnections.empty())
			{
				auto ConnectionsNode = WireNode->addChildNode("pin_connections");

				for (auto& Pin : PinConnections)
				{
					// Add a point node
					auto ConnectionNode = ConnectionsNode->addChildNode("connection");

					// Add the x and y position
					ConnectionNode->addChildNode("pin_parent_entity", Pin->getPinParent());
					ConnectionNode->addChildNode("pin_name", Pin->mPinName);
				}
			}

			// Wire wire connections
			auto& WireConnections = Wire->getConnectedWires();
			if (!WireConnections.empty())
			{
				auto ConnectionsNode = WireNode->addChildNode("wire_connections");

				for (auto& Wire : WireConnections)
					ConnectionsNode->addChildNode("wire_name", Wire->mWireName);
			}
		}
	}

	void TBoard::savePins(const xml::TXMLNode::Ptr PinsNode)
	{
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
	}

}