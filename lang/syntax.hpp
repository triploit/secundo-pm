#ifndef SYNTAX_CHECK_HPP
#define SYNTAX_CHECK_HPP

#include <vector>
#include <iostream>
#include <regex>
#include "../tstring.hpp"

#include "runtime.hpp"

namespace Secundo
{
    class SyntaxCheck
    {
    private:
        std::vector<std::vector<std::regex>> COMMANDS =
            {
                { // nothing
                    std::regex("")
                },
                {
                    std::regex("[ \t]*func[ \t]*[a-zA-Z_]*[a-zA-Z0-9]*[\n\t ]*\\{[a-z A-Z\\w\\W]*\\}")
                }
            };

        std::vector<std::string> COMMAND_NAME =
            {
                "NOTHING",
                "FUNCTION"
            };

    public:
        int isValidLine(tri::string command)
        {
            int nice = 0;
            std::smatch matches;
            std::string cmd = command.cxs();

            for (int i = 0; i < COMMANDS.size(); i++)
            {
                if (std::regex_match(cmd, matches, COMMANDS[i][0]))
                {
                    nice++;

                    for (int j = 1; j < COMMANDS[i].size(); j++)
                    {
                        if (std::regex_match(cmd, matches, COMMANDS[i][j]))
                        {
                            Secundo::Runtime.CommandType = COMMAND_NAME[i];
                            nice++;
                            return 0;
                        }
                    }

                    if (COMMANDS[i].size() == 1)
                    {
                        if (std::regex_match(cmd, matches, COMMANDS[i][0]))
                        {
                            Secundo::Runtime.CommandType = COMMAND_NAME[i];
                            nice++;
                            return 0;
                        }
                    }

                    return 1;
                }
                else
                {
                    // std::cout << "\"" << cmd << "\" != \"" << matches.str() << "\"" << std::endl;
                }
            }

            return 2;
        }
    } SyntaxCheck;
}

#endif
