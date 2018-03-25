#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <vector>

namespace Secundo
{
    class Global
    {
    private:
        std::string user = "triploit";
        std::vector<std::string> removing_packages;
        std::vector<std::string> installing_packages;
        std::vector<std::string> local_packages;
        std::vector<std::string> updating_packages;

    public:
        void addInstallingPackage(std::string name)
        {
            installing_packages.push_back(name);
        }

        void addInstallLocalPackage(std::string path)
        {
            local_packages.push_back(path);
        }

        std::vector<std::string> getInstallLocalPackages()
        {
            return local_packages;
        }

        std::vector<std::string> getInstallingPackages()
        {
            return installing_packages;
        }

        void addRemovingPackage(std::string name)
        {
            removing_packages.push_back(name);
        }

        std::vector<std::string> getRemovingPackages()
        {
            return removing_packages;
        }

        void addUpdatingPackage(std::string name)
        {
            updating_packages.push_back(name);
        }

        std::vector<std::string> getUpdatingPackages()
        {
            return updating_packages;
        }

        void setUser(std::string name)
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
