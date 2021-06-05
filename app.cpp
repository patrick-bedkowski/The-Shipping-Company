/********************************************************
 *					APP CLASS METHODS					*
 ********************************************************
 *	This file contains logic methods of the app class	*
 *  see app.h											*
 ********************************************************/
#include "app.h"

 // create static member of a App class
App *App::classInstance;

/// <returns>Instance of the App class</returns>
App* App::GetInstanceOfCompany(){
		return App::classInstance = new App();
}

void App::ReleaseInstanceOfCompany() {
	delete App::classInstance;
}

/********************************************************
 *					 PUBLIC METHODS						*
 *******************************************************/

// Creates a hub that is stored in a vector
void App::createHub(std::string hubName) {
	App::hubs.push_back(Hub(hubName)); // anonymous object
}

// Creates a hub that is stored in a vector
void App::createHub(Hub hub) {
	App::hubs.push_back(hub); // anonymous object
}

// Dismantles a hub that is stored in a vector
void App::closeHub(std::string hubName) {
	// If there are no hubs in a vector
	if((App::hubs).empty()) {
		throw std::out_of_range("There are no hubs to close!");
	}
	else {
		// create a pointer to increase code readability
		std::vector<Hub>* vptr = &(App::hubs);
		(*vptr).erase(std::remove((*vptr).begin(), (*vptr).end(), Hub(hubName)), (*vptr).end());
	}
}

// Clears hubs vector
void App::clearHubs() {
	hubs.clear();
}

/// <summary>
/// Creates an object of a package and assigns it to specific hub.
/// <param>
/// If wrong data has been inserted into this function.
/// Exception will be thrown.
/// </param>
/// </summary> 
/// <param name = 'data'>
/// - pointer to data describing a package</param>
/// <param name = 'whichHub'>
/// - pointer to chosen hub</param>
float App::sendPackage(packageDetails* data, Hub* whichHub) {
	// check package size
	switch ((char)(*data).size) {
	case 'S':
	{
		Package* ptrPackage = new S_Package(*data);
		appendPackageToHub(ptrPackage, whichHub);
		// save cost of created package
		float packageCost = (*ptrPackage).getSize();
		return packageCost;
	}
	case 'M':
	{
		Package* ptrPackage = new M_Package(*data);
		appendPackageToHub(ptrPackage, whichHub);
		// save cost of created package
		float packageCost = (*ptrPackage).getSize();
		return packageCost;
	}
	case 'L':
	{
		Package* ptrPackage = new L_Package(*data);
		appendPackageToHub(ptrPackage, whichHub);
		// save cost of created package
		float packageCost = (*ptrPackage).getSize();
		return packageCost;
	}
	default:
		throw std::invalid_argument("Inserted data was corrupted!");
	}
}

/// <summary>
/// Function proceeds to return a package which can be found
/// in a specific hub. 
/// This function is called, when a user wants his package
/// to be returned.
/// <param>
/// If wrong data has been inserted into this function.
/// Exception will be thrown.
/// </param>
/// </summary> 
/// <param name = 'whichHub'>
/// - pointer to chosen hub</param>
/// <param name = 'whichPackage'>
/// - pointer to package which is to be returned to user</param>
/// <returns>Object of package</returns>
const Package* App::popPackageFromHub(Hub* whichHub, const Package* whichPackage) {
	// Pop package from hub database
	const Package* packageToReturn = whichHub->popPackage(whichPackage);
	return packageToReturn; // return the package
}

// Returns reference to vector that holds hubs
std::vector<Hub>& App::getHubs() {
	// If there are no hubs in a vector
	if ((App::hubs).empty()) {
		throw std::out_of_range(("There are no hubs!"));
	}
	else{
		return (App::hubs);
	}
}

/********************************************************
 *					 PROTECTED METHODS					*
 *******************************************************/

// Returns a number of availabe hubs
int App::hubsQuantity() {
	return hubs.size();
}

// Returns pointer to hub with least packages
Hub* App::getHubWithMinPackages() {
	Hub* min;
	min = &(App::hubs[0]); // assign min to first hub

	// iterate through every hub
	for (Hub i : (App::hubs)) {
		// number of packages of the current hub
		int numberOfPackages = i.getPackagesNumber();
		// if number of pacakges is less than the minimum
		if (numberOfPackages < (*min).getPackagesNumber()) {
			(*min) = i; // assign new minimum hub
		}
	}
	return min; // return pointer to a hub
}

/// <summary>
/// Assigns package to a specific hub passed by a parameter
/// </summary>
/// <param name = 'package'>
/// - object of a package to be assigned to hub</param>
/// <param name = 'whichHub'>
/// - pointer to chosen hub</param>
void App::appendPackageToHub(const Package* package, Hub* whichHub){
	*whichHub += package;
}
