#include <iostream>
#include "global.hpp"
#include "installer.hpp"

void help();

int main(int argc, char* argv[])
{
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
                    std::string(argv[i+1]) != "us")
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
                    std::string(argv[i+1]) != "us")
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
                    std::string(argv[i+1]) != "us")
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
        else if (arg == "user" || arg == "us")
        {
            if ((i+1) < argc)
                Secundo::Global.setUser(std::string(argv[i+1]));
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
    std::cout << "Secundo Package Manager - v001" << std::endl;
    std::cout << "\nOptions:" << std::endl;
    std::cout << "\t install <package>      - installs a package from the choosed repository" << std::endl;
    std::cout << "\t update <package>       - updates a package from the choosed repository" << std::endl;
    std::cout << "\t remove <package>       - removes a package from the choosed repository" << std::endl;
    std::cout << "\t user <github-username> - change the current repository" << std::endl;
    exit(1);
}
