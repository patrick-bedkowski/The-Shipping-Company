#include "CppUnitTest.h"
#include <stdexcept>
#include "../ShippingCompany/app.h"

/********************************************************
 *					SOFTWARE TEST 						*
 ********************************************************
 *	This file contains tests of all classes and other	*
 *	logic methods of The Shipping Company software.		*
 *														*
 *	Tests are performed using Unit Test framework		*
 *	Correct data insertions are performed, as well as...*
 *														*
 *	The file is divied into test sections describing:	*
 *		> APP class										*
 *		> PACKAGE class and class that inherits from it	*
 *		> HUB class										*
 *		> READ/SAVE file management logic				*
 ********************************************************/

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


/********************************************************
 *														*
 *					APP CLASS TESTS						*
 *														*
 *******************************************************/


/* TEST CLASS THAT IHERITS FROM APP */
class TestApp : public App
{
public:
	TestApp() = default;
	~TestApp() = default;
	static TestApp* GetInstanceOfCompany() { return TestApp::classInstance = new TestApp(); };
	void TestApp::ReleaseInstanceOfCompany() { delete App::classInstance; }
	int hubsQuantity() { return App::hubsQuantity(); };
private:
	static TestApp* classInstance; // static instance of an App class
};

/* TEST CLASS */
TestApp *TestApp::classInstance; // define static member of a App class

namespace ShippingCompanyTests
{
	TEST_CLASS(ShippingCompanyTests)
	{
	public:
		TEST_METHOD(TestCreateHub)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			app->createHub("Warsaw"); // create hub

			for (Hub i : app->getHubs()) {
				Assert::AreEqual(std::string("Warsaw"), i.getName());
			}

			app->ReleaseInstanceOfCompany(); // delete app
		};
		TEST_METHOD(TestDeleteHub)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			app->createHub("Warsaw"); // create hub

			for (Hub i : app->getHubs()) {
				Assert::AreEqual(std::string("Warsaw"), i.getName());
			}

			app->closeHub("Warsaw"); // create hub

			auto func1 = [&] {app->getHubs(); }; // get availabe hubs
			Assert::ExpectException<std::out_of_range>(func1); // catch exception | There are no hubs

			app->ReleaseInstanceOfCompany(); // delete app
		};
		TEST_METHOD(AppendPackage)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			app->createHub("Warsaw"); // create hub

			// create package data
			packageDetails packageData;
			packageData.sender_address = "Kato";
			packageData.recipient_address = "Wroclaw";
			packageData.size = 'M';
			packageData.priority = false;

			Hub firsthub = (app->getHubs()).front(); // get firstly opened hub
			Assert::AreEqual(0, firsthub.getPackagesNumber()); // firsthub has zero packages

			app->sendPackage(&packageData, &firsthub);
			Assert::AreEqual(1, firsthub.getPackagesNumber()); // firsthub has one package

			const Package* to_delete = firsthub.getPackages().front(); // deallocate memory of a package

			delete to_delete;
			app->ReleaseInstanceOfCompany(); // delete app
		};
		TEST_METHOD(NumberOfHubs)
		{
			TestApp* testApp = TestApp::GetInstanceOfCompany(); // create object of App

			testApp->createHub("Warsaw"); // create hub
			testApp->createHub("Katowice"); // create hub
			testApp->createHub("Gliwice"); // create hub

			Assert::AreEqual(3, testApp->hubsQuantity());

			testApp->GetInstanceOfCompany(); // delete app
		};
		TEST_METHOD(getHubsNames)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			app->createHub("Hee"); // create hub
			app->createHub("Katowice"); // create hub
			app->createHub("Gliwice"); // create hub

			std::vector<Hub> hubs = app->getHubs();

			std::stringstream stream;
			for (Hub i : (hubs)) {
				stream << i.getName() << "\n";
			}

			std::string expected = "Hee\nKatowice\nGliwice\n";
			Assert::AreEqual(expected, stream.str());

			app->ReleaseInstanceOfCompany(); // delete app
		};

		TEST_METHOD(deleteSpecificPackage)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			// I. Create Hub
			app->createHub("Warsaw");

			// II. Prepare data of the Package
			packageDetails packageData;
			packageData.sender_address = "Kato";
			packageData.recipient_address = "Wroclaw";
			packageData.size = 'M';
			packageData.priority = false;

			// III. Get specific Hub
			//		This is a responsibility of an interface 
			//		to return a pointer to specific Hub that
			//		user wants to send a package to
			//	!	In this test the hub is selected manually
			Hub warsawHub = app->getHubs().front();
			// There is no package in this hub
			Assert::AreEqual(std::string("Warsaw"), warsawHub.getName());
			Assert::AreEqual(0, warsawHub.getPackagesNumber());

			// IV. send Package
			app->sendPackage(&packageData, &warsawHub);

			// Now, the package can be found in the hub
			Assert::AreEqual(1, warsawHub.getPackagesNumber());

			/* Return specific package from the warsawHub */

			// V. Get the package from the Hub
			//		This is a responsibility of an interface 
			//		to return a pointer to specific package that
			//		user wants to pick up
			//	!	In this test the package is selected manually
			const Package* packageToRelease = warsawHub.getPackages().front();

			Assert::AreEqual(std::string("Kato"), packageToRelease->getSenderAddress());

			// VI. Return package to user
			const Package* packageToReturn = app->popPackageFromHub(&warsawHub, packageToRelease);
			// object of a package is ready to be returned to user

			// The warsawHub has no packages left
			Assert::AreEqual(0, warsawHub.getPackagesNumber());

			app->ReleaseInstanceOfCompany(); // delete app
		};
		TEST_METHOD(InvalidSizeOfPackage)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			// I. Create Hub
			app->createHub("Warsaw");
			Hub warsawHub = app->getHubs().front();

			// II. Prepare data of the Package
			packageDetails packageData;
			packageData.sender_address = "Kato";
			packageData.recipient_address = "Wroclaw";
			packageData.size = 'H'; // Invalid SIZE
			packageData.priority = false;

			auto func1 = [&] {app->sendPackage(&packageData, &warsawHub); }; // send package with invalid size
			Assert::ExpectException<std::invalid_argument>(func1); // catch exception

			app->ReleaseInstanceOfCompany(); // delete app
		}
		TEST_METHOD(PopANonExistentPackage)
		{
			App* app = App::GetInstanceOfCompany(); // create object of App

			app->createHub("Warsaw"); // create hub
			Hub warsawHub = app->getHubs().front();

			// create a package with no data
			packageDetails packageData;
			const Package* package_1 = new S_Package(packageData);

			// Return a package that does NOT exist in the hub's database
			auto func1 = [&] {app->popPackageFromHub(&warsawHub, package_1); }; // send package with invalid size
			Assert::ExpectException<std::invalid_argument>(func1); // catch exception

			delete package_1;
			app->ReleaseInstanceOfCompany(); // delete app
		}
	};
}

