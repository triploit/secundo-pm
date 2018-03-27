#ifndef __PACKAGE_HPP
#define __PACKAGE_HPP

class Package
{
public:
	std::string user;
	std::string name;

	Package(std::string user, std::string package)
	{
		this->user = user;
		this->name = package;
	}
};

#endif
