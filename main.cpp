#include <iostream>
#include <fstream>

#define LOCKF_ "/usr/share/secundo/lock.lck"

void _quit(int i)
{
    if (std::ifstream(LOCKF_).is_open())
    {
        if (remove(LOCKF_) != 0)
            std::cout << ">> Error deleting lock file " << LOCKF_ << "!" << std::endl;
    }
    exit(i);
}

#include "global.hpp"
#include "installer.hpp"
#include "lang/runtime.hpp"

void help();

bool is_argument(const std::string &arg);

std::string _VERSION = "0.1.6.3";

int main(int argc, char *argv[])
{

    Secundo::Installer.init();
    Secundo::Runtime.initLV();

    char s[1024];
    getcwd(s, 1024);

    Secundo::Runtime.cPath = s;
    chdir("/");

    std::ifstream lock(LOCKF_);
    
    if (lock.is_open())
    {
        std::cout << ">> Error! Lock file /usr/share/secundo/lock.lck exists,\n   so an instance of secpm is already running!\n>> If this is a bug, delete this file, but BE SURE! Remove it at your own risk!" << std::endl;
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

        if (arg == "install" || arg == "ins")
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
                        std::cout << "Wrong package name: " << argv[i + 1] << std::endl;
                        std::cout << "\nThis is a package name:  user:package" << std::endl;
                        std::cout << "                         triploit:secpundo-pm" << std::endl;
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
                help();
            }
        }
        else if (arg == "quiet")
        {
            std::cout << ">> Quiet mode activated." << std::endl;
            Secundo::Runtime.quiet = " > /dev/null";
            Secundo::Runtime.git_quiet = " --quiet";
        }
        else if (arg == "help" || arg == "-h" || arg == "--help")
        {
            help();
        }
        else if (arg == "version" || arg == "-v" || arg == "--version" || arg == "ver")
        {
            std::cout << _VERSION << std::endl;
        }
        else if (arg == "remove" || arg == "rem")
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
                        std::cout << "Wrong package name: " << argv[i + 1] << std::endl;
                        std::cout << "This is a package name:  user:package" << std::endl;
                        std::cout << "                         triploit:secpundo-pm" << std::endl;
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
                help();
            }
        }
        else if (arg == "update" || arg == "up")
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
                        std::cout << "Wrong package name: " << argv[i + 1] << std::endl;
                        std::cout << "This is a package name:  user:package" << std::endl;
                        std::cout << "                         triploit:secpundo-pm" << std::endl;
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
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
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
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
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
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
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
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
                std::cout << ">> There was an error! Directory for the package-files not found!" << std::endl;
                _quit(1);
            }

            std::vector<std::string> msgs;

            for (Package p : pkgs)
            {
                msgs.push_back("    - " + p.user + "   ->   " + p.name + " v" + p.version.str);
            }

            std::sort(msgs.begin(), msgs.end());
            std::cout << "Installed " << pkgs.size() << " packages:" << std::endl;

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
                        s.cxs() != "secpm_trustings.conf" &&
                        s.cxs() != "lock.lck")
                    {
                        std::string rem = "rm -rf";

#ifdef _WIN32 || _WIN64
                        rem = "rmdir /s";
#endif

                        system(std::string(rem+" /usr/share/secundo/"+s.cxs()).c_str());
                        c++;
                    }
                }

                closedir(dir);
                if (c == 1)
                    std::cout << ">> Cleaned " << c << " object." << std::endl;
                else
                    std::cout << ">> Cleaned " << c << " objects." << std::endl;
            }
            else
            {
                std::cout << ">> There was an error! Directory /usr/share/secundo not found!" << std::endl;
                _quit(1);
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
                    std::cout << "Syntax error!\n" << std::endl;
                    help();
                }

                i++;
            }
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
                help();
            }
        }
        else if (arg == "-iu" || arg == "--ignore-up-to-date")
        {
            Secundo::Runtime.ignoreUTD = true;
        }
        else
        {
            std::cout << "Option \"" << arg << "\" not found!" << std::endl;
            help();
        }
    }

    Secundo::Installer.init();

    if (Secundo::Runtime.updateAll)
    {
        Secundo::Installer.update_all();
    }

    for (int i = 0; i < Secundo::Global.getInstallLocalPackages().size(); i++)
    {
        std::cout << "============================================\n>> Installing Local Directory "
                  << Secundo::Global.getInstallLocalPackages()[i] << "..." << std::endl;

        Secundo::Installer.install_local(Secundo::Global.getInstallLocalPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getInstallingPackages().size(); i++)
    {
        std::cout << "============================================\n>> Installing "
                  << Secundo::Global.getInstallingPackages()[i].user << "'s "
                  << Secundo::Global.getInstallingPackages()[i].name << "..." << std::endl;

        Secundo::Installer.install(Secundo::Global.getInstallingPackages()[i]);
        std::cout << ">> Finished!" << std::endl << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getRemovingPackages().size(); i++)
    {
        std::cout << "============================================\n>> Remove "
                  << Secundo::Global.getRemovingPackages()[i].user << "'s "
                  << Secundo::Global.getRemovingPackages()[i].name << "..." << std::endl;

        Secundo::Installer.remove(Secundo::Global.getRemovingPackages()[i]);
        std::cout << ">> Finished!" << std::endl << std::endl;
        chdir("/");
    }

    for (int i = 0; i < Secundo::Global.getUpdatingPackages().size(); i++)
    {
        std::cout << "============================================\n>> Updating "
                  << Secundo::Global.getUpdatingPackages()[i].user << "'s "
                  << Secundo::Global.getUpdatingPackages()[i].name << "..." << std::endl;

        Secundo::Installer.update(Secundo::Global.getUpdatingPackages()[i]);
        std::cout << ">> Finished!" << std::endl << std::endl;
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
        std::string(arg) == "-s" ||
        std::string(arg) == "--server" ||
        std::string(arg) == "-kf" ||
        std::string(arg) == "--keep-folders" ||
        std::string(arg) == "-ndc" ||
        std::string(arg) == "--no-dependency-checking" ||
        std::string(arg) == "--help" ||
        std::string(arg) == "-h" ||
        std::string(arg) == "help")
        return true;

    return false;
}

