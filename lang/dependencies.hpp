#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP

#include <vector>
#include "obj/dependency.hpp"

namespace Secundo
{
    class Dependencies
    {
    public:
        std::vector<Dependency> dependencies;

        void addDependency(Dependency d)
        {
            dependencies.push_back(d);
        }

        void clearDependencies()
        {
            dependencies.clear();
        }

        bool containsDependency(Dependency d)
        {
            for (Dependency dep : dependencies)
            {
                if (dep.user == d.user && 
                    dep.name == d.name && 
                    dep.version == d.version)
                {
                    return true;
                }
            }

            return false;
        }
    };
}

#endif