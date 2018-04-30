#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <vector>
#include "function.hpp"
#include "../runtime.hpp"

namespace Secundo
{
    class Token
    {
    private:
        std::string type;
        std::string value;
        std::string uvalue;

    public:
        std::string TYPE_STRING = "str";
        std::string TYPE_INTEGER = "int";
        std::string TYPE_COMMAND = "cmd";
        std::string TYPE_SCOPE = "scp";
        std::string TYPE_OTHER = "oth";
        std::string TYPE_FUNCTION = "func";

        Token(const std::string &val, const std::string &typ, const std::string &v = "")
        {
            value = val;

            if (typ != TYPE_STRING &&
                typ != TYPE_INTEGER &&
                typ != TYPE_COMMAND &&
                typ != TYPE_SCOPE &&
                typ != TYPE_OTHER &&
                typ != TYPE_FUNCTION)
            {
                std::cout << "TOKEN: ERROR: FALSE_TYPE_ERROR: " << typ << std::endl;
                exit(1);
            }
            else
            {
                type = typ;
            }

            uvalue = v;
        }

        std::string getValue()
        {
            return value;
        }

        std::string getType()
        {
            return type;
        }

        void setUValue(const std::string &v)
        {
            uvalue = v;
        }

        std::string getUValue()
        {
            return uvalue;
        }

    } TokenType("", "str");
}

#endif
