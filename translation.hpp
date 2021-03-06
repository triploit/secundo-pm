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
        YAML::Node fallback;

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
                if (!fallback[s])
                {
                    std::cout << ">> Fatal error in SecPM: Sentences \"" << s << "\" doesn't even in fallback exist!" << std::endl;
                    _quit(1);
                }
                else
                {
                    std::string str = std::string(fallback[s].as<std::string>());

                    if (nl)
                        str = str + "\n";
                    if (bnl)
                        str = "\n" + str;
                        
                    if (tri::_a42)
                        str = tri::string("")._a1337(str);

                    return ("[?] "+str);
                }
            }
        }

        void loadConfig(std::string path)
        {
            fallback = YAML::Load(R"V0G0N(
1: |
  Secundo Package Manager - v%s 

  Options: 
      install <user>:<package>        - installs a package from the choosed repository of a user
      update <user>:<package>         - updates a package from the choosed repository of a user 
      update all                      - updates all installed packages (only works for packages,
                                        installed with version 0.1.4 or above) 

      remove <user>:<package>         - removes a package from the choosed repository of a user 
      local <path>                    - install directory with installer script (pkg/ins.sc) 
      list                            - lists all installed packages. 

      clean                           - cleans packages that had errors at installing and were
                                        not cleaned or just unnecessary files and directories. 
      config                          - edit the configuration file (by default with vi, you can
                                        change the editor in /usr/share/secundo/conf/config.yml)
      lang                            - add a language file
                                        
      trust <user>                    - you will not get questions (like *1 or *2) about projects
                                        from this user, only do it if you are really sure! 

      untrust <user>                  - remove user from trusted users 

      -ndc, --no-dependency-checking  - (NOT RECOMMENDED) ignore dependencies at removing packages 
      -kf, --keep-folders             - keep cloned project-folders, clean with \"sudo secpm clean\" 
      -s, --server                    - setting the git server (default is github.com) 
      -iu, --ignore-up-to-date        - install/update even if package is up to date
      
      -I                              = install
      -U                              = update
      -Ua                             = update all
      -R                              = remove

      > sudo secpm quiet [...]        - there will be no output from the installer scripts 

    *1 - Are you really sure? 
    *2 - Do you want to see the build file? 

  Examples: 
      sudo secpm install user:project               - installs user's project 
      sudo secpm remove user:project -ndc           - removes user's project, without checking if
                                                      it's a dependency of other packages or not 
      sudo secpm -s bitbucket.org ins user:project  - installs user's project from bitbucket.org
2: "Finished!"
3: "Updating %s's %s..."
4: "Removing %s's %s..."
5: "Installing %s's %s..."
6: "Installing local directory %s..."
7: "Option \"%s\" not found!"
8: "Syntax error!"
9: "Quiet mode activated."
10: |
  Wrong package name: %s
  
  This is a package name:  user:package
                           triploit:secpundo-pm
11: "Installed %d packages:"
12: |
  Error! Lock file /usr/share/secundo/lock.lck exists,
     so an instance of secpm is already running!
  >> If this is a bug, delete this file, but BE SURE! Remove it at your own risk!
13: "There was an error! Directory for the package-files not found!"
14: "Error deleting lock file \"%s\"!"
15: |
  ERROR AT: git clone https://%s/%s/%s.git %s
                
  Error! Check this out:
    - is git installed?
    - does the repository exist?
    - does the github-user exist?
    - are you root?
16: "There was an error! Directory /usr/share/secundo not found!"
17: "Cleaned %d objects."
18: "Do you want to see the build file?"
19: "Please type 'y' or 'n'! > "
20: "Ok."
21: "Are you really sure?"
22: "Ok. Abort."
23: "Error at cleaning with: %s %s"
24: "Fatal error: wget not found! Install wget!"
25: |
  Error: Installation file of %s's %s on server not found!

  Make sure:
  ... that it is a secundo package.
  ... that the repository exists.
26: "Save installer file to... %s"
27: "Error at installing pakage! Package has the wrong version!"
28: "Version %s needed!"
29: "Package Up-to-date. Skipping."
30: "Package Up-to-date. Reinstalling."
31: |
  Error at %s

  Check out if:
  ... is wget installed?
  ... do you have an internet connection?
  ... does the repository exists?
  ... is the project a SecPM package?
32: "Package %s:%s is Up-to-date. Skipping."
33: "Package %s:%s is Up-to-date. Added to be reinstalled..."
34: "There was an error! Directory for the package-files not found!"
35: "Search for existing package file ... %s"
36: "Found ... running script."
37: "Cancelled, finishing proces..."
38: "Error: Removing of %s:%s : Is a dependency of %s:%s!"
39: "This package is not installed!\n>> Skipping."
40: "ERROR: FATAL_ERROR: INSTALL-FILE (\"%s\") NOT FOUND!"
41: "There was an error! Directory for the package-files (/usr/share/secundo/pkg_files) not found!"
42: "Added dependency to install list: %s:%s v%s"
43: "TOKEN: ERROR: FALSE_TYPE_ERROR: %s"
44: "EXECUTOR: PUT_TOGETHER: DEPENDENCY %s: ERROR: FATAL_ERROR: Syntax error!"
45: "EXECUTOR: PUT_TOGETHER: FUNC %s: ERROR: FATAL_ERROR: Syntax error!"
46: "EXECUTOR: PUT_TOGETHER: ERROR: FATAL_ERROR: Syntax error!"
47: "EXECUTOR: PUT_TOGETHER: VERSION %s: ERROR: FATAL_ERROR: Syntax error!"
48: "EXECUTOR: PUT_TOGETHER: USER %s: ERROR: FATAL_ERROR: Syntax error!"
49: "EXECUTOR: PUT_TOGETHER: NAME %s: ERROR: FATAL_ERROR: Syntax error!"
50: "ERROR: LINE %d: FATAL_ERROR: Function %s not found!"
51: "Warning: Unable to open trust-file."
53: "Cleaning %s ..."
54: "Language file \"%s\" not found!"
55: "Language file was installed!"
56: "Info: Check if it is a SecPM package..."
57: "Info: Finished! It is."
58: "Info: Won't save installation file..."
)V0G0N");

            if (std::ifstream(path).is_open())
            {
                sentences = YAML::LoadFile(path);
            }
            else
            {
                std::cout << ">> Warning: language file " << path << " not found!" << std::endl;
                std::cout << ">> Using fallback..." << std::endl;
            } 
        }
    } Translation;
}

#endif