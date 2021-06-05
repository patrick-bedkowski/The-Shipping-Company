#include <string>
#include <vector>
#include <list>
#include "hub.h"

Hub::Hub(std::string const& name)
{
    /*
    Initializes a new instance of the Hub class.
    In:
    - name : The Hub name
    */
    this->name = name;
}

std::string Hub::getName() const
{
    /*
    Return the name of the Hub.
    */
    return name;
}

std::vector<const Package*> Hub::getPackages() const
{
    /* Returns reference to vector that holds packages */
	if ((packages).empty())
    {
		throw std::out_of_range(("There are no packages!"));
	}
	else
    {
		return packages;
	}
}

int Hub::getPackagesNumber() const
{
    /*
    Return the total number of Packages in the Hub.
    */
    return packages.size();
}

const Package* Hub::getPackage(const Package* whichPackage)
{
    /*
    Return the Packages from the Hub.
    In:
    - Package id number
    Out:
    - the Package
    */
    for (unsigned int index = 0; index < packages.size(); index++)
    {
        if (packages[index] == whichPackage)
        {
            return packages[index];
        }
    }
    throw std::invalid_argument("Package could not be found!");
}

void Hub::transferPackage(const Package* whichPackage, Hub& hub)
{
    /*
    Transfer the Package from the Hub to hub.
    Function delete package from the Hub.
    In:
    - whichPackage: Package to be transfer
    - hub: Receiving Hub 
    */
    hub += Hub::getPackage(whichPackage);
    Hub::delPackage(whichPackage);
}

void Hub::delPackage(const Package* whichPackage)
{   
    /*
    Get the Package from the Hub and delete it from the Hub.
    In:
    - whichPackage: Package to be return
    */
    for (unsigned int index = 0; index < packages.size(); index++)
    {
        if (packages[index] == whichPackage)
        {
            delete packages[index];
            packages.erase(packages.begin() + index);
        }
    }
}

const Package* Hub::popPackage(const Package* whichPackage)
{   
    /*
    Get the Package from the Hub delete it from the Hub and return.
    In:
    - whichPackage: Package to be return
    Out:
    - whichPackage: Package to be return
    */
    const Package* package = Hub::getPackage(whichPackage);
    Hub::delPackage(whichPackage);
    return package;
}

void Hub::operator+=(const Package* newPackage) {
    /*
    Add Package to the Hub.
    In:
    - newPackage: Package to be add
    */
    packages.push_back(newPackage);
}

void Hub::operator+=(const std::vector<const Package*> newPackages) {
    /*
    Add Packages to the Hub.
    In:
    - newPackages: Packages to be add
    */
    for(const auto& newPackage: newPackages) {
        packages.push_back(newPackage);
    }
}

bool Hub::operator==(Hub const& hub) const {
    /*
    Compare the Hub with hub.
    In:
    - hub: Hub to compare
    Out:
    - bool value of comparing
    */
    if (hub.getName() == Hub::name)
    {
        return true;
    }
    else {
        return false;
    }
}
