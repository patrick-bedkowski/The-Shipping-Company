#include "package.h"
#include <iostream>


std::string Package::getSenderAddress() const
{
    /*
    Return the Sender address of the Package.
    */
    return sender_address;
}

std::string Package::getRecipientAddress() const
{
    /*
    Return the Recipient address of the Package.
    */
    return recipient_address;
}

bool Package::getPriority() const
{
    /*
    Return bool if the Package is priority.
    */
    return priority;
}

bool Package::getFragility() const
{
    /*
    Return bool if the Package is fragile.
    */
    return fragile;
}

void Package::setSenderAddress(std::string new_address)
{
    /*
    Set new Sender address of the Package.
    In:
    - new_address: new address of sender
    */
    sender_address = new_address;
}

void Package::setRecipientAddress(std::string new_address)
{
    /*
    Set new Recipient address of the Package.
    In:
    - new_address: new address of recipient
    */
    recipient_address = new_address;
}

void Package::setPriority(bool new_priority)
{
    /*
    Set new priority status of the Package.
    In:
    - new_priority: new priority status
    */
    priority = new_priority;
}

void Package::setFragile(bool new_fragile)
{
    /*
    Set new fragile status of the Package.
    In:
    - new_fragile: new fragile status
    */
    fragile = new_fragile;
}

bool Package::operator==(const Package& package) const
{
    /*
    Compare two Packages.
    In:
    - package: package to compare
    */

    return (sender_address == package.sender_address)
        && (recipient_address == package.recipient_address)
        && (getSize() == package.getSize())
        && (priority == package.priority)
        && (fragile == package.fragile);
}

std::string Package::getInfo() const
{
    std::string result = "";
    result += sender_address;
    result += " --[";
    result += getSize();
    result += "]--> ";
    result += recipient_address;
    result += "\n";
    return result;
}

 std::ostream& operator<<(std::ostream& out, const Package* package)
 {
    /*
    Print the Package.
    In:
    - package: package to print
    */
    // Nadawca A --[S]--> Odbiorca B
    std::string result = "";
    result += package->getSenderAddress();
    result += " --[";
    result += package->getSize();
    result += "]--> ";
    result += package->getRecipientAddress();
    result += "\nCost " + std::to_string(package->getCost()) + " PLN\n";
    out << result << std::endl;
    return out;
 }

Package::Package(std::string sender_addr_,
                 std::string recipient_addr_,
                 bool priority_, bool fragile_)
{
    /*
    Initializes a new instance of the Package class.
    In:
    - sender_: sender
    - sender_addr_: sender address
    - recipient_: recipient
    - recipient_addr_: recipient address
    - priority_: if Package is priority
    - fragile_: if Package is fragile
    */
    sender_address = sender_addr_;
    recipient_address = recipient_addr_;
    priority = priority_;
    fragile = fragile_;
}

S_Package::S_Package(std::string sender_addr_,
                     std::string recipient_addr_,
                     bool priority_, bool fragile_) : Package(
                     sender_addr_,
                     recipient_addr_,
                     priority_, fragile_)
{
    /*
    Initializes a new instance of the Small Package class.
    In:
    - sender_addr_: sender address
    - recipient_addr_: recipient address
    - priority_: if Package is priority
    - fragile_: if Package is fragile
    */
    float cost = 1;
    if (Package::fragile) cost++;
    if (Package::priority) cost++;
}

M_Package::M_Package(std::string sender_addr_,
                     std::string recipient_addr_,
                     bool priority_, bool fragile_) : Package(
                     sender_addr_,
                     recipient_addr_,
                     priority_, fragile_)
{
    /*
    Initializes a new instance of the Medium Package class.
    In:
    - sender_addr_: sender address
    - recipient_addr_: recipient address
    - priority_: if Package is priority
    - fragile_: if Package is fragile
    */
    float cost = 2;
    if (Package::fragile) cost += 2;
    if (Package::priority) cost += 2;
}

L_Package::L_Package(std::string sender_addr_,
                     std::string recipient_addr_,
                     bool priority_, bool fragile_) : Package(
                     sender_addr_,
                     recipient_addr_,
                     priority_, fragile_)
{
    /*
    Initializes a new instance of the Large Package class.
    In:
    - sender_addr_: sender address
    - recipient_addr_: recipient address
    - priority_: if Package is priority
    - fragile_: if Package is fragile
    */
    float cost = 3;
    if (Package::fragile) cost += 3;
    if (Package::priority) cost += 3;
}

Package::Package(packageDetails data)
{
    /*
    Initializes a new instance of the Package class.
    In:
    - data: info about Package
    */
    sender_address = data.sender_address;
    recipient_address = data.recipient_address;
    priority = data.priority;
    fragile = data.fragile;
}

S_Package::S_Package(packageDetails data) : Package(data)
{
    /*
    Initializes a new instance of the Small Package class.
    In:
    - data: info about Package
    */
    float cost = 1;
    if (Package::fragile) cost++;
    if (Package::priority) cost++;
}

M_Package::M_Package(packageDetails data) : Package(data)
{
    /*
    Initializes a new instance of the Medium Package class.
    In:
    - data: info about Package
    */
    float cost = 2;
    if (Package::fragile) cost += 2;
    if (Package::priority) cost += 2;
}

L_Package::L_Package(packageDetails data) : Package(data)
{
    /*
    Initializes a new instance of the Large Package class.
    In:
    - data: info about Package
    */
    float cost = 3;
    if (Package::fragile) cost += 3;
    if (Package::priority) cost += 3;
}

float Package::getCost() const {
    return packageCost() + optionalCosts();
}

float S_Package::packageCost() const
{
    return 5.0;
}

float S_Package::optionalCosts() const
{
    return fragile*2 + priority*1;
}

char S_Package::getSize() const { 
    return 'S';
}

float M_Package::packageCost() const
{
    return 10.0;
}

float M_Package::optionalCosts() const
{
    return fragile * 4 + priority * 2;
}

char M_Package::getSize() const {
    return 'M';
}

float L_Package::packageCost() const
{
    return 15.0;
}

float L_Package::optionalCosts() const
{
    return fragile * 6 + priority * 4;
}

char L_Package::getSize() const {
    return 'L';
}
