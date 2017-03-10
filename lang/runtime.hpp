#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <vector>
#include "obj/token.hpp"

namespace Secundo
{
    class Runtime
    {
    public:
        int LineNumber = 1;
        int Index = 1;
        bool Main = false;
        bool Verbose = true;

        std::string Scope;
        std::string CommandType;
        std::string MainFunction = "install";
        std::string M_Line;
        std::string M_Code;

        std::vector<Token> Tokens;
        std::vector<std::string> DeletingFiles;
    } Runtime;
}

#endif
