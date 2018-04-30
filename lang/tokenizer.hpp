#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <iostream>
#include <regex>
#include "../tstring.hpp"

#include "runtime.hpp"

namespace Secundo {
    class Tokenizer {
    private:
        std::vector<Token> Tokens;

    public:
        std::vector<Token> tokenize(std::string code) {
            code = tri::string(code).trim().cxs();
            Tokens.clear();

            bool str = false;
            bool scope = false;
            std::string tmp;
            std::string type = "oth";

            for (int i = 0; i < code.size(); i++) {
                // std::cout << ">> " << code[i] << std::endl;
                if (code[i] == '\"' && !scope) {
                    if (str) {
                        str = false;

                        if (tmp != "")
                            Tokens.push_back(Token(tmp, type));

                        tmp = "";
                        type = "oth";
                    } else {
                        type = TokenType.TYPE_STRING;
                        str = true;
                    }
                } else if (code[i] == '{' && !str) {
                    // std::cout << "FUNCTIONBEGIN" << std::endl;
                    type = TokenType.TYPE_SCOPE;
                    scope = true;
                    continue;
                } else if (code[i] == '}') {
                    // std::cout << "FUNCTIONEND" << std::endl;
                    scope = false;

                    if (tmp != "")
                        Tokens.push_back(Token(tmp, type));

                    tmp = "";
                    type = "oth";
                    continue;
                }

                if (!str && !scope) {
                    if (code[i] == ' ' || code[i] == '\n') {
                        for (int j = i; j < code.size(); j++) {
                            if (code[(j + 1)] == ' ' || code[(j + 1)] == '\n')
                                i = j + 1;
                            else
                                break;
                        }

                        if (tmp != "")
                            Tokens.push_back(Token(tmp, type));

                        tmp = "";
                        type = "oth";
                        continue;
                    }

                    tmp += code[i];
                } else {
                    tmp += code[i];
                }
            }
            if (tmp != "")
                Tokens.push_back(Token(tmp, type));

            // std::cout << std::endl << std::endl;

            /*for (int i = 0; i < Tokens.size(); i++)
            {
                std::cout << "TOKEN["<<i<<"]\n\tVALUE: \"" << Tokens[i].getValue() << "\"\n\tTYPE: \"" << Tokens[i].getType() << "\"" << std::endl;
            }*/

            return Tokens;
        }

        std::vector<std::string> scopeTokenizingToString(std::string code) {
            std::vector<std::string> toks;
            tri::string t = code;
            t = t.trim();
            code = t.cxs();

            bool str = false;
            bool scope = false;
            std::string tmp;

            for (int i = 0; i < code.size(); i++) {
                if (code[i] == '<' && code[i + 1] == '[' && !str) {
                    i++;
                    // std::cout << "FUNCTIONBEGIN" << std::endl;
                    scope = true;
                    continue;
                } else if (code[i] == ']' && code[i + 1] == '>' && !str) {
                    i++;
                    // std::cout << "FUNCTIONEND" << std::endl;
                    scope = false;

                    if (tmp != "")
                        toks.push_back("~" + tmp);

                    tmp = "";
                    continue;
                }

                if (!str && !scope) {
                    if (code[i] == '\n') {
                        for (int j = i; j < code.size(); j++) {
                            if (code[(j + 1)] == '\n')
                                i = j + 1;
                            else
                                break;
                        }

                        if (tmp != "")
                            toks.push_back(tmp);

                        tmp = "";
                        continue;
                    }

                    tmp += code[i];
                } else {
                    tmp += code[i];
                }
            }

            if (tmp != "")
                toks.push_back(tmp);

            // std::cout << std::endl << std::endl;

            /*for (int i = 0; i < Tokens.size(); i++)
            {
                std::cout << "TOKEN["<<i<<"]\n\tVALUE: \"" << Tokens[i].getValue() << "\"\n\tTYPE: \"" << Tokens[i].getType() << "\"" << std::endl;
            }*/

            return toks;
        }
    } Tokenizer;
}

#endif
