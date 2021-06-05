#pragma once

#include <string>
#include <vector>
#include <tuple>
#include "package.h"


class Hub {
    private:
        std::string name;
        std::vector<const Package*> packages;

    public:
        Hub() = default;
        Hub(std::string const& name);

        /// <summary>
        /// Returns hub name.
        /// </summary>
        /// <returns>
        /// Hub name.
        /// </returns>
        std::string getName() const;
        /// <summary>
        /// Returns hub packages.
        /// </summary>
        /// <returns>
        /// Pointer to the vector of packages. 
        /// </returns>
        std::vector<const Package*> getPackages() const;
        /// <summary>
        /// Returns number of packages.
        /// </summary>
        /// <returns>
        /// Number of packages.
        /// </returns>
        int getPackagesNumber() const;
        /// <summary>
        /// Returns package.
        /// </summary>
        /// <param name="whichPackage">
        /// - Pointer to the package that should be returned.
        /// </param>
        /// <returns>
        /// Pointer to the package.
        /// </returns>
        const Package* getPackage(const Package* whichPackage);
        /// <summary>
        /// Pops package.
        /// </summary>
        /// <param name="whichPackage">
        /// - Pointer to the package that should be popped.
        /// </param>
        /// <returns>
        /// Pointer to the package.
        /// </returns>
        const Package* popPackage(const Package* whichPackage);
        /// <summary>
        /// Deletes package.
        /// </summary>
        /// <param name="whichPackage">
        /// - Pointer to the package that should be deleted.
        /// </param>
        void delPackage(const Package* whichPackage);
        /// <summary>
        /// transfers package to different hub.
        /// </summary>
        /// <param name="whichPackage">
        /// - Pointer to the package that should be transfered.
        /// </param>
        /// <param name="hub">
        /// - Pointer to the hub to which package will be transfered.
        /// </param>
        void transferPackage(const Package* whichPackage, Hub& hub);

        void operator+=(const Package* new_package);
        void operator+=(std::vector<const Package*> new_packages);
        bool operator==(Hub const& hub) const;
};
