#ifndef INSTALLER_HPP
#define INSTALLER_HPP

#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>

#include "global.hpp"
#include "lang.hpp"

namespace Secundo
{
    class Installer
    {
    private:
        std::string user;

        void clone(std::string package, std::string o_dir)
        {
            if (system(std::string("git clone https://github.com/"+user+"/"+package+".git "+o_dir).c_str()) != 0)
            {
                std::cout << "Error! Check this out:" << std::endl;
                std::cout << "\t- is git installed?" << std::endl;
                std::cout << "\t- does the repository exist?" << std::endl;
                std::cout << "\t- does the github-user exist?" << std::endl;
                std::cout << "\t- are you root?" << std::endl;
                exit(1);
            }
        }

        void clean(std::string o_dir, std::string rem)
        {
            std::cout << ">> Cleaning " << o_dir << "..." << std::endl;
            if (system(std::string(rem+" "+o_dir).c_str()) != 0)
            {
                std::cout << "Error! Check this out:" << std::endl;
                std::cout << "\t- is git installed?" << std::endl;
                std::cout << "\t- does the repository exist?" << std::endl;
                std::cout << "\t- does the github-user exist?" << std::endl;
                std::cout << "\t- are you root?" << std::endl;
                exit(1);
            }
        }

    public:
        void init()
        {
            #ifdef _WIN32 || _WIN64
                mkdir("%appdata%\\secundo");
            #else
                mkdir("/usr/share/secundo", 755);
            #endif

            user = Secundo::Global.getUser();
        }

        void install(std::string package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "install";

            #ifdef _WIN32 || _WIN64
                o_dir = "%appdata%\\"+package_name;
                rem = "del";
                main_ = "install_win";
            #endif

            clone(package, o_dir);
            chdir(o_dir.c_str());
            Secundo::Seclang.run(o_dir+"/pkg/ins.sc", main_);
            clean(o_dir, rem);
        }

        void update(std::string package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "update";

            #ifdef _WIN32 || _WIN64
                o_dir = "%appdata%\\"+package_name;
                rem = "del";
                main_ = "update_win";
            #endif

            clone(package, o_dir);
            chdir(o_dir.c_str());
            Secundo::Seclang.run(o_dir+"/pkg/ins.sc", main_);
            clean(o_dir, rem);
        }

        void remove(std::string package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "remove";

            #ifdef _WIN32 || _WIN64
                o_dir = "%appdata%\\"+package_name;
                rem = "del";
                main_ = "remove_win";
            #endif

            clone(package, o_dir);
            chdir(o_dir.c_str());
            Secundo::Seclang.run(o_dir+"/pkg/ins.sc", main_);
            clean(o_dir, rem);
        }
    } Installer;
}

#endif