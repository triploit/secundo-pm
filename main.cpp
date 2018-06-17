#include <iostream>
#include <fstream>

#define LOCKF_ "/usr/share/secundo/lock.lck"

void _quit(int);

#include "translation.hpp"
#include "global.hpp"
#include "installer.hpp"
#include "lang/runtime.hpp"

void help();
bool is_argument(const std::string &arg);

std::string _VERSION = "0.1.7.3";

int main(int argc, char *argv[])
{
    Secundo::Installer.init();
    Secundo::Runtime.initLV();
    Secundo::Runtime.initConfig();

    char s[1024];
    getcwd(s, 1024);

    Secundo::Runtime.cPath = s;
    chdir("/");

    std::ifstream lock(LOCKF_);
    
    if (lock.is_open())
    {
        std::cout << ">> " << Secundo::Translation.get("12") << std::endl;
        exit(1);
    }
    else
    {
        std::ofstream(LOCKF_) << "LOCKED." << std::endl;
        lock.close();
    }

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "install" || arg == "ins" || arg == "-I")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    // Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

                    tri::string user = "";
                    tri::string regex = "[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}:[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}";
                    tri::string package = "";

                    if (Secundo::Runtime.regex_match(std::string(argv[i + 1]), regex.cxs()))
                    {
                        user = tri::string(argv[i + 1]).split(':')[0];
                        package = tri::string(argv[i + 1]).split(':')[1];

                        Secundo::Global.addInstallingPackage(Package(user.cxs(), package.cxs()));
                    }
                    else
                    {
                        printf(Secundo::Translation.get("10").c_str(), argv[i + 1]);
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "quiet")
        {
            std::cout << ">> " << Secundo::Translation.get("9", true) << std::endl;
            Secundo::Runtime.quiet = " > /dev/null";
            Secundo::Runtime.git_quiet = " --quiet";
        }
        else if (arg == "help" || arg == "-h" || arg == "--help")
        {help();
        }
        else if (arg == "version" || arg == "-v" || arg == "--version" || arg == "ver")
        {
            std::cout << _VERSION << std::endl;
        }
        else if (arg == "-l")
        {
            tri::_a42 = true;
        }
        else if (arg == "remove" || arg == "rem" || arg == "-R")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    // Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

                    tri::string user = "";
                    tri::string regex = "[a-z_\\d](?:[a-z_\\d]|-(?=[a-z_\\d])){0,38}:[a-z_\\d](?:[a-z_\\d]|-(?=[a-z_\\d])){0,38}"; // [a-z_\\d](?:[a-z_\\d]|-(?=[a-z_\\d])){0,38}
                    tri::string package = "";

                    if (Secundo::Runtime.regex_match(std::string(argv[i + 1]), regex.cxs()))
                    {
                        user = tri::string(argv[i + 1]).split(':')[0];
                        package = tri::string(argv[i + 1]).split(':')[1];

                        Secundo::Global.addRemovingPackage(Package(user.cxs(), package.cxs()));
                    }
                    else
                    {
                        printf(Secundo::Translation.get("10").c_str(), argv[i + 1]);
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "-Ua")
        {
            Secundo::Runtime.updateAll = true;
        }
        else if (arg == "update" || arg == "up" ||  arg == "-U")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    // Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

                    tri::string user = "";
                    tri::string regex = "[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}:[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}";
                    tri::string package = "";

                    if (Secundo::Runtime.regex_match(std::string(argv[i + 1]), regex.cxs()))
                    {
                        user = tri::string(argv[i + 1]).split(':')[0];
                        package = tri::string(argv[i + 1]).split(':')[1];

                        Secundo::Global.addUpdatingPackage(Package(user.cxs(), package.cxs()));
                    }
                    else if (std::string(argv[i + 1]) == "all")
                    {
                        Secundo::Runtime.updateAll = true;
                    }
                    else
                    {
                        printf(Secundo::Translation.get("10").c_str(), argv[i + 1]);
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
            }
        }
        else if (arg == "-ndc" || arg == "--no-dependency-checking")
        {
            Secundo::Runtime.noDepsCheck = true;
        }
        else if (arg == "-kf" || arg == "--keep-folders")
        {
            Secundo::Runtime.keepFolders = true;
        }
        else if (arg == "-s" || arg == "--server")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    Secundo::Runtime.repoServer = argv[i + 1];
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "trust")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    Secundo::Runtime.addTrusters(argv[i + 1]);
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "untrust")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    Secundo::Runtime.removeTrusters(argv[i + 1]);
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "list")
        {
            DIR *dir;
            struct dirent *ent;
            std::vector<Package> pkgs;

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

                    pkgs.push_back(Secundo::Seclang.createPackage(Secundo::Runtime.PackageFileDirectory+s.cxs()));
                }

                closedir(dir);
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("13", true) << std::endl;
                _quit(1);
            }

            std::vector<std::string> msgs;

            for (Package p : pkgs)
            {
                msgs.push_back("    - " + p.user + "   ->   " + p.name + " v" + p.version.str);
            }

            std::sort(msgs.begin(), msgs.end());

            printf(Secundo::Translation.get("11", true).c_str(), pkgs.size());

            for (std::string s : msgs)
            {
                std::cout << s << std::endl;
            }
        }
        else if (arg == "showtrust")
        {
            std::cout << "Trusting:" << std::endl;

            for (std::string s : Secundo::Runtime.trusted)
            {
                std::cout << "  - " << s << std::endl;
            }
        }
        else if (arg == "config")
        {
            std::string editor = "vi";

            if (Secundo::Runtime.Config["editor"])
                editor = Secundo::Runtime.Config["editor"].as<std::string>();

            if ((i+1) < argc && !is_argument(argv[i+1]))
            {
                editor = argv[i+1];
                i++;
            }    

            system(std::string(editor + " /usr/share/secundo/conf/config.yml").c_str());
        }
        else if (arg == "clean")
        {
            DIR *dir;
            struct dirent *ent;
            std::vector<Package> pkgs;
            int c = 0;

            if ((dir = opendir("/usr/share/secundo")) != NULL)
            {
                while ((ent = readdir(dir)) != NULL)
                {
                    tri::string s = ent->d_name;
                    s = s.trim();

                    if (s.at(0) == '.')
                        continue;

                    if (s.cxs() != "pkg_files" &&
                        s.cxs() != "lang" &&
                        s.cxs() != "conf" &&
                        s.cxs() != "lock.lck")
                    {
                        std::string rem = "rm -rf";

#ifdef _WIN32 || _WIN64
                        rem = "rmdir /s";
#endif

                        system(std::string(rem+" /usr/share/secundo/"+s.cxs()).c_str());
                        std::cout << "-> " << s.cxs() << std::endl;
                        c++;
                    }
                }

                closedir(dir);
                printf(std::string("\n>> "+Secundo::Translation.get("17", true)).c_str(), c);
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("16", true) << std::endl;
                _quit(1);
            }
        }
        else if (arg == "lang")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    chdir(Secundo::Runtime.cPath.c_str());

                    std::string fname = argv[i+1];
                    std::ifstream lfile(fname);

                    if (lfile.is_open())
                    {
                        std::vector<tri::string> path = tri::string(fname).split('/');
                        std::string oname = path[path.size()-1].cxs();

                        std::string line;
                        std::ofstream ofile("/usr/share/secundo/lang/"+oname);

                        while (std::getline(lfile, line))
                        {
                            ofile << line << std::endl;
                        }

                        ofile.close();
                    }
                    else
                    {
                        printf(std::string(">> "+Secundo::Translation.get("54", true)).c_str(), fname.c_str());
                    }

                    lfile.close();

                    if (Secundo::Translation.sentences["55"])
                        printf(std::string(">> "+Secundo::Translation.get("55", true)).c_str(), fname.c_str());
                    else
                        std::cout << ">> Language file was installed!" << std::endl;
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                chdir("/");
                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "local")
        {
            if ((i + 1) < argc)
            {
                if (!is_argument(argv[i + 1]))
                {
                    Secundo::Global.addInstallLocalPackage(std::string(argv[i + 1]));
                }
                else
                {
                    std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << ">> " << Secundo::Translation.get("8") << std::endl;
                help();
            }
        }
        else if (arg == "-iu" || arg == "--ignore-up-to-date")
        {
            Secundo::Runtime.ignoreUTD = true;
        }
        else
        {
            printf(Secundo::Translation.get("7", true).c_str(), arg.c_str());help();
        }
    }

    Secundo::Installer.init();

    if (Secundo::Runtime.updateAll)
    {
        Secundo::Installer.update_all();
    }

    for (int i = 0; i < Secundo::Global.getInstallLocalPackages().size(); i++)
    {
        printf(std::string("============================================\n>> "+Secundo::Translation.get("6")+"\n").c_str(),
                Secundo::Global.getInstallLocalPackages()[i].c_str());

        Secundo::Installer.install_local(Secundo::Global.getInstallLocalPackages()[i]);
        std::cout << ">> " << Secundo::Translation.get("2") << std::endl << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getInstallingPackages().size(); i++)
    {
        printf(std::string("============================================\n>> "+Secundo::Translation.get("5")+"\n").c_str(),
                Secundo::Global.getInstallingPackages()[i].user.c_str(),
                Secundo::Global.getInstallingPackages()[i].name.c_str());

        Secundo::Installer.install(Secundo::Global.getInstallingPackages()[i]);
        std::cout << ">> " << Secundo::Translation.get("2") << std::endl << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getRemovingPackages().size(); i++)
    {
        printf(std::string("============================================\n>> "+Secundo::Translation.get("4")+"\n").c_str(),
                Secundo::Global.getRemovingPackages()[i].user.c_str(),
                Secundo::Global.getRemovingPackages()[i].name.c_str());

        Secundo::Installer.remove(Secundo::Global.getRemovingPackages()[i]);
        std::cout << ">> " << Secundo::Translation.get("2") << std::endl << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getUpdatingPackages().size(); i++)
    {
        printf(std::string("============================================\n>> "+Secundo::Translation.get("3")+"\n").c_str(),
                Secundo::Global.getUpdatingPackages()[i].user.c_str(),
                Secundo::Global.getUpdatingPackages()[i].name.c_str());

        Secundo::Installer.update(Secundo::Global.getUpdatingPackages()[i]);
        std::cout << ">> " << Secundo::Translation.get("2") << std::endl << std::endl;
        chdir("/");
    }

    Secundo::Runtime.saveTrusters();
    _quit(0);
}

