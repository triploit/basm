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
            std::regex("(( *)(\\t*))*((M|m)(O|o)(V|v))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // push
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h)((?!(V|v)))).*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h)((?!(V|v))))( |\\t)(( *)(\\t*))[0-9]*(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h)((?!(V|v))))( |\\t)(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(U|u)(S|s)(H|h)((?!(V|v))))( |\\t)(( *)(\\t*))\"(?:(?!\").)*\"(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // pop
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p)).*"),
            std::regex("(( *)(\\t*))*((P|p)(O|o)(P|p))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // str
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r)).*"),
            std::regex("(( *)(\\t*))*((S|s)(T|t)(R|r))( |\\t)(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // rts
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s)).*"),
            std::regex("(( *)(\\t*))*((R|r)(T|t)(S|s))( |\\t)(( *)(\\t*))(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // out
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)((?!(L|l))))|#.*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // outl
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l)).*"),
            std::regex("(( *)(\\t*))*((O|o)(U|u)(T|t)(L|l))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // ptc
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c)).*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(C|c))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jmp
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p)).*"),
            std::regex("(( *)(\\t*))*((J|j)(M|m)(P|p))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jnn
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(N|n)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jln
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(L|l)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jgn
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(G|g)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // jqn
            std::regex("(( *)(\\t*))*((J|j)(E|e)(N|n)).*"),
            std::regex("(( *)(\\t*))*((J|j)(E|e)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // add
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d)).*"),
            std::regex("(( *)(\\t*))*((A|a)(D|d)(D|d))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // sub
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b)).*"),
            std::regex("(( *)(\\t*))*((S|s)(U|u)(B|b))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // mul
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l)).*"),
            std::regex("(( *)(\\t*))*((M|m)(U|u)(L|l))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // div
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v)).*"),
            std::regex("(( *)(\\t*))*((D|d)(I|i)(V|v))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // mod
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d)).*"),
            std::regex("(( *)(\\t*))*((M|m)(O|o)(D|d))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)(ax|bx|cx|dx|ex|fx|gx|hx)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // hlt
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t)).*"),
            std::regex("(( *)(\\t*))*((H|h)(L|l)(T|t))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // return
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n)).*"),
            std::regex("(( *)(\\t*))*((R|r)(E|e)(T|t)(U|u)(R|r)(N|n))(( *)(\\t*))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gt
            std::regex("(( *)(\\t*))*((G|g)(T|t)).*"),
            std::regex("(( *)(\\t*))*((G|g)(T|t))(( *)( |\\t)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gnn
            std::regex("(( *)(\\t*))*((G|g)(N|n)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(N|n)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gln
            std::regex("(( *)(\\t*))*((G|g)(L|l)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(L|l)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // ggn
            std::regex("(( *)(\\t*))*((G|g)(G|g)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(G|g)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gqn
            std::regex("(( *)(\\t*))*((G|g)(E|e)(N|n)).*"),
            std::regex("(( *)(\\t*))*((G|g)(E|e)(N|n))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // ptr
            std::regex("(( *)(\\t*))*((P|p)(T|t)(R|r)).*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(R|r))( |\\t)(( *)(\\t*))(([A-Za-z0-9_]*)|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)([0-9]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(R|r))( |\\t)(( *)(\\t*))(([A-Za-z0-9_]*)|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*"),
            std::regex("(( *)(\\t*))*((P|p)(T|t)(R|r))( |\\t)(( *)(\\t*))(([A-Za-z0-9_]*)|(ax|bx|cx|dx|ex|fx|gx|hx)),((( *)(\\t*))|)0x([0-9a-fA-F]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // var
            std::regex("(( *)(\\t*))*((V|v)(A|a)(R|r)).*"),
            std::regex("(( *)(\\t*))*((V|v)(A|a)(R|r))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // pushv
            std::regex("(( *)(\\t*))*(((P|p)(U|u)(S|s)(H|h)(V|v))).*"),
            std::regex("(( *)(\\t*))*(((P|p)(U|u)(S|s)(H|h)(V|v)))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))*(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // mvv
            std::regex("(( *)(\\t*))*((M|m)(V|v)(V|v)).*"),
            std::regex("(( *)(\\t*))*((M|m)(V|v)(V|v))( |\\t)(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)),(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // inp
            std::regex("(( *)(\\t*))*((I|i)(N|n)(P|p)).*"),
            std::regex("(( *)(\\t*))*((I|i)(N|n)(P|p))(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // eqi
            std::regex("(( *)(\\t*))*((E|e)(Q|q)(I|i)).*"),
            std::regex("(( *)(\\t*))*((E|e)(Q|q)(I|i))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // gqi
            std::regex("(( *)(\\t*))*((G|g)(Q|q)(I|i)).*"),
            std::regex("(( *)(\\t*))*((G|g)(Q|q)(I|i))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // lqi
            std::regex("(( *)(\\t*))*((L|l)(Q|q)(I|i)).*"),
            std::regex("(( *)(\\t*))*((L|l)(Q|q)(I|i))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // nqi
            std::regex("(( *)(\\t*))*((N|n)(Q|q)(I|i)).*"),
            std::regex("(( *)(\\t*))*((N|n)(Q|q)(I|i))(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
		{ // arr
            std::regex("(( *)(\\t*))*((A|a)(R|r)(R|r)).*"),
            std::regex("(( *)(\\t*))*((A|a)(R|r)(R|r))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
		},
		{ // ata
			std::regex("(( *)(\\t*))*((A|a)(T|t)(A|a)).*"),
			std::regex("(( *)(\\t*))*((A|a)(T|t)(A|a))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)|(\"(?:(?!\").)*\"))(;|)( |((( *)(\\t*))|)#.*)*")
		},
		{ // arl
			std::regex("(( *)(\\t*))*((A|a)(R|r)(L|l)).*"),
			std::regex("(( *)(\\t*))*((A|a)(R|r)(L|l))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
		},
		{ // ags
			std::regex("(( *)(\\t*))*((A|a)(G|g)(S|s)).*"),
			std::regex("(( *)(\\t*))*((A|a)(G|g)(S|s))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))((ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
		},
        { // aga
            std::regex("(( *)(\\t*))*((A|a)(G|g)(A|a)).*"),
            std::regex("(( *)(\\t*))*((A|a)(G|g)(A|a))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))((ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // asv
            std::regex("(( *)(\\t*))*((A|a)(S|s)(V|v)).*"),
            std::regex("(( *)(\\t*))*((A|a)(S|s)(V|v))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))([0-9]*|(ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*)),(( *)(\\t*))((ax|bx|cx|dx|ex|fx|gx|hx)|([A-Za-z0-9_]*))(;|)( |((( *)(\\t*))|)#.*)*")
        },
        { // asa
            std::regex("(( *)(\\t*))*((A|a)(S|s)(A|a)).*"),
            std::regex("(( *)(\\t*))*((A|a)(S|s)(A|a))( |\\t)(( *)(\\t*))([A-Za-z0-9_]*),(( *)(\\t*))([A-Za-z0-9_]*)(( *)(\\t*))(;|)( |((( *)(\\t*))|)#.*)*")
        }
    };

    std::vector<std::string> COMMAND_NAME =
    {
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
        "ptr",
        "var",
        "pushv",
        "mvv",
        "inp",
        "eqi",
        "gqi",
        "lqi",
        "nqi",
        "arr",
        "ata",
        "arl",
        "ags",
        "aga",
        "asv",
        "asa",
        "asa"
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
