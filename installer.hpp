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

		bool security(std::string script_file)
		{
			std::string ans = "";
			std::cout << "Do you want to see the build file? [y/n] ";

			while (ans != "y" && ans != "Y" && ans != "n" && ans != "N")
			{
				if (ans != "")
					std::cout << "Pleasye type 'y' or 'n'!";
				std::getline(std::cin, ans);

				if (ans == "n" || ans == "N")
				{
					std::cout << "Ok." << std::endl;
					break;
				}
			}

			if (ans == "y" || ans == "Y")
			{
				std::ifstream t(script_file);
				std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

				std::cout << "=============================================================" << std::endl;
				std::cout << str << std::endl;
				std::cout << "=============================================================" << std::endl;
			}

			ans = "";
			std::cout << "Are you sure to install this package? [y/n] ";

			while (ans != "y" && ans != "Y")
			{
				if (ans != "")
					std::cout << "Pleasye type 'y' or 'n'!";
				std::getline(std::cin, ans);

				if (ans == "n" || ans == "N")
				{
					std::cout << "Ok. Abort." << std::endl;
					return false;
				}
			}

			return true;
		}

        void clone(std::string package, std::string o_dir, bool local)
        {
            if (!local)
			{
				if (system(std::string("git clone https://github.com/"+user+"/"+package+".git "+o_dir).c_str()) != 0)
	            {
	                std::cout << "ERROR AT: git clone https://github.com/"+user+"/"+package+".git "+o_dir << std::endl << std::endl << "Error! Check this out:" << std::endl;
	                std::cout << "\t- is git installed?" << std::endl;
	                std::cout << "\t- does the repository exist?" << std::endl;
	                std::cout << "\t- does the github-user exist?" << std::endl;
	                std::cout << "\t- are you root?" << std::endl;
	                exit(1);
	            }
			}
        }

        void clean(const std::string& o_dir, const std::string& rem)
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
                mkdir(std::string("\""+Runtime.AppData+"\\secundo\"").c_str());
                mkdir(std::string("C:\\Program Files (x86)\\Secundo Software").c_str());
            #else
                mkdir("/usr/share/secundo", 755);
            #endif

            user = Secundo::Global.getUser();
        }

        void install_local(const std::string& path)
        {
            chdir(path.c_str());
            std::string main_ = "install";
            std::string script_file = path+"/pkg/ins.sc";

            #ifdef _WIN32 || _WIN64
                main_ = "install_win";
                script_file = path+"\\pkg\\ins.sc";
            #endif

			if (security(script_file)) Secundo::Seclang.run(script_file, main_);
        }

        void install(const std::string& package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "install";
            std::string script_file = o_dir+"/pkg/ins.sc";

            #ifdef _WIN32 || _WIN64
                o_dir = "\""+Runtime.AppData+"\\"+package+"\"";
                rem = "rmdir /s";
                main_ = "install_win";
                script_file = Runtime.AppData+"\\"+package+"\\pkg\\ins.sc";
            #endif

            clone(package, o_dir, false);
            chdir(o_dir.c_str());

			if (security(script_file)) Secundo::Seclang.run(script_file, main_);
            clean(o_dir, rem);
        }

        void update(const std::string& package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "update";
            std::string script_file = o_dir+"/pkg/ins.sc";

            #ifdef _WIN32 || _WIN64
                o_dir = "\""+Runtime.AppData+"\\"+package+"\"";
                rem = "rmdir /s";
                main_ = "update_win";
                script_file = Runtime.AppData+"\\"+package+"\\pkg\\ins.sc";
            #endif

            clone(package, o_dir, false);
            chdir(o_dir.c_str());
            Secundo::Seclang.run(script_file, main_);
            clean(o_dir, rem);
        }

        void remove(const std::string& package)
        {
            std::string o_dir = "/usr/share/secundo/"+package;
            std::string rem = "rm -rf";
            std::string main_ = "remove";
            std::string script_file = o_dir+"/pkg/ins.sc";

            #ifdef _WIN32 || _WIN64
                o_dir = "\""+Runtime.AppData+"\\"+package+"\"";
                rem = "rmdir /s";
                main_ = "remove_win";
                script_file = Runtime.AppData+"\\"+package+"\\pkg\\ins.sc";
            #endif

            clone(package, o_dir, false);
            chdir(o_dir.c_str());
            Secundo::Seclang.run(script_file, main_);
            clean(o_dir, rem);
        }
    } Installer;
}

#endif
