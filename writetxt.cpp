#include <iostream>
#include <fstream>
#include <string>

#include "writetxt.h"


void writeHubs(std::string fileName, std::vector<Hub> hubs)
{
    std::ofstream file_(fileName);
    if ( file_.is_open() )
    {
        std::string row;
        for (int index = 0; index < hubs.size(); index++)
        {
            Hub hub = hubs[index];
            file_ << hub.getName() << ";-;\n";
            const std::vector<const Package*> packages = hub.getPackages();
            for (int index = 0; index < packages.size(); index++)
            {
                row = "";
                const Package* package = packages[index];
                row.push_back(package->getSize());
                row.append(";-;");
                row.append(package->getSenderAddress());
                row.append(";-;");
                row.append(package->getRecipientAddress());
                row.append(";-;");
                if (package->getPriority()) row.append("1");
                else row.append("0");
                row.append(";-;");
                if (package->getFragility()) row.append("1");
                else row.append("0");
                row.append(";-;");
                
                file_ << row << "\n";
            }
        }
        file_.close();
    }
}
