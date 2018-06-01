#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <vector>
#include <regex>
#include <yaml-cpp/yaml.h>
#include "obj/token.hpp"
#include "../exec.hpp"
#include "../translation.hpp"
#include "../tstring.hpp"

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
        bool updateAll = false;

        std::string Scope;
        std::string CommandType;
        std::string MainFunction = "install";
        std::string M_Line;
        std::string M_Code;
        std::string quiet = "";
        std::string git_quiet = "";
        std::string cPath;
        std::string ConfigPath = "";
        std::string repoServer = "github.com";

        std::vector<Token> Tokens;
        std::vector<std::string> DeletingFiles;
        std::vector<std::string> Dependencies;
        std::vector<std::string> trusted;

        std::string AppData = "";
        std::string PackageFileDirectory = "";
        std::string TrustFile = "";

        YAML::Node Config;

        void initLV()
        {
            TrustFile = "/usr/share/secundo/conf/trustings.conf";
            PackageFileDirectory = "/usr/share/secundo/pkg_files/";
            ConfigPath = "/usr/share/secundo/conf/config.yml";
            std::string user = exec("whoami");


#ifdef _WIN32 || _WIN64
            AppData = std::string(getenv("AppData"));
            user = "none"
            TrustFile = AppData+"\\conf\\trustings.conf";
            PackageFileDirectory = AppData+"\\pkg_files\\";
            ConfigPath = AppData+"\\conf\\config.yml";
#else
            user = exec("whoami");
            user = user.substr(0, user.length() - 1);

            if (user != "root")
            {
                std::cout << "You have to be root to run this program!" << std::endl;
                _quit(1);
            }
#endif

            loadTrust();
        }

        bool wgetLinkisNice(std::string link)
        {   
            if (tri::string(exec(std::string("wget --server-response --spider "+link+" 2>&1 | awk '/^  HTTP/{print $2}'").c_str())).trim().cxs() == "404")
            {
                return false;
            }

            return true;
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

        void initConfig()
        {
            if (std::ifstream(ConfigPath).is_open())
            {
                Config = YAML::LoadFile(ConfigPath);
            }
            else
            {
                std::ofstream(ConfigPath) << "trustcfg: /usr/share/secundo/trustings.conf\nlangcfg: /usr/share/secundo/lang/en.yml" << std::endl;
                Config = YAML::LoadFile(ConfigPath);
            }

            Translation.loadConfig(Config["langcfg"].as<std::string>());
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
                std::cout << Secundo::Translation.get("51") << std::endl;
            }
        }
    } Runtime;
}

#endif