bool is_argument(const std::string &arg)
{
    if (std::string(arg) == "ins" ||
        std::string(arg) == "install" ||
        std::string(arg) == "remove" ||
        std::string(arg) == "rem" ||
        std::string(arg) == "update" ||
        std::string(arg) == "up" ||
        std::string(arg) == "user" ||
        std::string(arg) == "us" ||
        std::string(arg) == "local" ||
        std::string(arg) == "trust" ||
        std::string(arg) == "untrust" ||
        std::string(arg) == "showtrust" ||
        std::string(arg) == "quiet" ||
        std::string(arg) == "list" ||
        std::string(arg) == "clean" ||
        std::string(arg) == "config" ||
        std::string(arg) == "-s" ||
        std::string(arg) == "--server" ||
        std::string(arg) == "-kf" ||
        std::string(arg) == "--keep-folders" ||
        std::string(arg) == "-ndc" ||
        std::string(arg) == "--no-dependency-checking" ||
        std::string(arg) == "--help" ||
        std::string(arg) == "-h" ||
        std::string(arg) == "help" ||
        std::string(arg) == "-I" ||
        std::string(arg) == "-U" ||
        std::string(arg) == "-Ua" ||
        std::string(arg) == "-R")
        return true;

    return false;
}

void help()
{
    printf(std::string(Secundo::Translation.sentences["1"].as<std::string>()).c_str(), _VERSION.c_str());
    _quit(1);
}

void _quit(int i)
{
    if (std::ifstream(LOCKF_).is_open())
    {
        if (remove(LOCKF_) != 0)
            printf(std::string(">> "+Secundo::Translation.get("14")).c_str(), LOCKF_);
    }
    exit(i);
}
