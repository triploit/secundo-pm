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

namespace Secundo
{
    class Seclang
    {
    private:
        void fileRead(std::string __file)
        {
            Runtime.M_Code = "";
            std::ifstream _file(__file);

            if (_file.is_open())
            {
                while (std::getline(_file, Runtime.M_Line))
                {
                    tri::string s = Runtime.M_Line;
                    s = s.trim();
                    Runtime.M_Code = Runtime.M_Code + s.cxs() + "\n";
                }
            }
            else
            {
                std::cout << "ERROR: FATAL_ERROR: INSTALL-FILE (" << __file << ") NOT FOUND!" << std::endl;
                exit(1);
            }
        }

    public:
        void run(const std::string &script, const std::string &main_function)
        {
            Functions.clearFunctions();
            Secundo::Runtime.MainFunction = main_function;
            fileRead(script);
            bool found = false;

            Executor.execute(Secundo::Tokenizer.tokenize(Runtime.M_Code));

            if (Runtime.MainFunction != "remove" || Runtime.MainFunction != "remove_win")
            {
                for (std::string dep : Runtime.Dependencies)
                {
                    std::string user = tri::string(dep).split(':')[0].cxs();
                    std::string pkgn = tri::string(dep).split(':')[1].cxs();

                    DIR *dir;
                    struct dirent *ent;

                    if ((dir = opendir(Secundo::Runtime.PackageFileDirectory.c_str())) != NULL)
                    {
                        while ((ent = readdir(dir)) != NULL)
                        {
                            tri::string s = ent->d_name;

                            if (s.at(0) == '.')
                                continue;

                            if ((user+"_"+pkgn+".sc") == s.cxs())
                            {
                                found = true;
                            }
                        }

                        closedir(dir);
                    }
                    else
                    {
                        std::cout << ">> There was an error! Directory for the package-files (/usr/share/secundo/pkg_files) not found!" << std::endl;
                        exit(1);
                    }

                    if (!found)
                    {
                        std::cout << ">>>>>>>>>>>>>>>>> Installing dependency: " << user << ":" << pkgn << std::endl;
                        Secundo::Global.addInstallingPackage(Package(user, pkgn));
                    }                    
                }
            }

            Functions.runFunction(Runtime.MainFunction);

            for (int i = 0; i < Runtime.DeletingFiles.size(); i++)
            {
                remove(Runtime.DeletingFiles[i].c_str());
            }

            Functions.clearFunctions();
        }
    } Seclang;
}
#endif
