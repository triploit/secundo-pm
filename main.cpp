#include <iostream>
#include "global.hpp"
#include "installer.hpp"
#include "lang/runtime.hpp"

void help();
std::string _VERSION = "0.1.1";

int main(int argc, char* argv[])
{
    Secundo::Runtime.initLV();

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "install" || arg == "ins")
        {
            if ((i+1) < argc)
            {
                if (std::string(argv[i+1]) != "ins" &&
                    std::string(argv[i+1]) != "install" &&
                    std::string(argv[i+1]) != "remove" &&
                    std::string(argv[i+1]) != "rem" &&
                    std::string(argv[i+1]) != "update" &&
                    std::string(argv[i+1]) != "up" &&
                    std::string(argv[i+1]) != "user" &&
                    std::string(argv[i+1]) != "us" &&
                    std::string(argv[i+1]) != "local")
                {
                    Secundo::Global.addInstallingPackage(std::string(argv[i+1]));
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
		else if (arg == "version" || arg == "-v" || arg == "--version" || arg == "ver")
        {
            std::cout << _VERSION << std::endl;
        }
        else if (arg == "remove" || arg == "rem")
        {
            if ((i+1) < argc)
            {
                if (std::string(argv[i+1]) != "ins" &&
                    std::string(argv[i+1]) != "install" &&
                    std::string(argv[i+1]) != "remove" &&
                    std::string(argv[i+1]) != "rem" &&
                    std::string(argv[i+1]) != "update" &&
                    std::string(argv[i+1]) != "up" &&
                    std::string(argv[i+1]) != "user" &&
                    std::string(argv[i+1]) != "us" &&
                    std::string(argv[i+1]) != "local")
                {
                    Secundo::Global.addRemovingPackage(std::string(argv[i+1]));
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
            if ((i+1) < argc)
            {
                if (std::string(argv[i+1]) != "ins" &&
                    std::string(argv[i+1]) != "install" &&
                    std::string(argv[i+1]) != "remove" &&
                    std::string(argv[i+1]) != "rem" &&
                    std::string(argv[i+1]) != "update" &&
                    std::string(argv[i+1]) != "up" &&
                    std::string(argv[i+1]) != "user" &&
                    std::string(argv[i+1]) != "us" &&
                    std::string(argv[i+1]) != "local")
                {
                    Secundo::Global.addUpdatingPackage(std::string(argv[i+1]));
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
        else if (arg == "local")
        {
            if ((i+1) < argc)
            {
                if (std::string(argv[i+1]) != "ins" &&
                    std::string(argv[i+1]) != "install" &&
                    std::string(argv[i+1]) != "remove" &&
                    std::string(argv[i+1]) != "rem" &&
                    std::string(argv[i+1]) != "update" &&
                    std::string(argv[i+1]) != "up" &&
                    std::string(argv[i+1]) != "user" &&
                    std::string(argv[i+1]) != "us" &&
                    std::string(argv[i+1]) != "local")
                {
                    Secundo::Global.addInstallLocalPackage(std::string(argv[i+1]));
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
        else if (arg == "user" || arg == "us")
        {
            if ((i+1) < argc)
            {
				Secundo::Global.setUser(std::string(argv[i+1]));
				i++;
			}
            else
            {
                std::cout << "Syntax error!\n" << std::endl;
                help();
            }
        }
        else
        {
            std::cout << "Option \"" << arg << "\" not found!" << std::endl;
            help();
        }
    }

    Secundo::Installer.init();

    for (int i = 0; i < Secundo::Global.getInstallLocalPackages().size(); i++)
    {
        std::cout << ">> Installing Local Directory " << Secundo::Global.getInstallLocalPackages()[i] << "..." << std::endl;
        Secundo::Installer.install_local(Secundo::Global.getInstallLocalPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

    for (int i = 0; i < Secundo::Global.getInstallingPackages().size(); i++)
    {
        std::cout << ">> Installing " << Secundo::Global.getInstallingPackages()[i] << "..." << std::endl;
        Secundo::Installer.install(Secundo::Global.getInstallingPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

    for (int i = 0; i < Secundo::Global.getRemovingPackages().size(); i++)
    {
        std::cout << ">> Updating " << Secundo::Global.getRemovingPackages()[i] << "..." << std::endl;
        Secundo::Installer.remove(Secundo::Global.getRemovingPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

    for (int i = 0; i < Secundo::Global.getUpdatingPackages().size(); i++)
    {
        std::cout << ">> Updating " << Secundo::Global.getUpdatingPackages()[i] << "..." << std::endl;
        Secundo::Installer.update(Secundo::Global.getUpdatingPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

}

void help()
{
    std::cout << "Secundo Package Manager - v" << _VERSION << std::endl;
    std::cout << "\nOptions:" << std::endl;
    std::cout << "\t install <package>      - installs a package from the choosed repository" << std::endl;
    std::cout << "\t update <package>       - updates a package from the choosed repository" << std::endl;
    std::cout << "\t remove <package>       - removes a package from the choosed repository" << std::endl;
    std::cout << "\t user <github-username> - change the current repository" << std::endl;
    std::cout << "\t local <path>           - install directory with installer script (pkg/ins.sc)" << std::endl;
    exit(1);
}
