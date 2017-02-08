
//////////////////////////////////////////////////////////////////////////

/// Mark a component as selected in the logic board by passing the entity that owns the component
template <class T>
void nne::TBoard::setSelectedComponent(const TEntity::EntityPtr& Entity)
{
	setSelectedComponent(Entity->getComponentAsPtr<T>());
}

/// Check if a component is placed in the logic board by passing the entity that owns the component
template <class T>
bool nne::TBoard::hasComponent(const TEntity::EntityPtr& Entity)
{
	return hasComponent(Entity->getComponentAsPtr<T>());
}

/// Remove a component in the logic board by passing the entity that owns the component
template <class T>
void nne::TBoard::removeComponent(const TEntity::EntityPtr& Entity)
{
	removeComponent(Entity->getComponentAsPtr<T>());
}

/// Place a component in the logic board by passing the entity that owns the component
template <class T>
void nne::TBoard::placeComponent(const TEntity::EntityPtr& Entity)
{
	placeComponent(Entity->getComponentAsPtr<T>());
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value>::type TBoard::placeComponent(T* ComponentToPlace)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToPlace)
		return;

	mPlacedChips.push_back(ComponentToPlace);
	mInsertionMethod = TBoard::TInsertionMethod::CHIP;
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value>::type TBoard::placeComponent(T* ComponentToPlace)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToPlace)
		return;

	mPlacedWires.push_back(ComponentToPlace);
	mInsertionMethod = TBoard::TInsertionMethod::WIRE;
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value>::type TBoard::placeComponent(T* ComponentToPlace)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToPlace)
		return;

	mPlacedBusses.push_back(ComponentToPlace);
	mInsertionMethod = TBoard::TInsertionMethod::BUS;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value>::type TBoard::removeComponent(T* ComponentToRemove)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToRemove)
		return;

	auto It = std::find(mPlacedChips.begin(), mPlacedChips.end(), ComponentToRemove);

	if (It != mPlacedChips.end())
		mPlacedChips.erase(It);

	if (ComponentToRemove == mSelectedChip)
	{
		mSelectedChip = nullptr;
		mLastSelectedItem = "";
	}
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value>::type TBoard::removeComponent(T* ComponentToRemove)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToRemove)
		return;

	auto It = std::find(mPlacedWires.begin(), mPlacedWires.end(), ComponentToRemove);

	if (It != mPlacedWires.end())
		mPlacedWires.erase(It);

	if (ComponentToRemove == mSelectedWire)
	{
		mSelectedWire = nullptr;
		mLastSelectedItem = "";
	}
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value>::type TBoard::removeComponent(T* ComponentToRemove)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToRemove)
		return;

	auto It = std::find(mPlacedBusses.begin(), mPlacedBusses.end(), ComponentToRemove);

	if (It != mPlacedBusses.end())
		mPlacedBusses.erase(It);

	if (ComponentToRemove == mSelectedBus)
	{
		mSelectedBus = nullptr;
		mLastSelectedItem = "";
	}
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value, bool>::type TBoard::hasComponent(T* ComponentToCheck) const
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToCheck)
		return false;

	auto It = std::find(mPlacedChips.begin(), mPlacedChips.end(), ComponentToCheck);

	return It != mPlacedChips.end() ? true : false;
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value, bool>::type TBoard::hasComponent(T* ComponentToCheck) const
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToCheck)
		return false;

	auto It = std::find(mPlacedWires.begin(), mPlacedWires.end(), ComponentToCheck);

	return It != mPlacedChips.end() ? true : false;
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value, bool>::type TBoard::hasComponent(T* ComponentToCheck) const
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToCheck)
		return false;

	auto It = std::find(mPlacedBusses.begin(), mPlacedBusses.end(), ComponentToCheck);

	return It != mPlacedChips.end() ? true : false;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value>::type TBoard::setSelectedComponent(T* ComponentToSelect)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToSelect)
		return;

	// If we are selecting a new chip, still keep in cache the old chip by moving it to the mFormerSelectedChip variable
	if (mSelectedChip && mSelectedChip != ComponentToSelect)
		mFormerSelectedChip = mSelectedChip;

	// Cache the selected chip
	mSelectedChip = ComponentToSelect;

	// Save what kind of component we selected
	mLastSelectedItem = "CHIP";

	// Make sure to mark the old selected chip as not selected anymore
	if (mFormerSelectedChip && mInsertionMethod == TInsertionMethod::NONE)
		mFormerSelectedChip->deselectPin();
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value>::type TBoard::setSelectedComponent(T* ComponentToSelect)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToSelect)
		return;

	// If we are selecting a new chip, still keep in cache the old chip by moving it to the mFormerSelectedChip variable
	if (mSelectedWire && mSelectedWire != ComponentToSelect)
		mFormerSelectedWire = mSelectedWire;

	// Cache the selected wire
	mSelectedWire = ComponentToSelect;

	// Save what kind of component we selected
	mLastSelectedItem = "WIRE";

	// Make sure to mark the old selected wire as not selected anymore
	if (mFormerSelectedWire && mInsertionMethod == TInsertionMethod::NONE)
		mFormerSelectedWire->setSelectedStatus(false);
}

