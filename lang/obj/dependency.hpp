#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP

#include <iostream>
#include "version.hpp"

namespace Secundo
{
    class Dependency
    {
    public:
        std::string name;
        std::string user;
        std::string parent_name;
        std::string parent_user;
        Version version;

        Dependency() {}

        Dependency(std::string user, std::string name, Version v)
        {
            this->name = name;
            this->version = v;
            this->user = user;
        }
    };
}

#endif