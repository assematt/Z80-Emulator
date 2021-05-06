#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>

#include "TValues.h"
#include INCLUDE_ENTITY_CLASS
#include <ECS/_TManager.h>
#include <ECS/Interfaces/_TReference.h>
#include "IScene.h"
#include "TXMLFile.h"
#include "TBusComponent.h"
#include "TChipComponent.h"
#include "TWireComponent.h"

namespace nne
{
	class TBoard
	{
	public:

		///
		//template <class T>
		//using ChipStorage = std::unordered_map<ecs::_IComponent::ID, typename ecs::_TReference<T>&>;

		template <class T>
		using ChipStorage = std::unordered_set<typename ecs::_TReference<T>&>;

		/// Enum of all the possible things we can insert in the logic board
		enum class TInsertionMethod
		{
			CHIP,
			WIRE,
			BUS,
			REMOVE,
			NONE
		} TReturnType;

		/// function to save the current board
		bool saveBoard(const std::string& Path);

		/// Function to lead a file in the board
#if ENTITY_SYSTEM == NNE
		bool loadBoard(const std::string& Path, TBoard& Board, TManager& EntityManager, IScene* Scene);
#else
		bool loadBoard(const std::string& Path, TBoard& Board, ecs::_TManager& EntityManager, IScene* Scene);
#endif
		
		/// Get what we clicked
#if ENTITY_SYSTEM == NNE
		std::pair<IComponent*, std::string> getLastSelectedItem(const sf::Vector2f& MousePos) const;
#else
		std::pair<ecs::_IComponent::Ptr, std::string> getLastSelectedItem(const sf::Vector2f& MousePos) const;
#endif

		//////////////////////////////////////////////////////////////////////////

		/// Place a component in the logic board by passing the entity that owns the component
		template <class T>
		void placeComponent(const ENTITY_PTR& Entity);
		
		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value>::type placeComponent(T* ComponentToPlace);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value>::type placeComponent(T* ComponentToPlace);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value>::type placeComponent(T* ComponentToPlace);

		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Remove a component in the logic board by passing the entity that owns the component
		template <class T>
		void removeComponent(const ENTITY_PTR& Entity);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value>::type removeComponent(T* ComponentToRemove);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value>::type removeComponent(T* ComponentToRemove);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value>::type removeComponent(T* ComponentToRemove);

		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Check if a component is placed in the logic board by passing the entity that owns the component
		template <class T>
		void hasComponent(const ENTITY_PTR& Entity);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value, bool>::type hasComponent(T* ComponentToCheck) const;

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value, bool>::type hasComponent(T* ComponentToCheck) const;

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value, bool>::type hasComponent(T* ComponentToCheck) const;

		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Mark a component as selected in the logic board by passing the entity that owns the component
		template <class T>
		void setSelectedComponent(const ENTITY_PTR& Entity);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value>::type setSelectedComponent(T* ComponentToSelect);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value>::type setSelectedComponent(T* ComponentToSelect);

		/// Place a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value>::type setSelectedComponent(T* ComponentToSelect);

		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Get the selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value, T>::type* getSelectedComponent() const;

		/// Get the selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value, T>::type* getSelectedComponent() const;

		/// Get the selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value, T>::type* getSelectedComponent() const;

		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Get the former selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value, T>::type* getFormerSelectedComponent();

		/// Get the former selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value, T>::type* getFormerSelectedComponent();

		/// Get the former selected in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value, T>::type* getFormerSelectedComponent();

		//////////////////////////////////////////////////////////////////////////
		
		
		//////////////////////////////////////////////////////////////////////////

		/// Deselect a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value>::type deselectComponent(const bool& DisableFormerComponentToo = false);

		/// Deselect a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value>::type deselectComponent(const bool& DisableFormerComponentToo = false);

		/// Deselect a component in the logic board by passing directly the component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value>::type deselectComponent(const bool& DisableFormerComponentToo = false);
		
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////

		/// Get the vector of all the currently placed specified component
		template <class T>
		typename std::enable_if<std::is_same<T, TChipComponent>::value, const std::vector<T*>&>::type getComponentVector() const;

		/// Get the vector of all the currently placed specified component
		template <class T>
		typename std::enable_if<std::is_same<T, TWireComponent>::value, const std::vector<T*>&>::type getComponentVector() const;

		/// Get the vector of all the currently placed specified component
		template <class T>
		typename std::enable_if<std::is_same<T, TBusComponent>::value, const std::vector<T*>&>::type getComponentVector() const;

		//////////////////////////////////////////////////////////////////////////

		/// Helper function to deselect everything
		void deselectEverything();

		/// Check if the chip we are trying to place is colliding with another chip already on the logic board
		bool checkCollisions(TChipComponent* Chip);

		/// Set/Get function to set or get the tools we are using to place component in the logic board
		void setInsertionMethod(const TInsertionMethod& Method);
		const TInsertionMethod& getInsertionMethod() const;

	private:

#if ENTITY_SYSTEM == NNE
		/// Functions to load the chips
		void loadChips(const xml::TXMLNode::TChildren ChipVector, TBoard& Board, TManager& EntityManager, IScene* Scene);

		/// Functions to load the wires 
		void loadWires(const xml::TXMLNode::TChildren WireVector, TBoard& Board, TManager& EntityManager, IScene* Scene);

		/// Functions to load the pins 
		void loadPins(const xml::TXMLNode::TChildren PinVector, TBoard& Board, TManager& EntityManager, IScene* Scene);
#else
		/// Functions to load the chips
		void loadChips(const xml::TXMLNode::TChildren ChipVector, TBoard& Board, ecs::_TManager& EntityManager, IScene* Scene);

		/// Functions to load the wires 
		void loadWires(const xml::TXMLNode::TChildren WireVector, TBoard& Board, ecs::_TManager& EntityManager, IScene* Scene);

		/// Functions to load the pins 
		void loadPins(const xml::TXMLNode::TChildren PinVector, TBoard& Board, ecs::_TManager& EntityManager, IScene* Scene);
#endif

		/// Functions to save the chips 
		void saveChips(const xml::TXMLNode::Ptr IntegratedCircuitsNode);

		/// Functions to save the wires 
		void saveWires(const xml::TXMLNode::Ptr WiresNode);

		/// Functions to save the pins 
		void savePins(const xml::TXMLNode::Ptr PinsNode);

	private:
		std::string						mLastSelectedItem;

		TBusComponent*					mSelectedBus;
		TBusComponent*					mFormerSelectedBus;

		TChipComponent*					mSelectedChip;
		TChipComponent*					mFormerSelectedChip;

		TWireComponent*					mSelectedWire;
		TWireComponent*					mFormerSelectedWire;

		TInsertionMethod				mInsertionMethod;

		// Vectors that stores a pointer to all the chips/wires/busses that are currently placed in the logicboard
#if ENTITY_SYSTEM == NNE
		std::vector<TBusComponent*>		mPlacedBusses;
		std::vector<TWireComponent*>	mPlacedWires;
		std::vector<TChipComponent*>	mPlacedChips;
#else
// 		std::vector<ecs::_TReference<TBusComponent>*>	mPlacedBusses;
// 		std::vector<ecs::_TReference<TWireComponent>*>	mPlacedWires;
// 		std::vector<ecs::_TReference<TChipComponent>*>	mPlacedChips;
		ChipStorage<TBusComponent>	mPlacedBusses;
		ChipStorage<TWireComponent>	mPlacedWires;
		ChipStorage<TChipComponent>	mPlacedChips;
#endif
	};

	//////////////////////////////////////////////////////////////////////////

	#include "TBoard.inl"
	
}