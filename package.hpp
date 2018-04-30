#ifndef __PACKAGE_HPP
#define __PACKAGE_HPP

class Package
{
public:
    std::string user{};
    std::string name{};

    Package(std::string p_user, std::string p_package) : user(p_user), name(p_package)
    {
    }

    Package() = default;

};

#endif
