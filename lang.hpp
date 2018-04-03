#ifndef LANG_HPP
#define LANG_HPP

#include <iostream>
#include <fstream>
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
                std::cout << "ERROR: FATAL_ERROR: INSTALL-FILE(" << __file << ") NOT FOUND!" << std::endl;
                exit(1);
            }
        }

    public:
        void run(const std::string& script, const std::string& main_function)
        {
			Functions.clearFunctions();
            Secundo::Runtime.MainFunction = main_function;
            fileRead(script);

            Executor.execute(Secundo::Tokenizer.tokenize(Runtime.M_Code));
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
