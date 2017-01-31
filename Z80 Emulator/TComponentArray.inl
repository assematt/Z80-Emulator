/// Function to add a component to the entity
template <class T, typename... TArgs>
void TComponentArray::addComponent(TArgs&&... mArgs)
{
	// Make sure we are not adding a duplicate component
	assert(!hasComponent<T>());

	// Compute an unique ID
	//TComponentID UniqueID = TUtility::getTypeID<TComponentID, T>();
	TComponentID UniqueID = idgenerator::GenerateByType::getUniqueID<TComponentID, T>();

	// Creates a shared ptr that hold the component and set his parent entity and component id value
	auto NewComponentPtr = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
	NewComponentPtr->mParent = mComponentsParent;
	NewComponentPtr->mID = UniqueID;

	//TComponentHandle Test = TComponentHandle::CreatesHandle<T>();

	// Put the position of the newly created shared_ptr in the mComponentsArray for easy access
	mComponentsArray[UniqueID] = mComponents.size();

	// Flag the component as alive
	mComponentsState[UniqueID] = true;

	// Put the component in the component array
	mComponents.push_back(std::move(NewComponentPtr));
}

template <class T>
void TComponentArray::addComponent(T* Pointer)
{
	addComponent<T>(std::move(std::unique_ptr<T>(Pointer)));
}

template <class T>
void TComponentArray::addComponent(std::unique_ptr<T>&& Move)
{
	// Make sure we are not adding a duplicate component
	assert(!hasComponent<T>() && "A is not equal to B");

	// Put the position of the newly created unique_ptr in the mComponentsArray for easy access
	mComponentsArray[Move->mID] = mComponents.size();

	// Flag the component as alive
	mComponentsState[Move->mID] = true;

	mComponents.push_back(std::move(Move));
}

template <class T, typename... TArgs>
void TComponentArray::replaceComponent(TArgs&&... mArgs)
{
	replaceComponent<T>(std::move(std::make_unique<T>(std::forward<TArgs>(mArgs)...)));
}

template <class T>
void TComponentArray::replaceComponent(T* Pointer)
{
	replaceComponent<T>(std::move(std::unique_ptr<T>(Pointer)));
}

template <class T>
void TComponentArray::replaceComponent(std::unique_ptr<T>&& Move)
{
	// Delete the component and flag the component as dead
	mComponentsState[Move->mID] = true;

	mComponents[mComponentsArray[Move->mID]] = std::move(Move);
}

/// Function to remove a component by component type
template <class T>
void TComponentArray::removeComponent()
{
	removeComponent(idgenerator::GenerateByType::getUniqueID<TComponentID, T>());
}

/// Function to remove a component by component ID
void TComponentArray::removeComponent(TComponentID ID)
{
	// Delete the component and flag the component as dead
	mComponents[mComponentsArray[ID]].reset();
	mComponentsArray[ID] = 0;
	mComponentsState[ID] = false;
}

/// Function to get a component by component type as cast
template <class T>
T& TComponentArray::getComponent() const
{
	return *dynamic_cast<T*>(getComponent(idgenerator::GenerateByType::getUniqueID<TComponentID, T>()));
}

/// Function to get a component by component type as shared_ptr 
template <class T>
T* TComponentArray::getComponentAsPtr() const
{
	return dynamic_cast<T*>(getComponent(idgenerator::GenerateByType::getUniqueID<TComponentID, T>()));
}

/// Function to get a component to the entity by component ID
IComponent* TComponentArray::getComponent(TComponentID ID) const
{
	// Make sure the component we are trying to get exist
	assert(hasComponent(ID) && "ID is not present");

	// Get the component from the array
	return mComponents[mComponentsArray[ID]].get();
}

/// Function to check if a component exist by component type
template <class T>
const bool TComponentArray::hasComponent() const
{
	return mComponentsState[idgenerator::GenerateByType::getUniqueID<TComponentID, T>()];
}

/// Function to check if a component exist by component ID
const bool TComponentArray::hasComponent(TComponentID ID) const
{
	return mComponentsState[ID];
}

/// Function that init all the components
void TComponentArray::initComponents()
{
	for (auto& Component : mComponents)
	{
		Component->init();
	}
}

/// Function that init a single component by component type
template <class T>
void TComponentArray::initComponent()
{
	getComponent<T>().init();
}

/// Function that init a single component by component ID
void TComponentArray::initComponent(TComponentID ID)
{
	getComponent(ID)->init();
}