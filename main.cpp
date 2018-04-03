#include <iostream>
#include "global.hpp"
#include "installer.hpp"
#include "lang/runtime.hpp"

void help();
bool is_argument(const std::string& arg);
std::string _VERSION = "0.1.4";

int main(int argc, char* argv[])
{
	Secundo::Installer.init();
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
					// Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

					tri::string user = "";
					tri::string regex = "[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}:[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}";
					tri::string package = "";

					if (Secundo::Runtime.regex_match(std::string(argv[i+1]), regex.cxs()))
					{
						user = tri::string(argv[i+1]).split(':')[0];
						package = tri::string(argv[i+1]).split(':')[1];

	                    Secundo::Global.addInstallingPackage(Package(user.cxs(), package.cxs()));
					}
					else
					{
						std::cout << "Wrong package name: " << argv[i+1] << std::endl;
						std::cout << "\nThis is a package name:  user:package" << std::endl;
						std::cout << "                         triploit:secpundo-pm" << std::endl;
						exit(1);
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
					// Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

					tri::string user = "";
					tri::string regex = "[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}:[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}";
					tri::string package = "";

					if (Secundo::Runtime.regex_match(std::string(argv[i+1]), regex.cxs()))
					{
						user = tri::string(argv[i+1]).split(':')[0];
						package = tri::string(argv[i+1]).split(':')[1];

	                    Secundo::Global.addRemovingPackage(Package(user.cxs(), package.cxs()));
					}
					else
					{
						std::cout << "Wrong package name: " << argv[i+1] << std::endl;
						std::cout << "This is a package name:  user:package" << std::endl;
						std::cout << "                         triploit:secpundo-pm" << std::endl;
						exit(1);
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
            if ((i+1) < argc)
            {
                if (!is_argument(argv[i+1]))
                {
					// Regex: ^[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}:[a-z\d](?:[a-z\d]|-(?=[a-z\d])){0,38}$

					tri::string user = "";
					tri::string regex = "[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}:[a-z\\d](?:[a-z\\d]|-(?=[a-z\\d])){0,38}";
					tri::string package = "";

					if (Secundo::Runtime.regex_match(std::string(argv[i+1]), regex.cxs()))
					{
						user = tri::string(argv[i+1]).split(':')[0];
						package = tri::string(argv[i+1]).split(':')[1];

	                    Secundo::Global.addUpdatingPackage(Package(user.cxs(), package.cxs()));
					}
					else if (std::string(argv[i+1]) == "all")
					{
						Secundo::Installer.update_all();
					}
					else
					{
						std::cout << "Wrong package name: " << argv[i+1] << std::endl;
						std::cout << "This is a package name:  user:package" << std::endl;
						std::cout << "                         triploit:secpundo-pm" << std::endl;
						exit(1);
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
        std::cout << ">> Installing " << Secundo::Global.getInstallingPackages()[i].user << "'s " << Secundo::Global.getInstallingPackages()[i].name << "..." << std::endl;
        Secundo::Installer.install(Secundo::Global.getInstallingPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

    for (int i = 0; i < Secundo::Global.getRemovingPackages().size(); i++)
    {
        std::cout << ">> Remove " << Secundo::Global.getRemovingPackages()[i].user << "'s " << Secundo::Global.getRemovingPackages()[i].name << "..." << std::endl;
        Secundo::Installer.remove(Secundo::Global.getRemovingPackages()[i]);
        std::cout << ">> Finished!" << std::endl;
    }

    for (int i = 0; i < Secundo::Global.getUpdatingPackages().size(); i++)
    {
        std::cout << ">> Updating " << Secundo::Global.getUpdatingPackages()[i].user << "'s " << Secundo::Global.getUpdatingPackages()[i].name << "..." << std::endl;
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
    std::cout << "\t install <user>:<package> - installs a package from the choosed repository of a user" << std::endl;
    std::cout << "\t update <user>:<package>  - updates a package from the choosed repository of a user" << std::endl;

    std::cout << "\t update all               - updates all installed packages (only works for packages,\n" <<
			  << "\t                            installed with version 0.1.4 or above)" << std::endl;

    std::cout << "\t remove <user>:<package>  - removes a package from the choosed repository of a user" << std::endl;
    std::cout << "\t local <path>             - install directory with installer script (pkg/ins.sc)" << std::endl;
	std::cout << "\t trust <user>             - you will not get questions (like *1 or *2) about projects" << std::endl;
	std::cout << "\t                            from this user, only do it if you are really sure!" << std::endl;
	std::cout << "\t untrust <user>           - remove user from trusted users" << std::endl;
	std::cout << std::endl;
	std::cout << "\t *1 Are you really?" << std::endl;
	std::cout << "\t *2 Do you want to see the build file?" << std::endl;
    exit(1);
}
