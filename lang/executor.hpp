#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <iostream>
#include <vector>
#include "obj/token.hpp"
#include "obj/function.hpp"
#include "functions.hpp"
#include "tokenizer.hpp"

namespace Secundo {
    class Executor {
    private:
        std::vector<Token> Tokens;
        std::vector<Token> RealTokens;

        void putTogether() {
            for (int i = 0; i < Tokens.size(); i++) {
                std::string value = Tokens[i].getValue();
                std::string type = Tokens[i].getType();

                if (value == "func" && (i + 2) < Tokens.size()) {
                    if (Tokens[i + 1].getType() == TokenType.TYPE_OTHER &&
                        Tokens[i + 2].getType() == TokenType.TYPE_SCOPE)
                        RealTokens.push_back(
                                Token(Tokens[i + 1].getValue(), TokenType.TYPE_FUNCTION, Tokens[i + 2].getValue()));
                    else {
                        std::cout << "EXECUTOR: PUT_TOGETHER: FUNC " << Tokens[i + 1].getValue()
                                  << ": ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                        exit(1);
                    }
                    i += 2;
                } else {
                    std::cout << "EXECUTOR: PUT_TOGETHER: ERROR: FATAL_ERROR: Syntax error!" << std::endl;
                    exit(1);
                }
            }

            for (int i = 0; i < RealTokens.size(); i++) {
                if (RealTokens[i].getType() == TokenType.TYPE_FUNCTION) {
                    Function f(RealTokens[i].getValue());
                    f.setCode(Tokenizer.scopeTokenizingToString(RealTokens[i].getUValue()));

                    Functions.addFunction(f);
                }
            }
        }

    public:

        void execute(const std::vector<Token> &v) {
            Tokens.clear();
            RealTokens.clear();

            Tokens = v;
            putTogether();
        }
    } Executor;
}

#endif
