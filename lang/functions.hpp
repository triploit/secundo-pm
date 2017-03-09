#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include "obj/function.hpp"
#include "runtime.hpp"
#include "../tstring.hpp"

namespace Secundo
{
    class Functions
    {
    private:
        std::vector<Function> functions;

    public:
        void addFunction(Function f)
        {
            // std::cout << "ADD FUNCTION!!! " << f.getName() << std::endl;
            functions.push_back(f);
        }

        bool existsFunction(std::string func)
        {
            for (int i = 0; i < functions.size(); i++)
            {
                if (functions[i].getName() == func)
                {
                    return true;
                }
            }
            return false;
        }

        void runFunction(std::string func)
        {
            if (!existsFunction(func))
            {
                std::cout << "ERROR: FATAL_ERROR: Function " << func << " not found!" << std::endl;
                exit(1);
            }

            std::vector<std::string> v = getFunction(func).getCode();

            for (int i = 0; i < v.size(); i++)
            {
                tri::string tmp = v[i];
                tmp = tmp.trim();

                std::string f = tmp.cxs().substr(1, tmp.length()-1);

                if (tmp.at(0) != '&')
                    system(v[i].c_str());
                else runFunction(f);
            }
        }

        Function getFunction(std::string func)
        {
            if (!existsFunction(func))
            {
                std::cout << "ERROR: LINE " << Secundo::Runtime.LineNumber << ": FATAL_ERROR: Function " << func << " not found!" << std::endl;
                exit(1);
            }

            for (int i = 0; i < functions.size(); i++)
            {
                if (functions[i].getName() == func)
                {
                    return functions[i];
                }
            }

            return Function("[<NULL>]");
        }
    } Functions;
}

#endif
