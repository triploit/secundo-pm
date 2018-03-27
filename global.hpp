#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <vector>
#include "package.hpp"

namespace Secundo
{
    class Global
    {
    private:
        std::string user = "triploit";
        std::vector<Package> removing_packages;
        std::vector<Package> installing_packages;
        std::vector<std::string> local_packages;
        std::vector<Package> updating_packages;

    public:
        void addInstallingPackage(const Package& p)
        {
            installing_packages.push_back(p);
        }

        void addInstallLocalPackage(const std::string& path)
        {
            local_packages.push_back(path);
        }

        std::vector<std::string> getInstallLocalPackages()
        {
            return local_packages;
        }

        std::vector<Package> getInstallingPackages()
        {
            return installing_packages;
        }

        void addRemovingPackage(const Package& p)
        {
            removing_packages.push_back(p);
        }

        std::vector<Package> getRemovingPackages()
        {
            return removing_packages;
        }

        void addUpdatingPackage(const Package& p)
        {
            updating_packages.push_back(p);
        }

        std::vector<Package> getUpdatingPackages()
        {
            return updating_packages;
        }

        void setUser(const std::string& name)
        {
            user = name;
        }

        std::string getUser()
        {
            return user;
        }

    } Global;
}

#endif
