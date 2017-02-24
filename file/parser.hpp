// Befehle, mit ihren Argumenten, wenn sie denn welche haben, erkennen und ausführen

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include "tokenizer.hpp"
#include "../rte/commands.hpp"

class Parser
{
private:
    std::string command;
    std::vector<std::string> args;

public:
    Parser(std::string _command, std::vector<std::string> _args)
    {
        command = _command;
        args = _args;

        // std::cout << "[C] " << _command << std::endl;
        // std::cout << "[A] ";

        // for (int i = 0; i < _args.size(); i++)
        //     std::cout << _args[i];

        // std::cout << std::endl;
    }

    void setAll(std::string _command, std::vector<std::string> _args)
    {
        command = _command;
        args = _args;

        if (Runtime.Compile)
        {
             // std::cout << "[C] " << command << std::endl;
             // std::cout << "[A] ";

             // for (int i = 0; i < args.size(); i++)
            //       std::cout << args[i] << " ";

             // std::cout << std::endl;
        }
    }

    void clearAll()
    {
        command = "";
        args.clear();
    }

    Parser(){}

    void doParse()
    {
        Commands.runCommand(command, args);
    }
} Parser;

#endif
