cmake_minimum_required(VERSION 3.9)
project(secundo_pm)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        secundo_pm
        lang/cmds/commands.hpp
        lang/obj/command.hpp
        lang/obj/function.hpp
        lang/obj/token.hpp
        lang/executor.hpp
        lang/functions.hpp
        lang/runtime.hpp
        lang/syntax.hpp
        lang/tokenizer.hpp
        pkg/ins.sc
        global.hpp
        installer.hpp
        lang.hpp
        main.cpp
        package.hpp
        tstring.hpp
        exec.hpp
        exec.cpp)
