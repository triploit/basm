// Syntaxpruefung

#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <regex>
#include "../tstring.hpp"

class Lexer
{
private:
    // std::regex CMD_MOV_BASE = std::regex("[Mm][Oo][Vv]");
    // std::regex CMD_MOV_INT = std::regex("[Mm][Oo][Vv] [0-9]*, (ax|bx|cx);");
    // std::regex CMD_MOV_STR = std::regex("[Mm][Oo][Vv] \"(?:(?!\").)*\", (ax|bx|cx);");

    std::vector<std::vector<std::regex>> COMMANDS =
    {
        { // nothing
            std::regex("")
        },
        { // comment
                std::regex("( *)#.*")
        },
        { // Label
                std::regex("[A-Za-z0-9_]*:(( |\\t)*#.*|( |\t)*)")
        },
        { // mov
            std::regex("(( *)(\\t*))*((M|m)(O|o)(V|v)).*"),
            std::regex("(( *)(\\t*))*((M|m)(O|o)(V|v))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // push
            std::regex("(( *)(\\t*))*(((P|p)(U|u)(S|s)(H|h))|push).*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))( *)[0-9]*(;|)( |( *|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))( *)\"(?:(?!\").)*\"(;|)( |( *|)#.*)*")
        },
        { // pop
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p)).*"),
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p))(;|)( |( *|)#.*)*")
        },
        { // str
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r)).*"),
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r))( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // rts
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s)).*"),
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s))( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // out
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)((?!(L|l))))|#.*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t))(;|)( |( *|)#.*)*")
        },
        { // outl
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l)).*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l))(;|)( |( *|)#.*)*")
        },
        { // ptc
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c)).*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c))(;|)( |( *|)#.*)*")
        },
        { // jmp
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p)).*"),
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p))( *)([A-Za-z0-9_]*)(;|)( |( *|)#.*)*")
        },
        { // jnn
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n))( *)([A-Za-z0-9_]*)(;|)( |( *|)#.*)*")
        },
        { // jln
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n))( *)([A-Za-z0-9_]*)(;|)( |( *|)#.*)*")
        },
        { // jgn
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n))( *)([A-Za-z0-9_]*)(;|)( |( *|)#.*)*")
        },
        { // jqn
            std::regex("(( *)(\\t*))*((J|j)(Q|q)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(Q|q)(N|n))( *)([A-Za-z0-9_]*)(;|)( |( *|)#.*)*")
        },
        { // add
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d)).*"),
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // sub
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b)).*"),
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // mul
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l)).*"),
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // div
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v)).*"),
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // mod
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d)).*"),
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d))( *)([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |( *|)#.*)*")
        },
        { // hlt
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t)).*"),
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t))(;|)( |( *|)#.*)*")
        },
        { // return
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n)).*"),
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n))( *)(;|)( |( *|)#.*)*")
        }
    };

    std::vector<std::string> COMMAND_NAME =
    {
        "mov",
        "push",
        "pop",
        "str",
        "rts",
        "out",
        "outl",
        "ptc",
        "jmp",
        "jnn",
        "jln",
        "jgn",
        "jqn",
        "add",
        "sub",
        "mul",
        "div",
        "mod",
        "hlt"
    };

public:
    int isNiceCommand(tri::string command)
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
                        nice++;
                        return 0;
                    }
                }

                if (COMMANDS[i].size() == 1)
                {
                    if (std::regex_match(cmd, matches, COMMANDS[i][0]))
                    {
                        nice++;
                        return 0;
                    }
                }

                return 1;
            }
            else
            {
                    std::cout << "\"" << cmd << "\" != \"" << matches.str() << "\"" << std::endl;
            }
        }

        return 2;
    }

};

#endif