void help()
{
    std::cout << "Secundo Package Manager - v" << _VERSION << std::endl;

    std::cout << "\nOptions:" << std::endl;
    std::cout << "     install <user>:<package>        - installs a package from the choosed repository of a user"
              << std::endl;
    std::cout << "     update <user>:<package>         - updates a package from the choosed repository of a user" << std::endl;

    std::cout << "     update all                      - updates all installed packages (only works for packages,\n"
              << "                                       installed with version 0.1.4 or above)" << std::endl;

    std::cout << "     remove <user>:<package>         - removes a package from the choosed repository of a user" << std::endl;
    std::cout << "     local <path>                    - install directory with installer script (pkg/ins.sc)" << std::endl;
    std::cout << "     list                            - lists all installed packages." << std::endl;
    std::cout << "     clean                           - cleans packages that had errors at installing and were\n" 
              << "                                       not cleaned or just unnecessary files and directories." << std::endl;

    std::cout << "     trust <user>                    - you will not get questions (like *1 or *2) about projects"
              << std::endl;
    std::cout << "                                       from this user, only do it if you are really sure!" << std::endl;

    std::cout << "     untrust <user>                  - remove user from trusted users" << std::endl;
    std::cout << std::endl;

    std::cout << "     -ndc, --no-dependency-checking  - (NOT RECOMMENDED) ignore dependencies at removing packages" << std::endl;
    std::cout << "     -kf, --keep-folders             - keep cloned project-folders, clean with \"sudo secpm clean\"" << std::endl;
    std::cout << "     -s, --server                    - setting the git server (default is github.com)" << std::endl;

    std::cout << std::endl;
    std::cout << "     > sudo secpm quiet [...]        - there will be no output from the installer scripts" << std::endl;

    std::cout << std::endl;
    std::cout << " *1 - Are you really sure?" << std::endl;
    std::cout << " *2 - Do you want to see the build file?" << std::endl;

    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "     sudo secpm install user:project               - installs user's project" << std::endl;
    std::cout << "     sudo secpm remove user:project -ndc           - removes user's project, without checking if" << std:: endl;
    std::cout << "                                                     it's a dependency of other packages or not" << std::endl;
    std::cout << "     sudo secpm -s bitbucket.org ins user:project  - installs user's project from bitbucket.org" << std::endl;
    _quit(1);
}
