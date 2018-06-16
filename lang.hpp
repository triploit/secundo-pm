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
                printf(Secundo::Translation.get("40").c_str(), __file.c_str());
                _quit(1);
            }

            return code;
        }

    public:
        Package createPackage(const std::string &script)
        {
            return Executor.execute(Tokenizer.tokenize(fileRead(script)));
        }

        Package createPackageFromLink(const Package &p)
        {
            std::string o_f = "/usr/share/secundo/tmp_ins.sc";
            // https://raw.githubusercontent.com/user/name/master/pkg/ins.sc

            if (!Runtime.wgetLinkisNice("https://raw.githubusercontent.com/"+p.user+"/"+p.name+"/master/pkg/ins.sc"))
            {
                printf(std::string(">> "+Secundo::Translation.get("25")).c_str(), p.user.c_str(), p.name.c_str());
                _quit(1);
            }

            std::string command = "wget -q https://raw.githubusercontent.com/"+p.user+"/"+p.name+"/master/pkg/ins.sc -O "+o_f;
            Package package;

            if (system(std::string(command + Secundo::Runtime.quiet).c_str()) != 0)
            {
                printf(std::string(">> "+Secundo::Translation.get("31")).c_str(), command.c_str());
                _quit(1);
            }
            else
            {
                package = createPackage(o_f);
                system(std::string("rm "+o_f).c_str());
            }

            return package;
        }

        void run(Package p, const std::string &main_function)
        {
            Secundo::Runtime.MainFunction = main_function;
            bool found = false;

            if (main_function != "remove" && main_function != "remove_win")
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
                        std::cout << ">> " << Secundo::Translation.get("41") << std::endl;
                        _quit(1);
                    }

                    if (!found)
                    {

                        Package p = Package(d.user, d.name);
                        p.version = d.version;

                        found = false;

                        for (Package pkg : Secundo::Global.getInstallingPackages())
                        {
                            // std::cout << pkg.name << " " << pkg.user << " " << pkg.version << std::endl;
                            // std::cout << p.name << " " << p.user << " " << p.version << std::endl;

                            if (pkg.name == p.name &&
                                pkg.user == p.user)
                                found = true;
                        }

                        if (!found)
                        {
                            Secundo::Global.addInstallingPackage(p);
                            printf(std::string(">> "+Secundo::Translation.get("42", true)).c_str(),
                                d.user.c_str(),
                                d.name.c_str(),
                                d.version.str.c_str());
                        }
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
