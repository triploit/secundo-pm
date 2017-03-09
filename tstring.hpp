#ifndef TRIPLOIT_LIB_STRING
#define TRIPLOIT_LIB_STRING

#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <stdio.h>

namespace tri
{
    class string
    {
    private:
        std::string str;

        static inline std::string &ltrim(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }

        static inline std::string &rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }

        std::string trimf()
        {
            return ltrim(rtrim(str));
        }

        template<typename Out>
        void splitf(const std::string &s, char delim, Out result)
        {
            std::stringstream ss;
            ss.str(s);
            std::string item;

            while (std::getline(ss, item, delim))
            {
                *(result++) = item;
            }
        }


        std::vector<std::string> splitf(char delim)
        {
            std::vector<std::string> elems;
            splitf(str, delim, std::back_inserter(elems));
            return elems;
        }

        bool replace(std::string& str, const std::string& from, const std::string& to)
        {
            size_t start_pos = str.find(from);
            if(start_pos == std::string::npos)
                return false;

            str.replace(start_pos, from.length(), to);
            return true;
        }

    public:
        string(std::string r):str(r) {}
        string() {str="";}
        string(const char c):str(&c) {}
        //string(const tri::string c):str(c.cxs()) {}
        string(const char* r):str(r) {}

        bool find(string s)
        {
            if (str.find(s.cxs()))
                return true;
            else
                return false;
        }

        bool equals(string s)
        {
            string s1 = str;
            if (s1.cxs().compare(s.cxs()))
                return true;
            else
                return false;
        }

        bool equalsIgnoreCase(string s)
        {
            string s1 = str;
            s = s.toLower();
            s1 = s1.toLower();

            std::string x, y;
            x = s1.cxs();
            y = s.cxs();

            if (s1.cxs().compare(s.cxs()) || x == y)
                return true;
            else
                return false;
        }


        std::string cxs()
        {
            return str;
        }

        const char* cs()
        {
            return str.c_str();
        }

        string trim()
        {
            return string(trimf());
        }

        void reverse()
        {
            std::reverse(str.begin(), str.end());
        }

        std::vector<string> split(char delim)
        {
            std::vector<string> tstrs;
            std::vector<std::string> strs = splitf(delim);

            for (int i = 0; i < strs.size(); i++)
            {
                tstrs.push_back(string(strs[i]));
            }

            return tstrs;
        }

        std::vector<string> split()
        {
            std::vector<string> tstrs;
            std::vector<std::string> strs = splitf(' ');

            for (int i = 0; i < strs.size(); i++)
            {
                tstrs.push_back(string(strs[i]));
            }

            return tstrs;
        }

        char at(int index)
        {
            return str[index];
        }

        const int length()
        {
            return str.size();
        }

        tri::string operator+(tri::string s)
        {
            return tri::string(str += s.str);
        }

        tri::string operator=(tri::string s)
        {
            return tri::string(str = s.str);
        }

        tri::string operator=(std::string s)
        {
            return tri::string(str = s);
        }

        tri::string operator=(const char* s)
        {
            return tri::string(str = s);
        }

        string toUpper()
        {
            std::string s = str;
            std::string tmp = "";

            for (int i = 0; i < s.size(); i++)
            {
                tmp = tmp + (char) std::toupper(s[i]);
            }

            return string(tmp);
        }

        string toLower()
        {
            std::string s = str;
            std::string tmp = "";

            for (int i = 0; i < s.size(); i++)
            {
                tmp = tmp + (char) std::tolower(s[i]);
            }

            return string(tmp);
        }

        tri::string replace(string from, string to)
        {
            std::string s = str;
            replace(s, from.cxs(), to.cxs());
            return tri::string(s);
        }

        tri::string replaceAll(string from, string to)
        {
            for (int i = 0; i < str.size(); i++)
                replace(str, from.cxs(), to.cxs());
            return tri::string(str);
        }

        std::vector<char> toCharArray()
        {
            return (std::vector<char>(str.begin(), str.end()));
        }

        bool endsWith(tri::string s)
        {
            if (string(str.substr(str.size(), str.size()-s.length())).cxs() == s.cxs())
                return true;

            return false;
        }

        bool startsWith(tri::string s)
        {
            // std::cout << "TRI::" << string(str.substr(0, s.length())).cxs() << std::endl;

            if (string(str.substr(0, s.length())).cxs() == s.cxs())
                return true;

            return false;
        }

    };
}

#endif
