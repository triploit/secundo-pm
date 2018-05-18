#ifndef __PACKAGE_HPP
#define __PACKAGE_HPP

#include "lang/obj/version.hpp"
#include "lang/functions.hpp"
#include "lang/dependencies.hpp"

class Package
{
public:
    std::string user{};
    std::string name{};
    Secundo::Version version;
    Secundo::Functions functions;
    Secundo::Dependencies dependencies;

    Package(std::string p_user, std::string p_package) : user(p_user), name(p_package) 
    {
        version = Secundo::Version("0.0.0.0");
    }

    Package()
    {   
        version = Secundo::Version("0.0.0.0");
    }
};

#endif
