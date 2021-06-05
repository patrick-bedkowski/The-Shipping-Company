/*************************************************************
 *  This project was created as part of the Object-Oriented	 *
 *  Programming class at Warsaw University of Technology	 *
 *************************************************************
 * Developers:												 *
 *	> Szymon Skarzyński										 *
 *	> Łukasz Jaremek										 *
 *	> Patryk Będkowski										 *
 *************************************************************
 * About the project:										 *
 *	The Shipping Company Simulator is a software that can	 *
 *	be used as a basic tool to simulate interraction with	 *
 *	multiple packages and shipping centres.					 *
 *************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <string>
#include "hub.h"

/// <summary>
/// Class represents a company that manages its hubs
///	and shipments. It acts as a bridge between program
/// operations and user interface. Thus handling every
/// user interaction.
/// <para>Build on Singleton pattern.</para>
/// </summary>
class App
{
public:
	// Safety measure for creating another instance of an app
	App(const App&) = delete;

	/// <returns>Instance of the App class</returns>
	static App* GetInstanceOfCompany();
	static void ReleaseInstanceOfCompany();

	void createHub(std::string hubName);
	void createHub(Hub hub);
	void closeHub(std::string hubName);
	void clearHubs();
	float sendPackage(packageDetails* data, Hub* whichHub);
	const Package* popPackageFromHub(Hub* whichHub, const Package* whichPackage);
	std::vector<Hub>& getHubs();
	void appendPackageToHub(const Package* package, Hub* whichHub);

protected:
	// constructor is defined as a private,
	// meaning that it cannot be called outside of this class
	App() = default;

	// static instance of an App class
	static App* classInstance;

	// returns number of hubs currently available
	int hubsQuantity();
	Hub* getHubWithMinPackages();
	std::vector<Hub> hubs; // vector that holds all hubs
};