// Syntaxpruefung

#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <regex>
#include "../tstring.hpp"
#include "../rte/runtime.hpp"

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
        { // function
                std::regex("(( *)(\\t*))*[A-Za-z0-9_]*:(( |\\t)*#.*|( |\\t)*)*")
        },
        { // goto-label
                std::regex("(( *)(\\t*))*\\.[A-Za-z0-9_]*:(( |\\t)*#.*|( |\\t)*)*")
        },
        { // mov
            std::regex("(( *)(\\t*))*((M|m)(O|o)(V|v)).*"),
            std::regex("(( *)(\\t*))*((M|m)(O|o)(V|v))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // push
            std::regex("(( *)(\\t*))*(((P|p)(U|u)(S|s)(H|h))|push).*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))(( *)(\\t*))[0-9]*(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h))(( *)(\\t*))\"(?:(?!\").)*\"(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // pop
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p)).*"),
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // str
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r)).*"),
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r))(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // rts
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s)).*"),
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s))(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // out
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)((?!(L|l))))|#.*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // outl
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l)).*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // ptc
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c)).*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jmp
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p)).*"),
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jnn
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jln
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jgn
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jqn
            std::regex("(( *)(\\t*))*((J|j)(E|e)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(E|e)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // add
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d)).*"),
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // sub
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b)).*"),
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // mul
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l)).*"),
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // div
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v)).*"),
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // mod
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d)).*"),
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),( *)(ax|bx|cx|dx|ex|fx|gx|hx)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // hlt
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t)).*"),
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // return
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n)).*"),
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gt
            std::regex("(( *)(\\t*))*((G|g)(T|t)).*"),
            std::regex("(( *)(\\t*))*((G|g)(T|t))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gnn
            std::regex("(( *)(\\t*))*((G|g)(N|n)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(N|n)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gln
            std::regex("(( *)(\\t*))*((G|g)(L|l)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(L|l)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // ggn
            std::regex("(( *)(\\t*))*((G|g)(G|g)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(G|g)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gqn
            std::regex("(( *)(\\t*))*((G|g)(E|e)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(E|e)(N|n))(( *)(\\t*))([A-Za-z0-9_]*)(;|)( |((( *)(\\t*))|)#.*)*")
        }
    };

    std::vector<std::string> COMMAND_NAME =
    {
        "NOTHING",
        "COMMENT",
        "FUNCTION",
        "GOTOLABEL",
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
        "jen",
        "add",
        "sub",
        "mul",
        "div",
        "mod",
        "hlt",
        "return",
        "gt",
        "gnn",
        "gln",
        "ggn",
        "gen",
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
                        Runtime.CommandType = COMMAND_NAME[i];
                        nice++;
                        return 0;
                    }
                }

                if (COMMANDS[i].size() == 1)
                {
                    if (std::regex_match(cmd, matches, COMMANDS[i][0]))
                    {
                        Runtime.CommandType = COMMAND_NAME[i];
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

};

#endif
