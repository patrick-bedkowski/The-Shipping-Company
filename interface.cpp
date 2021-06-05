#include <iostream>
#include <string>
#include "interface.h" //includes also: app, hub, package
#include "readtxt.h"
#include "writetxt.h"

Interface::Interface(App* app)
{
    this->app = app;
};

bool Interface::inputIsValidOption(
    std::string const& input, 
    int const& options
) const
{
    if (input == "q")
    {
        return true;
    }
    for (int n = 1; n <= options; n++)
    {
        if (input == std::to_string(n))
        {
            return true;
        }
    }

    return false;
}

bool Interface::inputIsValidValue(
    std::string const& input,
    std::string const& type
) const
{
    if (input == "q" || type == "string")
    {
        return true;
    }
    else if (type == "int")
    {  
        for(const char& character: input)
        {
            if (isdigit(character) == false)
            {
                return false;
            }
        }
        return true;
    }
    else if (type == "size")
    { 
        return (input == "S"  || input == "M" || input == "L");
    }
    else if (type == "bool")
    { 
        return (input == "y" || input == "n");
    }
    else if (type == "float")
    {
        int dot_counter = 0;

        for(const char& character: input)
        {
            if (character == '.')
            {
                if (dot_counter == 0)
                {
                    dot_counter = 1;
                }
                else
                {
                    return false;
                }
            }
            else if (isdigit(character) == false)
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

void Interface::invalidOption() const
{
    /*
    Print message about invalid user option.
    */
    system("cls");
    std::cout << "Invalid option\n" << std::endl;
    system("pause");
}

void Interface::invalidValue() const
{
    /*
    Print message about invalid user value.
    */
    system("cls");
    std::cout << "Invalid value\n" << std::endl;
    system("pause");
}

std::string Interface::getInputOption(
    int const& options, 
    std::string const& menu_text
) const
{
    /*
    Get input option from user.
    In:
    - options:
    - menu_test: 
    */
    std::string input;

    while(true)
    {
        // std::cin >> input;
        std::getline(std::cin, input);
        if (inputIsValidOption(input, options))
        {
            return input;
        }
        else
        {
            invalidOption();

            system("cls");
            std::cout << menu_text;
        }
    }
}

std::string Interface::getInputValue(
    std::string const& type, 
    std::string const& prompt_text
) const
{
    /*
    Get input value from user.
    In:
    - type: 
    - prompt_text: 
    */
    system("cls");
    std::cout << prompt_text;

    std::string input;

    while(true)
    {
        // std::cin >> input;
        std::getline(std::cin, input);
        if (inputIsValidValue(input, type))
        {
            return input;
        }
        else
        {
            invalidValue();

            system("cls");
            std::cout << prompt_text;
        }
    }
}

Hub* Interface::selectHub() const
{
    /*
    Print the section on selecting a Hub
    */
    try
    {
        std::vector<Hub>& hubs = app->getHubs();

        std::string menu_text;
        menu_text += "Select the hub:\n";
        for(unsigned int i = 0; i < hubs.size(); i++)
        {
            menu_text += '\n';
            menu_text += std::to_string(i+1);
            menu_text += " - ";
            menu_text += hubs[i].getName();
        }
        menu_text += "\n\nq - BACK";
        menu_text += "\n\n:";

        system("cls");
        // std::cout << hubs.size() << std::endl;
        std::cout << menu_text;

        std::string input = getInputOption(hubs.size(), menu_text);
        if (input != "q")
        {
            int selected_index = std::stoi(input);
            for(unsigned int i = 0; i < hubs.size(); i++)
            {
                if (i == selected_index - 1)
                {
                    return &(hubs[i]);
                }
            }
        }
        else
        {
            //user goes back
            return nullptr;
        }
    }
    catch (const std::out_of_range& e)
    {
        throw e;
    }

    return nullptr;
}

void Interface::hubCreator() const
{
    /*
    Print the section on creating a Hub.
    */
    std::string prompt_text;
    prompt_text += "===Hub Creation===";
    prompt_text += "\n\nq - BACK";
    prompt_text += "\n\nName:";
    
    std::string input = getInputValue("string", prompt_text);

    if (input != "q")
    {
        app->createHub(input);
    }
}

void Interface::hubCloser() const
{
    /*
    Print out the section on shutting down the Hub.
    */
    try
    {
        const Hub* hub = selectHub();
        //check if user did not Back
        if (hub != nullptr)
        {
            app->closeHub(hub->getName());
        }
    }
    catch (const std::out_of_range& e)
    {
        throw e;
    }
}

void Interface::viewHubs() const
{
    try
    {
        std::vector<Hub>& hubs = app->getHubs();

        std::string text = "===Hubs List===\n";
        for(unsigned int i = 0; i < hubs.size(); i++)
        {
            text += '\n';
            text += std::to_string(i+1);
            text += " - ";
            text += hubs[i].getName();
        }
        text += "\n\nq - BACK";
        text += "\n\n:";

        system("cls");
        std::cout << text;

        std::string input = getInputOption(0, text);
    }
    catch (const std::out_of_range& e)
    {
        throw e;
    }
}

bool Interface::hubsManagementMenu() const
{
    /*
    Print section on selecting Hubs options.
    */
    std::string menu_text;
    menu_text += "===Hubs Management Menu===";
     menu_text += "\n\n1. Hubs List";
    menu_text += "\n2. Create Hub";
    menu_text += "\n3. Close Hub";
    menu_text += "\n\nq - BACK";
    menu_text += "\n\n:";

    system("cls");
    std::cout << menu_text;

    std::string input = getInputOption(3, menu_text);

    if (input == "q")
    {
        return  true;
    }
    else
    {
        switch(std::stoi(input))
        {
            case 1:
                try
                {
                    viewHubs();
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                    system("pause");
                }
                break;
            case 2:
                hubCreator();
                break;
            case 3:
               try
                {
                    hubCloser();
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                    system("pause");
                }
                break;
        }
    }
    return false;
}


void Interface::addPackage() const
{
    /*
    Print the section for adding Package.
    */
    try
    {
        Hub* hub = selectHub();

        // check if user goes back (input == "q")
        if (hub == nullptr)
        {
            return;
        }

        struct packageDetails package_details;

        std::string prompt_text;
        std::string input;

        // Sender address
        prompt_text = "q - BACK";
        prompt_text += "\n\nSender address:";
        
        input = getInputValue("string", prompt_text);

        if (input == "q")
        {
            return;
        }

        std::string sender_address = input;

        // Recipient address
        prompt_text = "q - BACK";
        prompt_text += "\n\nRecipient address:";
        
        input = getInputValue("string", prompt_text);

        if (input == "q")
        {
            return;
        }

        std::string recipient_address = input;

        // Size
        prompt_text = "q - BACK";
        prompt_text += "\n\nSize (S/M/L):";
        
        input = getInputValue("size", prompt_text);

        if (input == "q")
        {
            return;
        }

        char size = input[0];

        //Priority
        prompt_text = "q - BACK";
        prompt_text += "\n\nPriority (y/n):";
        
        input = getInputValue("bool", prompt_text);

        if (input == "q")
        {
            return;
        }

        bool priority = (input == "y");

        //Fragile
        prompt_text = "q - BACK";
        prompt_text += "\n\nFragile (y/n):";
        
        input = getInputValue("bool", prompt_text);

        if (input == "q")
        {
            return;
        }

        bool fragile = (input == "y");

        package_details.sender_address = sender_address;
        package_details.recipient_address = recipient_address;
        package_details.size = size;
        package_details.priority = priority;
        package_details.fragile = fragile;

        try
        {
            float cost = app->sendPackage(&package_details, hub);

            /* DISPLAY THE COST OF THE PACKAGE */
            system("cls");
            std::cout << "Addresed package price:"<< cost << " PLN\n" << std::endl;
            system("pause");
        }
        catch(const std::invalid_argument& e)
        {
            system("cls");
            std::cout << e.what() << std::endl << std::endl;
            system("pause");
        }
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "ok3" << std::endl;
        system("cls");
        std::cout << e.what() << std::endl << std::endl;
        system("pause");
    }
}

void Interface::releasePackage() const
{
    /*
    Print the section for release Package.
    */
    try
    {
        Hub* hub = selectHub();

        // check if user Backed
        if (hub == nullptr)
        {
            return;
        }
        
        std::string text = "Select the package:\n\n";

        const std::vector<const Package*> packages = hub->getPackages();

        for(unsigned int i = 0; i < packages.size(); i++)
        {
            text += std::to_string(i + 1);
            text += " - ";
            text += packages[i]->getInfo();
        }
        text += "\nq - BACK";
        text += "\n\n:";

        system("cls");
        std::cout << text;

        std::string input = getInputOption((packages).size(), text);
        if (input != "q")
        {
            int selected_index = std::stoi(input);
            for(unsigned int i = 0; i < (packages).size(); i++)
            {
                if (i == selected_index - 1)
                {   
                    try {
                        const Package* package = packages[i];
                        app->popPackageFromHub(hub, package);
                    }
                    catch (std::invalid_argument){
                        /* DISPLAY THE COST OF THE PACKAGE */
                        system("cls");
                        std::cout << "Package could not be found!\n" << std::endl;
                        system("pause");
                    }
                }
            }
        }

        if (input == "q")
        {
            return;
        }
    }
    catch (const std::out_of_range& e)
    {
        system("cls");
        std::cout << e.what() << std::endl << std::endl;
        system("pause");
    }
}

void Interface::viewPackages() const
{
    try
    {
        system("cls");
        std::string text;

        text = "===Packages List===\n\n";

        std::vector<Hub>& hubs = app->getHubs();

        // iterate through hubs
        for(unsigned int i = 0; i < hubs.size(); i++)
        {
            text += std::to_string(i + 1);
            text += " - ";
            text += hubs[i].getName();
            text += "\n";
            
            std::string package;
            try
            {
                const std::vector<const Package*> packages = hubs[i].getPackages();

                // iterate through hub packages
                for(unsigned int j = 0; j < packages.size(); j++)
                {
                    text += "\t";
                    text += packages[j]->getInfo();
                }
            }
            catch (const std::out_of_range& e)
            {
            
            }
        }
        text += "\nq - BACK";
        text += "\n\n:";

        system("cls");
        std::cout << text;

        std::string input = getInputOption(0, text);
    }
    catch (const std::out_of_range& e)
    {
        system("cls");
        std::cout << e.what() << std::endl << std::endl;
        system("pause");
    }
}

void Interface::readFile() const
{
    std::string prompt_text;
    prompt_text += "q - BACK";
    prompt_text += "\n\n(txt format will be used)";
    prompt_text += "\nFile name:";
    
    std::string input;
    input = getInputValue("string", prompt_text);
    // std::string input = "file.txt";

    if (input == "q")
    {
        return;
    }

    input += ".txt";

    try
    {
        std::vector<Hub> hubs = readHubs(input);
        
        app->clearHubs();
        
        for(unsigned int i = 0; i < hubs.size(); i++)
        {
            app->createHub(hubs[i]);
        }

        system("cls");
        std::cout << "Data loaded from file.\n" << std::endl;
        system("pause");
    }
    catch(...)
    {
        // ERROR HERE
        system("cls");
        std::cout << "Such file does not exist!\n" << std::endl;
        // std::cout << e.what() << std::endl << std::endl;
        system("pause");
    }

}

void Interface::writeFile() const
{
    std::string prompt_text;
    prompt_text += "q - BACK";
    prompt_text += "\n\n(txt format will be used)";
    prompt_text += "\nFile name:";
    
    std::string input;
    input = getInputValue("string", prompt_text);
    // std::string input = "file.txt";

    if (input == "q")
    {
        return;
    }

    input += ".txt";

    try
    {
        writeHubs(input, app->getHubs());
    }
    catch(...)
    {
        // ERROR HERE
        system("cls");
        std::cout << "Error occured when writing to file.\n" << std::endl;
        system("pause");
    }

}

bool Interface::mainMenu() const
{
    /*
    Print the section about the main menu.
    */
    std::string menu_text;
    menu_text += "===Main Menu===";
    menu_text += "\n\n1. Hubs Management";
    menu_text += "\n2. Packages List";
    menu_text += "\n3. Add Package";
    menu_text += "\n4. Release Package";
    menu_text += "\n5. Read from file";
    menu_text += "\n6. Save to file";
    menu_text += "\n\nq - QUIT";
    menu_text += "\n\n:";

    system("cls");
    std::cout << menu_text;

    std::string input = getInputOption(6, menu_text);
    
    if (input == "q")
    {
        return true;
    }
    else
    {
        switch(std::stoi(input))
        {
            case 1:
                bool exit;
                do
                {
                    exit = hubsManagementMenu();
                } while(exit == false);
                break;
            case 2:
                viewPackages();
                break;
            case 3:
                addPackage();
                break;
            case 4:
                releasePackage();
                break;
            case 5:
                readFile();
                break;
            case 6:
                writeFile();
                break;
        }
    }

    return false;
}

void Interface::open() const
{
    /*
    Main loop.
    */
    bool exit;
    do
    {
        exit = mainMenu();
    } while(exit == false);

    system("cls");
    std::cout << "Interface closed";
}
