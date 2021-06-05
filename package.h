#pragma once

#include <string>
#include <iostream>

// pass a struct to package and assign the data to attributes
// so it looks more clear
// also recipment address need to be specified right away

struct packageDetails {
	std::string sender_address;
	std::string recipient_address;
	char size;
	bool priority;
	bool fragile;
};

class Package
{
    public:
        Package(std::string,
                std::string,
                bool, bool);
        Package(packageDetails data);
        Package() = default;
        //~Package() = default;

        std::string getSenderAddress() const;
        std::string getRecipientAddress() const;
        std::string getInfo() const;
        bool getPriority() const;
        bool getFragility() const;
        float getCost() const;
        virtual char getSize() const = 0;
        virtual float packageCost() const = 0;
        virtual float optionalCosts() const = 0;

        void setSenderAddress(std::string);
        void setRecipientAddress(std::string);
        void setPriority(bool);
        void setFragile(bool);

        friend std::ostream& operator<<(std::ostream& out, const Package* package);
        bool operator==(const Package& package) const;

    protected:
        std::string sender_address;
        std::string recipient_address;
        bool priority;
        bool fragile;
};

class S_Package: public Package
{
    public:
        S_Package(std::string,
                  std::string,
                  bool, bool);
        S_Package(packageDetails data);
        float packageCost() const;
        float optionalCosts() const;
        char getSize() const;
};

class M_Package: public Package
{
    public:
        M_Package(std::string,
                  std::string,
                  bool, bool);
        M_Package(packageDetails data);
        float packageCost() const;
        float optionalCosts() const;
        char getSize() const;
};

class L_Package: public Package
{
    public:
        L_Package(std::string,
                  std::string,
                  bool, bool);
        L_Package(packageDetails data);
        float packageCost() const;
        float optionalCosts() const;
        char getSize() const;
};

std::ostream& operator<<(std::ostream& out, const Package* package);