/****************************************************
 *													*
 *				PACKAGE CLASS TESTS					*
 *			S_Package M_Package L_Package			*
 *													*
 ***************************************************/

namespace PackageClassTests
{
	TEST_CLASS(PackageClassTests)
	{
	public:
		TEST_METHOD(CreatePackage) {
			// Create package by inserting raw data 
			const Package* package_1 = new S_Package("Birmingham", "London", false, false);

			// Test if package data matches the input
			Assert::AreEqual(std::string("Birmingham"), package_1->getSenderAddress());
			Assert::AreEqual(std::string("London"), package_1->getRecipientAddress());
			Assert::AreEqual(false, package_1->getPriority());
			Assert::AreEqual(false, package_1->getFragility());

			delete package_1;
		}

		TEST_METHOD(CreatePackageWithStruct)
		{	
			// Create data for Package
			packageDetails data;
			data.sender_address = "Birmingham";
			data.recipient_address = "London";
			data.priority = false;
			data.fragile = false;

			// Create package
			const Package* package_1 = new S_Package(data);

			// Test if package data matches the input
			Assert::AreEqual(std::string("Birmingham"), package_1->getSenderAddress());
			Assert::AreEqual(std::string("London"), package_1->getRecipientAddress());
			Assert::AreEqual(false, package_1->getPriority());
			Assert::AreEqual(false, package_1->getFragility());
			delete package_1;
		};

		TEST_METHOD(CreatePackageWithStructMinimalized)
		{
			// It is also possible to initailize data of the pacakge like so:
			struct packageDetails data = {
				"Birmingham", "London",
				false, false
			};

			// Create package
			const Package* package_1 = new S_Package(data);

			// Test if package data matches the input
			Assert::AreEqual(std::string("Birmingham"), package_1->getSenderAddress());
			Assert::AreEqual(std::string("London"), package_1->getRecipientAddress());
			Assert::AreEqual(false, package_1->getPriority());
			Assert::AreEqual(false, package_1->getFragility());
			delete package_1;
		};

		TEST_METHOD(CompareCreatedPackages)
		{
			// Prepare data for packages
			struct packageDetails data = {
				"Birmingham", "London",
				false, false };

			// create two packages with the same set of data
			const Package* package_1 = new S_Package(data);
			const Package* package_2 = new S_Package(data);

			bool if_equal = ((*package_1) == (*package_2)); // compare two packages
			Assert::AreEqual(true, if_equal); // both packages are equal

			delete package_1;
			delete package_2;
		};

		TEST_METHOD(CompareDifferentSizePackages)
		{

			// Prepare data for packages
			struct packageDetails data = {
				"Birmingham",
				"London",
				false,
				false
			};

			// create two packages with the same set of data
			const Package* package_1 = new S_Package(data);
			const Package* package_2 = new M_Package(data);

			bool if_equal = (package_1 == package_2); // compare two packages
			Assert::AreEqual(false, if_equal);
			// even thought packages hold the same data
			// they are NOT equal because of their size

			delete package_1;
			delete package_2;
		};
	};
}

/************************************************
 *												*
 *				HUB CLASS TESTS					*
 *												*
 ***********************************************/

