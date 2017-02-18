// Code auseinandernehmen und Befehle in Vector mit ARGC und ARGV

#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <iostream>
#include <vector>
#include "lexer.hpp"

class Tokenizer
{
private:
    std::vector<std::string> args;
    std::string command;
    std::string code;

public:
    Tokenizer(std::string _code)
    {
        code = _code;
    }

    Tokenizer(){}

    void setCode(std::string _code)
    {
        code = _code;
    }

    std::string getCode()
    {
        return code;
    }

    int doTokenize()
    {
        Lexer l;

        if (code == "" || code.size() == 0)
        {
            std::cout << "[ MAIN ]:[ TOKENIZER ]: ERROR:" << std::endl;
            std::cout << "\tThere is no Code to tokenize!" << std::endl;
            return 1;
        }

            bool isstr = false;
            std::string tmp;
            int argc = 0;

            for (int i = 0; i < code.size() || code[i] == ';'; i++)
            {

                if (code[i] == '\"')
                {
                    if (isstr)
                        isstr = false;
                    else
                        isstr = true;

                    i++;
                }

                if (code[i] == '#' && !isstr)
                    break;

                if (!isstr)
                {
                    if (code[i] == ' ' || code[i] == ',' || code[i] == ';')
                    {
                        while(code[i+1] == ' ' || code[i+1] == ',')
                        {
                            i++;
                            // std::cout << "[IGN] \"" << code[i] << "\"" << std::endl;
                        }

                        if (argc == 0)
                        {
                            command = tmp;
                            // std::cout << "[T][C] " << tmp << std::endl;
                            tmp = "";
                            argc++;
                        }
                        else if (argc > 0)
                        {
                            if (tmp != "")
                                args.push_back(tmp);
                            // std::cout << "[T][A][" << argc << "] " << tmp << std::endl;
                            tmp = "";
                            argc++;
                        }
                    }
                    else
                    {
                        tmp += code[i];
                    }
                }
                else
                {
                    tmp += code[i];
                }
            }

        if (tmp != "")
        {
            if (argc == 0)
                command = tmp;
            else
                args.push_back(tmp);

        }

        return 0;
    }

    void clearAll()
    {
        code = "";
        args.clear();
        command = "";
    }

    std::vector<std::string> getArgs()
    {
        return args;
    }

    std::string getCommand()
    {
        return command;
    }

    // Spalte Code
    // Wenn erster Token kein Befehl ist, error,
    // sonnst weitergeben (return);

    // getArgs -> args
    // getCommand -> command
} Tokenizer;

#endif