/// Place a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value>::type TBoard::setSelectedComponent(T* ComponentToSelect)
{
	// Skip the rest of the function if the pointer passed it's nullptr
	if (!ComponentToSelect)
		return;

	// If we are selecting a new chip, still keep in cache the old chip by moving it to the mFormerSelectedChip variable
	if (mSelectedBus && mSelectedBus != ComponentToSelect)
		mFormerSelectedBus = mSelectedBus;

	// Cache the selected bus
	mSelectedBus = ComponentToSelect;

	// Save what kind of component we selected
	mLastSelectedItem = "BUS";

	// Make sure to mark the old selected bus as not selected anymore
	if (mFormerSelectedBus && mInsertionMethod == TInsertionMethod::NONE)
		mFormerSelectedBus->setSelectedStatus(false);
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Get the selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value, T>::type* TBoard::getSelectedComponent() const
{
	return mSelectedChip;
}

/// Get the selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value, T>::type* TBoard::getSelectedComponent() const
{
	return mSelectedWire;
}

/// Get the selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value, T>::type* TBoard::getSelectedComponent() const
{
	return mSelectedBus;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Get the former selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value, T>::type* TBoard::getFormerSelectedComponent()
{
	return mFormerSelectedChip;
}

/// Get the former selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value, T>::type* TBoard::getFormerSelectedComponent()
{
	return mFormerSelectedWire;
}

/// Get the former selected in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value, T>::type* TBoard::getFormerSelectedComponent()
{
	return mFormerSelectedBus;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Deselect a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value>::type TBoard::deselectComponent(const bool& DisableFormerComponentToo /*= false*/)
{
	if (mSelectedChip)
	{
		mSelectedChip->deselectPin();

		mSelectedChip = nullptr;
	}

	if (DisableFormerComponentToo && mFormerSelectedChip)
	{
		mFormerSelectedChip->deselectPin();
		mFormerSelectedChip = nullptr;
	}
}

/// Deselect a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value>::type TBoard::deselectComponent(const bool& DisableFormerComponentToo /*= false*/)
{
	if (mSelectedWire)
	{
		mSelectedWire->setSelectedStatus(false);
		mSelectedWire = nullptr;
	}

	if (DisableFormerComponentToo && mFormerSelectedWire)
	{
		mFormerSelectedWire->setSelectedStatus(false);
		mFormerSelectedWire = nullptr;
	}
}

/// Deselect a component in the logic board by passing directly the component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value>::type TBoard::deselectComponent(const bool& DisableFormerComponentToo /*= false*/)
{
	if (mSelectedBus)
	{
		mSelectedBus->setSelectedStatus(false);
		mSelectedBus = nullptr;
	}

	if (DisableFormerComponentToo && mFormerSelectedBus)
	{
		mFormerSelectedBus->setSelectedStatus(false);
		mFormerSelectedBus = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/// Get the vector of all the currently placed specified component
template <class T>
typename std::enable_if<std::is_same<T, TChipComponent>::value, const std::vector<T*>&>::type TBoard::getComponentVector() const
{
	return mPlacedChips;
}

/// Get the vector of all the currently placed specified component
template <class T>
typename std::enable_if<std::is_same<T, TWireComponent>::value, const std::vector<T*>&>::type TBoard::getComponentVector() const
{
	return mPlacedWires;
}

/// Get the vector of all the currently placed specified component
template <class T>
typename std::enable_if<std::is_same<T, TBusComponent>::value, const std::vector<T*>&>::type TBoard::getComponentVector() const
{
	return mPlacedBusses;
}

//////////////////////////////////////////////////////////////////////////