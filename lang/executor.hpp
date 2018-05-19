#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <iostream>
#include <vector>
#include "obj/token.hpp"
#include "obj/function.hpp"
#include "functions.hpp"
#include "tokenizer.hpp"

namespace Secundo
{
    class Executor
    {
    private:
        std::vector<Token> Tokens;
        std::vector<Token> RealTokens;

        Package putTogether()
        {
            Functions fs;
            Version v;
            Dependencies dp;

            std::string name;
            std::string user;

            for (int i = 0; i < Tokens.size(); i++)
            {
                std::string value = Tokens[i].getValue();
                std::string type = Tokens[i].getType();

                if (value == "func" && (i + 2) < Tokens.size())
                {
                    if (Tokens[i + 1].getType() == TokenType.TYPE_OTHER &&
                        Tokens[i + 2].getType() == TokenType.TYPE_SCOPE)
                        RealTokens.push_back(
                                Token(Tokens[i + 1].getValue(), TokenType.TYPE_FUNCTION, Tokens[i + 2].getValue()));
                    else
                    {
                        std::cout << "EXECUTOR: PUT_TOGETHER: FUNC " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        _quit(1);
                    }
                    i += 2;
                }
                else if (value == "dep" && (i+3) < Tokens.size())
                {
                    if (Tokens[i + 1].getType() == TokenType.TYPE_OTHER &&
                        Tokens[i + 2].getType() == TokenType.TYPE_OTHER &&
                        Tokens[i + 3].getType() == TokenType.TYPE_OTHER)
                    {
                        Dependency d;
                        
                        d.user = Tokens[i+1].getValue();
                        d.name = Tokens[i+2].getValue();
                        d.version = Version(Tokens[i+3].getValue());

                        dp.addDependency(d);
                    }
                    else
                    {
                        std::cout << "EXECUTOR: PUT_TOGETHER: DEPENDENCY " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        _quit(1);
                    }

                    i += 3;
                }
                else if (value == "name" && (i+1) < Tokens.size())
                {
                    if (Tokens[i+1].getType() == TokenType.TYPE_OTHER)
                    {
                        name = Tokens[i+1].getValue();
                        i++;
                    }
                    else
                    {
                        std::cout << "EXECUTOR: PUT_TOGETHER: NAME " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        _quit(1);
                    }
                }
                else if (value == "user" && (i+1) < Tokens.size())
                {
                    if (Tokens[i+1].getType() == TokenType.TYPE_OTHER)
                    {
                        user = Tokens[i+1].getValue();
                        i++;
                    }
                    else
                    {
                        std::cout << "EXECUTOR: PUT_TOGETHER: USER " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        _quit(1);
                    }
                }
                else if (value == "ver" && (i+1) < Tokens.size())
                {
                    if (Tokens[i+1].getType() == TokenType.TYPE_OTHER)
                    {               
                        v = Version(Tokens[i+1].getValue());
                        i++;
                    }
                    else
                    {
                        std::cout << "EXECUTOR: PUT_TOGETHER: VERSION " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        _quit(1);
                    }
                }
                else
                {
                    std::cout << "EXECUTOR: PUT_TOGETHER: ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                    _quit(1);
                }
            }

            for (int i = 0; i < RealTokens.size(); i++)
            {
                if (RealTokens[i].getType() == TokenType.TYPE_FUNCTION)
                {
                    Function f(RealTokens[i].getValue());
                    f.setCode(Tokenizer.scopeTokenizingToString(RealTokens[i].getUValue()));

                    fs.addFunction(f);
                }
            }

            Package p;
            p.version = v;
            p.functions = fs;

            p.name = name;
            p.user = user;
            
            p.dependencies = dp;
            return p;
        }

    public:

        Package execute(const std::vector<Token> &v)
        {
            Tokens.clear();
            RealTokens.clear();

            Tokens = v;
            return putTogether();
        }
    } Executor;
}

#endif
