#pragma once

#include <iostream>
#include <string>
#include "app.h" //includes also: hub, package

class Interface
{
    private:
        App* app;

        /// <summary>
        /// Checks if given string input is a valid option in the current context.
        /// ("q" is always available)
        /// </summary> 
        /// <param name="input"> - User input.</param>
        /// <param name="options">
        /// - Number of options that are valid.
        /// </param>
        /// <returns>
        /// Information wheter user input corresponds to valid option.
        /// </returns>
        bool inputIsValidOption(
            std::string const& input,
            int const& options
        ) const;
        /// <summary>
        /// Checks if given string input is a valid value in the current context.
        /// </summary> 
        /// <param name="input"> - User input.</param>
        /// <param name="type">
        /// - Data type that is valid.
        /// </param>
        /// <returns>
        /// Information wheter user input corresponds to valid option.
        /// </returns>
        bool inputIsValidValue(
            std::string const& input,
            std::string const& type
        ) const;
        
        /// <summary>
        /// Prints invalid option message and waits for any key.
        /// </summary>
        void invalidOption() const;

        /// <summary>
        /// Prints invalid value message and waits for any key.
        /// </summary>
        void invalidValue() const;
    

        /// <summary>
        /// Prints menu and gets option input from user.
        /// </summary> 
        /// <param name="options">
        /// - Number of options that are valid.
        /// </param>
        /// <param name="menu_text">
        /// - Menu text that should be displayed after another message pops up.
        /// </param>
        /// <returns>
        /// Option selected by user.
        /// </returns>
        std::string getInputOption(
            int const& options,
            std::string const& menu_text
        ) const;
        /// <summary>
        /// Prints prompt and gets value input from user.
        /// </summary> 
        /// <param name="options">
        /// - Number of options that are valid.
        /// </param>
        /// <param name="prompt_text">
        /// - Prompt text that should be displayed after another message pops up.
        /// </param>
        /// <returns>
        /// Option selected by user.
        /// </returns>
        std::string getInputValue(
            std::string const& type,
            std::string const& prompt_text
        ) const;

        /// <summary>
        /// Prints main menu and waits for user to select option.
        /// </summary>
        /// <returns>
        /// Information wheter the menu should be closed.
        /// </returns> 
        bool mainMenu() const;
        
        /// <summary>
        /// Prints hub selcection menu and gets option input from user.
        /// </summary>
        /// <returns>
        /// Pointer to the hub selected by user.
        /// </returns>
        Hub* selectHub() const;

        /// <summary>
        /// Prints hubs management menu and waits for user to select option.
        /// </summary>
        /// <returns>
        /// Information wheter the menu should be closed.
        /// </returns> 
        bool hubsManagementMenu() const;
        /// <summary>
        /// Creates new hub with name given by user.
        /// </summary> 
        void hubCreator() const;
        /// <summary>
        /// Closes hub selected by user.
        /// </summary> 
        void hubCloser() const;
        /// <summary>
        /// Presents hubs list to the user.
        /// </summary> 
        void viewHubs() const;

        
        /// <summary>
        /// Creates package with parameters given by the user.
        /// </summary> 
        void addPackage() const;
        /// <summary>
        /// Releases package selected by the user.
        /// </summary> 
        void releasePackage() const;
        /// <summary>
        /// Presents packages list to the user.
        /// </summary> 
        void viewPackages() const;
        /// <summary>
        /// Reads session data from txt file.
        /// </summary> 
        void readFile() const;
        /// <summary>
        /// Saves session data to txt file.
        /// </summary> 
        void writeFile() const;

    public:
        /// <summary>
        /// Creates interface connect to given app.
        /// </summary> 
        Interface(App* app);
        /// <summary>
        /// Opens interface.
        /// </summary> 
        void open() const;
};
