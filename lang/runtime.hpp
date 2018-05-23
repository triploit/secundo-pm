#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <vector>
#include <regex>
#include "obj/token.hpp"
#include "../exec.hpp"

namespace Secundo
{
    class Runtime
    {
    public:
        int LineNumber = 1;
        int Index = 1;
        bool Main = false;
        bool Verbose = true;
        bool noDepsCheck = false;
        bool keepFolders = false;
        bool ignoreUTD = false;

        std::string Scope;
        std::string CommandType;
        std::string MainFunction = "install";
        std::string M_Line;
        std::string M_Code;
        std::string quiet = "";
        std::string git_quiet = "";
        std::string cPath;
        std::string repoServer = "github.com";

        std::vector<Token> Tokens;
        std::vector<std::string> DeletingFiles;
        std::vector<std::string> Dependencies;
        std::vector<std::string> trusted;

        std::string AppData = "";
        std::string PackageFileDirectory = "";
        std::string TrustFile = "";

        void initLV()
        {
            TrustFile = "/usr/share/secundo/secpm_trustings.conf";
            PackageFileDirectory = "/usr/share/secundo/pkg_files/";
            std::string user = exec("whoami");


#ifdef _WIN32 || _WIN64
            user = "none"
            TrustFile = AppData+"\\secpm_trustings.conf";
            PackageFileDirectory = AppData+"\\pkg_files\\";
            AppData = std::string(getenv("AppData"));
#else
            user = exec("whoami");
            user = user.substr(0, user.length() - 1);
            if (user != "root")
            {
                std::cout << "Error: You must be root to use this programm!" << std::endl;
                _quit(1);
            }
#endif

            loadTrust();
        }

        bool isTruster(const std::string &user)
        {
            for (std::string t : trusted)
            {
                if (t == user) return true;
            }

            return false;
        }

        void addTrusters(const std::string &t)
        {
            if (!isTruster(t)) trusted.push_back(t);
        }

        void removeTrusters(const std::string &t)
        {
            for (int i = 0; i < trusted.size(); i++)
            {
                if (trusted[i] == t) trusted.erase(trusted.begin() + i);
            }
        }


        bool regex_match(const std::string &str, const std::string &pattern)
        {
            std::smatch matches;
            return (std::regex_match(str, std::regex(pattern)));
        }

        void saveTrusters()
        {
            std::ofstream afile(TrustFile);

            for (std::string t : trusted)
            {
                afile << t << std::endl;
            }
            afile.close();
        }

        void loadTrust()
        {
            std::ifstream afile(TrustFile, std::ios::in);

            if (afile.is_open())
            {
                std::string line;
                while (std::getline(afile, line))
                {
                    trusted.push_back(line);
                }
                afile.close();
            }
            else
            {
                std::cout << "Warning: Unable to open trust-file.\n";
            }
        }
    } Runtime;
}

#endif
