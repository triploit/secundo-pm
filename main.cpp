#include <iostream>
#include "global.hpp"
#include "installer.hpp"
#include "lang/runtime.hpp"

void help();
bool is_argument(const std::string& arg);
std::string _VERSION = "0.1.2";

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
                if (!is_argument(argv[i+1]))
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
                if (!is_argument(argv[i+1]))
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
                if (!is_argument(argv[i+1]))
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
        else if (arg == "trust")
        {
            if ((i+1) < argc)
            {
                if (!is_argument(argv[i+1]))
                {
                    Secundo::Runtime.addTrusters(argv[i+1]);
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
            if ((i+1) < argc)
            {
                if (!is_argument(argv[i+1]))
                {
                    Secundo::Runtime.removeTrusters(argv[i+1]);
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
        else if (arg == "showtrust")
        {
			std::cout << "Trusting:" << std::endl;

			for (std::string s : Secundo::Runtime.trusted)
			{
				std::cout << "  - " << s << std::endl;
			}
        }
        else if (arg == "local")
        {
            if ((i+1) < argc)
            {
                if (!is_argument(argv[i+1]))
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

	Secundo::Runtime.saveTrusters();
}

bool is_argument(const std::string& arg)
{
	if (std::string(arg) == "ins" &&
		std::string(arg) == "install" &&
		std::string(arg) == "remove" &&
		std::string(arg) == "rem" &&
		std::string(arg) == "update" &&
		std::string(arg) == "up" &&
		std::string(arg) == "user" &&
		std::string(arg) == "us" &&
		std::string(arg) == "local" &&
		std::string(arg) == "trust" &&
		std::string(arg) == "untrust" &&
		std::string(arg) == "showtrust")
		return true;
	return false;
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
	std::cout << "\t trust <user>           - you will not get questions (like *1 or *2) about projects" << std::endl;
	std::cout << "\t                          from this user, only do it if you are really sure!" << std::endl;
	std::cout << "\t untrust <user>         - remove user from trusted users" << std::endl;
	std::cout << std::endl;
	std::cout << "\t *1 Are you sure to install this package?" << std::endl;
	std::cout << "\t *2 Do you want to see the build file?" << std::endl;
    exit(1);
}
