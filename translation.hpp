#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include "tstring.hpp"
#include <yaml-cpp/yaml.h>

namespace Secundo
{
    class Translation
    {
    public:
        YAML::Node sentences;

        Translation() {}

        std::string get(std::string s, bool nl = false, bool bnl = false)
        {
            if (sentences[s])
            {
                std::string str = std::string(sentences[s].as<std::string>());

                if (nl)
                    str = str + "\n";
                if (bnl)
                    str = "\n" + str;
                    
                if (tri::_a42)
                    str = tri::string("")._a1337(str);

                return str;
            }
            else
            {
                std::cout << ">> Fatal error in language file: Sentences \"" << s << "\" doesn't exists!" << std::endl;
                _quit(1);
            }
        }

        void loadConfig(std::string path)
        {
            if (std::ifstream(path).is_open())
            {
                sentences = YAML::LoadFile(path);
            }
            else
            {
                std::cout << ">> Error: language file " << path << " not found!" << std::endl;
                _quit(1);
            }
        }
    } Translation;
}

#endif