namespace HubClassTests
{
	TEST_CLASS(HubClassTests)
	{
	public:
		TEST_METHOD(CreateHub) {
			Hub first_hub("Warsaw"); // create hub

			Assert::AreEqual(std::string("Warsaw"), first_hub.getName()); // test name of the hub
			Assert::AreEqual(0, first_hub.getPackagesNumber()); // test number of packages


			auto func = [&] { first_hub.getPackages(); }; // view packages
			Assert::ExpectException<std::out_of_range>(func); // catch exception
			// vector is not holding any package
		};
		TEST_METHOD(AppendPackagesToHub) {
			Hub first_hub("Warsaw"); // create hub

			// create two packages
			const Package* package_1 = new S_Package("Birmingham", "London",
				false, false);
			const Package* package_2 = new S_Package("USA", "Italy",
				true, false);

			// append packages to Hub
			first_hub += package_1;
			first_hub += package_2;

			Assert::AreEqual(2, first_hub.getPackagesNumber()); // test number of packages

			delete package_1;
			delete package_2;
		};
		TEST_METHOD(RemovePackagesFromHub) {
			Hub first_hub("Warsaw"); // create hub

			// create two packages
			const Package* package_1 = new S_Package("Birmingham", "London",
													false, false);
			const Package* package_2 = new S_Package("USA", "Italy",
													true, false);

			// append packages to Hub
			first_hub += package_1;
			first_hub += package_2;
			Assert::AreEqual(2, first_hub.getPackagesNumber()); // test number of packages

			// Choose which package to remove
			const Package* package_to_remove;
			// select first appended package -> package_1
			package_to_remove = first_hub.getPackages().front();

			first_hub.popPackage(package_to_remove);
			Assert::AreEqual(1, first_hub.getPackagesNumber()); // test number of packages

			// Remove remaining package -> package_2
			package_to_remove = first_hub.getPackages().front();

			first_hub.popPackage(package_to_remove);
			Assert::AreEqual(0, first_hub.getPackagesNumber()); // test number of packages

			auto func = [&] { first_hub.getPackages(); }; // view packages
			Assert::ExpectException<std::out_of_range>(func); // catch exception
			// vector is not holding any package

		};
		TEST_METHOD(GetPackageFromHub) {
			Hub first_hub("Warsaw"); // create hub

			// create two package
			const Package* package_1 = new S_Package("Birmingham", "London",
													false, false);
			// append package to Hub
			first_hub += package_1;

			/* Now we need to create a pointer to a package that we want to get from Hub */
			const Package* package_to_return;
			// select first appended package -> package_1
			package_to_return = first_hub.getPackages().front();

			// Insert a pointer to a package and get object of that package
			const Package* received_package = first_hub.getPackage(package_to_return);

			// check if the returned package is equal to the inserted one
			bool are_equal = received_package == package_1;
			Assert::AreEqual(true, are_equal); 

			// Since this operation does not remove package from the database,
			// number of packages is equal to one
			Assert::AreEqual(1, first_hub.getPackagesNumber());

			delete package_1;
		};
		TEST_METHOD(DeletePackageFromHub) {
			Hub first_hub("Warsaw"); // create hub

			// create package
			const Package* package_1 = new S_Package("Birmingham","London",
													false,false);
			// append package to Hub
			first_hub += package_1;

			/* Now we need to create a pointer to a package that we want to delete from Hub */
			const Package* package_to_remove;
			// select first appended package -> package_1
			package_to_remove = first_hub.getPackages().front();

			Assert::AreEqual(1, first_hub.getPackagesNumber()); // test number of packages
			
			// delete package
			first_hub.delPackage(package_to_remove);

			// number of packages is equal to 0
			Assert::AreEqual(0, first_hub.getPackagesNumber()); // test number of packages
		};
		TEST_METHOD(TransferPackagesBetweenHubs) {
			Hub first_hub("Warsaw"); // create hub
			Hub second_hub("Katowice"); // create hub

			// create two packages
			const Package* package_1 = new S_Package("Birmingham", "London",
													false, false);
			// append package to Hub
			first_hub += package_1;
			Assert::AreEqual(1, first_hub.getPackagesNumber()); // test number of packages
			Assert::AreEqual(0, second_hub.getPackagesNumber()); // test number of packages

			// select package to transfer
			const Package* package_to_transfer;
			// select first appended package -> package_1
			package_to_transfer = first_hub.getPackages().front();

			// transfer package to hub 
			first_hub.transferPackage(package_to_transfer, second_hub);

			// confirm that number of packages has changed
			Assert::AreEqual(0, first_hub.getPackagesNumber());
			Assert::AreEqual(1, second_hub.getPackagesNumber());
		}
		TEST_METHOD(CompareHubs) {
			Hub first_hub("Warsaw"); // create hub
			Hub second_hub("Katowice"); // create hub

			// check if two hubs have the same name
			bool are_equal = (first_hub == second_hub);
			Assert::AreEqual(false, are_equal);

			// create third hub with the same name
			Hub third_hub("Warsaw"); // create hub
			are_equal = (first_hub == third_hub);
			Assert::AreEqual(true, are_equal);
		}
	};
}
