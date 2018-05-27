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
#include "package.hpp"
#include "translation.hpp"

namespace Secundo
{
    class Installer
    {
    private:
        std::string user;

        bool security(std::string script_file, const Package &p)
        {
            if (Runtime.isTruster(p.user))
                return true;

            std::string ans = "";
            std::cout << Secundo::Translation.get("18") << " [y/n] ";

            while (ans != "y" && ans != "Y" && ans != "n" && ans != "N")
            {
                if (ans != "")
                    std::cout << Secundo::Translation.get("19");
                std::getline(std::cin, ans);

                if (ans == "n" || ans == "N")
                {
                    std::cout << Secundo::Translation.get("20") << std::endl;
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
            std::cout << Secundo::Translation.get("21") << " [y/n] ";

            while (ans != "y" && ans != "Y")
            {
                if (ans != "")
                    std::cout << Secundo::Translation.get("19");
                std::getline(std::cin, ans);

                if (ans == "n" || ans == "N")
                {
                    std::cout << Secundo::Translation.get("22") << std::endl;
                    return false;
                }
            }

            return true;
        }

        void clone(const Package &package, std::string o_dir, bool local)
        {
            if (!local)
            {
                if (system(std::string(
                        "git clone https://"+Secundo::Runtime.repoServer+"/" + package.user + "/" + package.name + ".git " + o_dir + " " +
                        Secundo::Runtime.git_quiet).c_str()) != 0)
                {
                    printf(Secundo::Translation.get("15").c_str(), 
                        Secundo::Runtime.repoServer.c_str(), 
                        package.user.c_str(), 
                        package.name.c_str(), 
                        o_dir.c_str());

                    _quit(1);
                }
            }
        }

        void clean(const std::string &o_dir, const std::string &rem)
        {
            if (!Runtime.keepFolders)
            {
                std::cout << ">> Cleaning " << o_dir << "..." << std::endl;
                if (system(std::string(rem + " " + o_dir).c_str()) != 0)
                {
                    printf(std::string(">> "+Secundo::Translation.get("22")).c_str(), rem.c_str(), o_dir.c_str());
                    _quit(1);
                }
            }
        }

        void saveInstallFile(std::string from, std::string to)
        {
            std::ifstream src(from, std::ios::binary);
            std::ofstream dst(to, std::ios::binary);

            dst << src.rdbuf();
        }

        void check_secundo(const Package &pkg)
        {
            if (system("wget --help > /dev/null") != 0)
            {
                std::cout << ">> " << Secundo::Translation.get("24") << std::endl;
                _quit(1);
            }

            if (!Runtime.wgetLinkisNice("https://raw.githubusercontent.com/"+pkg.user+"/"+pkg.name+"/master/pkg/ins.sc"))
            {
                printf(std::string(">> "+Secundo::Translation.get("25")).c_str(), pkg.user.c_str(), pkg.name.c_str());
                _quit(1);
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
            mkdir("/usr/share/secundo/pkg_files", 755);
#endif

            user = Secundo::Global.getUser();
        }

        void install_local(const std::string &path)
        {
            chdir(std::string(Runtime.cPath+"/"+path).c_str());

            std::string main_ = "install";
            std::string script_file = "./pkg/ins.sc";

#ifdef _WIN32 || _WIN64
            main_ = "install_win";
            script_file = path+"\\pkg\\ins.sc";
#endif

            Package package = Secundo::Seclang.createPackage(script_file);

            if (security(script_file, Package("", ""))) 
                Secundo::Seclang.run(package, main_);

            std::string pt = Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc";
            printf(Secundo::Translation.get("26", true, true).c_str(), pt.c_str());

            saveInstallFile(script_file, Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc");
            std::cout << Secundo::Translation.get("2") << std::endl;
            chdir("/");
        }

        void install(const Package &package)
        {
            /*std::cout << ">> Checking if Secundo-Package." << std::endl;
            std::cout << ">> Finished. It is." << std::endl;*/
            check_secundo(package);

            std::string o_dir = "/usr/share/secundo/" + package.name;
            std::string rem = "rm -rf";
            std::string main_ = "install";
            std::string script_file = o_dir + "/pkg/ins.sc";

#ifdef _WIN32 || _WIN64
            o_dir = "\""+Runtime.AppData+"\\"+package.name+"\"";
            rem = "rmdir /s";
            main_ = "install_win";
            script_file = Runtime.AppData+"\\"+package.name+"\\pkg\\ins.sc";
#endif

            clone(package, o_dir, false);
            chdir(o_dir.c_str());

            /*
            char s[1024];
            getcwd(s, 1024);
            std::cout << "INSTALLER: " << s << std::endl;

            
            getcwd(s, 1024);
            std::cout << "INSTALLER: " << s << std::endl;
            */

            Package p = Secundo::Seclang.createPackage(script_file);
            Version v1 = p.version;
            Version v2 = package.version;

            if (v2 > Version("0.0.0.0") || v2 < Version("0.0.0.0"))
            {
                if (v2 < v1 || v2 > v1)
                {
                    std::cout << ">> " << Secundo::Translation.get("27") << std::endl;
                    printf(std::string(">> "+Secundo::Translation.get("28")).c_str(), package.version.str.c_str());

                    clean(o_dir, rem);
                    _quit(1);
                }
                else if (std::ifstream(Secundo::Runtime.PackageFileDirectory + package.user + "+" + package.name +".sc").is_open())
                {
                    if (Secundo::Seclang.createPackage(Secundo::Runtime.PackageFileDirectory + package.user + "+" + package.name +".sc").version == v1)
                    {
                        if (!Runtime.ignoreUTD)
                        {
                            std::cout << ">> " << Secundo::Translation.get("29") << std::endl;
                            clean(o_dir, rem);
                            return;
                        }
                        else
                            std::cout << ">> " << Secundo::Translation.get("30") << std::endl;
                    }
                }
            }
            else
            {
                if (std::ifstream(Secundo::Runtime.PackageFileDirectory + package.user + "+" + package.name +".sc").is_open())
                {
                    if (Secundo::Seclang.createPackage(Secundo::Runtime.PackageFileDirectory + package.user + "+" + package.name +".sc").version == v1)
                    {
                        if (!Runtime.ignoreUTD)
                        {
                            std::cout << ">> " << Secundo::Translation.get("29") << std::endl;
                            clean(o_dir, rem);
                            return;
                        }
                        else
                            std::cout << ">> " << Secundo::Translation.get("30") << std::endl;
                    }
                }
            }

            if (security(script_file, package)) 
                Secundo::Seclang.run(p, main_);

            std::string path = Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc";
            printf(Secundo::Translation.get("26", true, true).c_str(), path.c_str());

            saveInstallFile(script_file, Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc");
            std::cout << Secundo::Translation.get("2") << std::endl;

            clean(o_dir, rem);
            chdir("/");
        }

        void update_all()
        {
            std::string rem = "rm ";
#ifdef _WIN32 || _WIN64
            rem = "del ";
#endif

            std::string path = Secundo::Runtime.PackageFileDirectory;
            std::vector<Package> packages;
            std::string o_f = "/usr/share/secundo/tmp_ins.sc";

            DIR *dir;
            struct dirent *ent;

            if ((dir = opendir(Secundo::Runtime.PackageFileDirectory.c_str())) != NULL)
            {
                while ((ent = readdir(dir)) != NULL)
                {
                    tri::string s = ent->d_name;
                    s = s.trim();

                    if (s.at(0) == '.')
                        continue;

                    if (s.cxs().substr(s.length()-3, s.length()) != ".sc")
                    {
                        continue;
                    }

                    Package p = Secundo::Seclang.createPackage(Secundo::Runtime.PackageFileDirectory+s.cxs());

                    // https://raw.githubusercontent.com/user/name/master/pkg/ins.sc

                    if (!Runtime.wgetLinkisNice("https://raw.githubusercontent.com/"+p.user+"/"+p.name+"/master/pkg/ins.sc"))
                    {
                        printf(std::string(">> "+Secundo::Translation.get("25")).c_str(), p.user.c_str(), p.name.c_str());
                        return;
                    }

                    std::string command = "wget -q https://raw.githubusercontent.com/"+p.user+"/"+p.name+"/master/pkg/ins.sc -O "+o_f;

                    if (system(std::string(command + Secundo::Runtime.quiet).c_str()) != 0)
                    {
                        printf(std::string(">> "+Secundo::Translation.get("31")).c_str(), command.c_str());
                        _quit(1);
                    }
                    else
                    {
                        Package up = Secundo::Seclang.createPackage(o_f);
                        
                        if (!Runtime.ignoreUTD)
                        {
                            if (up.version > p.version)
                            {
                                packages.push_back(p);
                            }
                            else
                                printf(std::string(">> "+Secundo::Translation.get("32", true)).c_str(), p.user.c_str(), p.name.c_str());                                
                        }
                        else
                        {
                            printf(std::string(">> "+Secundo::Translation.get("33", true)).c_str(), p.user.c_str(), p.name.c_str());
                            packages.push_back(p);
                        }

                        system(std::string(rem+" /usr/share/secundo/tmp_ins.sc").c_str());
                    }
                }

                closedir(dir);
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("34") << std::endl;
                _quit(1);
            }

            for (Package package : packages)
            {                
                printf(std::string("============================================\n>> "+Secundo::Translation.get("3")).c_str(),
                    package.user.c_str(),
                    package.name.c_str());

                init();
                Secundo::Runtime.initLV();
                chdir("/");

                update(package);

                chdir("/");
                std::cout << ">> Finished!" << std::endl << std::endl;
            }
        }

        void update(const Package &package)
        {
            /*std::cout << ">> Checking if Secundo-Package." << std::endl;
            check_secundo(package);
            std::cout << ">> Finished. It is." << std::endl;*/

            std::string o_dir = "/usr/share/secundo/" + package.name;
            std::string rem = "rm -rf";
            std::string main_ = "update";
            std::string script_file = o_dir + "/pkg/ins.sc";

#ifdef _WIN32 || _WIN64
            o_dir = "\""+Runtime.AppData+"\\"+package.name+"\"";
            rem = "rmdir /s";
            main_ = "update_win";
            script_file = Runtime.AppData+"\\"+package.name+"\\pkg\\ins.sc";
#endif

            clone(package, o_dir, false);
            chdir(o_dir.c_str());

            Package p = Secundo::Seclang.createPackage(script_file);

            if (p.version <= package.version)
            {
                if (!Runtime.ignoreUTD)
                {
                    std::cout << ">> " << Secundo::Translation.get("29") << std::endl;
                    clean(o_dir, rem);
                    return;
                }
                else
                    std::cout << ">> " << Secundo::Translation.get("30") << std::endl;
            }

            if (security(script_file, package)) 
                Secundo::Seclang.run(p, main_);

            std::string path = Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc";
            printf(Secundo::Translation.get("26", true, true).c_str(), path.c_str());

            saveInstallFile(script_file, Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc");
            std::cout << Secundo::Translation.get("2") << std::endl;

            clean(o_dir, rem);
            chdir("/");
        }

        void remove(const Package &package)
        {
            /*std::cout << ">> Checking if Secundo-Package." << std::endl;
            check_secundo(package);
            std::cout << ">> Finished. It is." << std::endl;*/

            std::string o_dir = "/usr/share/secundo/" + package.name;
            std::string rem = "rm -rf";
            std::string main_ = "remove";
            std::string script_file = o_dir + "/pkg/ins.sc";

#ifdef _WIN32 || _WIN64
            o_dir = "\""+Runtime.AppData+"\\"+package.name+"\"";
            rem = "rmdir /s";
            main_ = "remove_win";
            script_file = Runtime.AppData+"\\"+package.name+"\\pkg\\ins.sc";
#endif

            std::string sc_script = Runtime.PackageFileDirectory + package.user + "+" + package.name + ".sc";
            std::ifstream f(sc_script, std::ios::in);

            printf(std::string("\n"+Secundo::Translation.get("35")).c_str(), sc_script.c_str());

            if (f.is_open())
            {
                std::cout << Secundo::Translation.get("36") << std::endl << std::endl;
                Runtime.DeletingFiles.push_back(sc_script);

                std::vector<Dependency> deps;

                if (!Runtime.noDepsCheck)
                {
                    DIR *dir;
                    struct dirent *ent;

                    if ((dir = opendir(Secundo::Runtime.PackageFileDirectory.c_str())) != NULL)
                    {
                        while ((ent = readdir(dir)) != NULL)
                        {
                            tri::string s = ent->d_name;
                            s = s.trim();

                            if (s.at(0) == '.')
                                continue;

                            if (s.cxs().substr(s.length()-3, s.length()) != ".sc")
                            {
                                continue;
                            }

                            if (s.cxs() == (package.user+"+"+package.name+".sc"))
                                continue;

                            Package p = Secundo::Seclang.createPackage(Secundo::Runtime.PackageFileDirectory+s.cxs());

                            for (Dependency d : p.dependencies.dependencies)
                            {
                                d.parent_user = p.user;
                                d.parent_name = p.name;

                                deps.push_back(d);
                            }
                        }

                        closedir(dir);
                    }
                    else
                    {
                        std::cout << ">> " << Secundo::Translation.get("34") << std::endl;
                        _quit(1);
                    }

                    for (Dependency d : deps)
                    {
                        if (package.name == d.name &&
                            package.user == d.user)
                        {
                            printf(std::string(">> "+Translation.get("38")).c_str(),
                                package.user.c_str(),
                                package.name.c_str(),
                                d.parent_user.c_str(),
                                d.parent_name.c_str());

                            std::cout << ">> " << Secundo::Translation.get("37") << std::endl;
                            return;
                        }
                    }
                }

                if (security(sc_script, package))
                    Secundo::Seclang.run(Secundo::Seclang.createPackage(sc_script), main_);
                f.close();
                return;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("39") << std::endl;
            }

            chdir("/");
        }
    } Installer;
}

#endif
