#ifndef LANG_HPP
#define LANG_HPP

#include <iostream>
#include <fstream>
#include "tstring.hpp"
#include "lang/functions.hpp"
#include "lang/tokenizer.hpp"
#include "lang/syntax.hpp"
#include "lang/executor.hpp"
#include "lang/runtime.hpp"
#include "lang/obj/dependency.hpp"

namespace Secundo
{
    class Seclang
    {
    private:
        std::string fileRead(std::string __file)
        {
            std::string code = "";
            std::string line = "";
            std::ifstream _file(__file);

            if (_file.is_open())
            {
                while (std::getline(_file, line))
                {
                    tri::string s = line;
                    s = s.trim();
                    code = code + s.cxs() + "\n";
                }
            }
            else
            {
                std::cout << "ERROR: FATAL_ERROR: INSTALL-FILE (" << __file << ") NOT FOUND!" << std::endl;
                _quit(1);
            }

            return code;
        }

    public:
        Package createPackage(const std::string &script)
        {
            return Executor.execute(Tokenizer.tokenize(fileRead(script)));
        }

        void run(Package p, const std::string &main_function)
        {
            Secundo::Runtime.MainFunction = main_function;
            bool found = false;

            if (Runtime.MainFunction != "remove" || Runtime.MainFunction != "remove_win")
            {
                for (Dependency d : p.dependencies.dependencies)
                {
                    DIR *dir;
                    struct dirent *ent;

                    found = false;
                    Package pack;

                    if ((dir = opendir(Secundo::Runtime.PackageFileDirectory.c_str())) != NULL)
                    {
                        while ((ent = readdir(dir)) != NULL)
                        {
                            tri::string s = ent->d_name;

                            if (s.at(0) == '.')
                                continue;

                            if (s.cxs().substr(s.length()-3, s.length()) == ".sc")
                                continue;

                            pack = createPackage(s.cxs());

                            if (d.name == pack.name &&
                                d.user == pack.user &&
                                d.version == pack.version)
                                found = true;
                        }

                        closedir(dir);
                    }
                    else
                    {
                        std::cout << ">> There was an error! Directory for the package-files (/usr/share/secundo/pkg_files) not found!" << std::endl;
                        _quit(1);
                    }

                    if (!found)
                    {
                        std::cout << ">> Added dependency to install list: " << d.user << ":" << d.name << std::endl;

                        Package p = Package(d.user, d.name);
                        p.version = d.version;

                        Secundo::Global.addInstallingPackage(p);
                    }
                }
            }

            p.functions.runFunction(Runtime.MainFunction);

            for (int i = 0; i < Runtime.DeletingFiles.size(); i++)
            {
                remove(Runtime.DeletingFiles[i].c_str());
            }
        }
    } Seclang;
}
#endif
