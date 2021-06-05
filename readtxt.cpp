#include <iostream>
#include <fstream>
#include <exception>

#include "readtxt.h"

struct NoFileException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Such file does not exist!";
    }
};


std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> results;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        results.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    return results;
}

Package* readPackage(std::vector<std::string> row)
{
    bool priority, fragile;
    if ( row[3] == "1" ) priority = true;
    else priority = false;
    if ( row[4] == "1" ) fragile = true;
    else fragile = false;
    if ( row[0] == "S" )
    {
        return new S_Package(row[1], 
                             row[2],
                             priority, fragile);
    }
    else if ( row[0] == "M" )
    {
        return new M_Package(row[1], 
                             row[2],
                             priority, fragile);
    }
    else
    {
        return new L_Package(row[1], 
                             row[2],
                             priority, fragile);
    }
}

std::vector<Hub> readHubs(std::string fileName)
{
    std::ifstream file_(fileName);
    std::vector<Hub> hubs;
    if ( file_.is_open() )
    {
        std::string line;
        int index = -1;
        std::vector<std::string> new_line;
        bool priority, fragile;
        while ( std::getline(file_, line) )
        {
            new_line = split(line, ";-;");
            if ( new_line.size() == 1)
            {
                hubs.push_back( new_line[0] );
                index ++;
            }
            else
            {
                hubs[index] += readPackage(new_line);
            }
        }
    }
    else
    {
        throw NoFileException();
    }
    return hubs;
}
