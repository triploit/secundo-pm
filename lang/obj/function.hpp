#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <vector>

namespace Secundo {
    class Function {
    private:
        std::vector<std::string> code;
        std::string name;
    public:
        void addCodeLine(const std::string &line) {
            code.push_back(line);
        }

        std::string getName() {
            return name;
        }

        void setCode(const std::vector<std::string> &_c) {
            code = _c;
        }

        std::vector<std::string> getCode() {
            return code;
        }

        Function(const std::string &_name) {
            name = _name;
        }
    };
}

#endif
