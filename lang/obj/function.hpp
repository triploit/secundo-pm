#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <vector>

namespace Secundo
{
    class Function
    {
    private:
        std::vector<std::string> code;
        std::string name;
    public:
        void addCodeLine(std::string line)
        {
            code.push_back(line);
        }

        std::string getName()
        {
            return name;
        }

        void setCode(std::vector<std::string> _c)
        {
            code = _c;
        }

        std::vector<std::string> getCode()
        {
            return code;
        }

        Function(std::string _name)
        {
            name = _name;
        }
    };
}

#endif
