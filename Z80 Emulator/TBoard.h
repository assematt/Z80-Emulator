#pragma once

#include <vector>
#include <type_traits>

#include "TEntity.h"
#include "TXMLFile.h"
#include "TBusComponent.h"
#include "TChipComponent.h"
#include "TWireComponent.h"

namespace nne
{
	class TBoard
	{
	public:

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
		bool loadBoard(const std::string& Path, TBoard& Board, TManager& EntityManager, IScene* Scene);

		/// Get what we clicked
		std::pair<IComponent*, std::string> getLastSelectedItem(const sf::Vector2f& MousePos) const;

		//////////////////////////////////////////////////////////////////////////

		/// Place a component in the logic board by passing the entity that owns the component
		template <class T>
		void placeComponent(const TEntity::EntityPtr& Entity);

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
		void removeComponent(const TEntity::EntityPtr& Entity);

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
		bool hasComponent(const TEntity::EntityPtr& Entity);

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
		void setSelectedComponent(const TEntity::EntityPtr& Entity);

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
		template <class T, const std::vector<T*>&>
		typename std::enable_if<std::is_same<T, TChipComponent>::value>::type getComponentVector() const;

		/// Get the vector of all the currently placed specified component
		template <class T, const std::vector<T*>&>
		typename std::enable_if<std::is_same<T, TWireComponent>::value>::type getComponentVector() const;

		/// Get the vector of all the currently placed specified component
		template <class T, const std::vector<T*>&>
		typename std::enable_if<std::is_same<T, TBusComponent>::value>::type getComponentVector() const;

		//////////////////////////////////////////////////////////////////////////

		/// Helper function to deselect everything
		void deselectEverything();

		/// Check if the chip we are trying to place is colliding with another chip already on the logic board
		bool checkCollisions(TChipComponent* Chip);

		/// Set/Get function to set or get the tools we are using to place component in the logic board
		void setInsertionMethod(const TInsertionMethod& Method);
		const TInsertionMethod& getInsertionMethod() const;

	private:

		/// Functions to load the chips 
		void loadChips(const xml::TXMLNode::TChildren ChipVector, TBoard& Board, TManager& EntityManager, IScene* Scene);

		/// Functions to load the wires 
		void loadWires(const xml::TXMLNode::TChildren WireVector, TBoard& Board, TManager& EntityManager, IScene* Scene);

		/// Functions to load the pins 
		void loadPins(const xml::TXMLNode::TChildren PinVector, TBoard& Board, TManager& EntityManager, IScene* Scene);

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
		std::vector<TBusComponent*>		mPlacedBusses;
		std::vector<TWireComponent*>	mPlacedWires;
		std::vector<TChipComponent*>	mPlacedChips;
	};

	//////////////////////////////////////////////////////////////////////////

	#include "TBoard.inl"
	
}