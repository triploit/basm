#include <iostream>
#include <regex>
#include <fstream>
#include <stdlib.h>

#include "file/file_read.hpp"
#include "file/file_parse.hpp"
#include "rte/compiler.hpp"

void help();

int main(int argc, char const *argv[])
{
    std::string inp;
    tri::string input;
    std::smatch s;

    Commands.initCommands();
    Registers.initRegisters();

    Tokenizer.clearAll();
    Parser.clearAll();

    Variables.addVariable(Variable("var_ax", "_r_var_ax"));
    Variables.addVariable(Variable("var_bx", "_r_var_bx"));
    Variables.addVariable(Variable("var_cx", "_r_var_cx"));
    Lists.addList(List("list_ax"));
    Lists.addList(List("list_bx"));
    Lists.addList(List("list_cx"));

    Compiler.addLineT("#include <iostream>");
    Compiler.addLineT("#include <stack>");
    Compiler.addLineT("#include <vector>");
    Compiler.addLineT("");
    Compiler.addLineT("int _r_a = 0;");
    Compiler.addLineT("int _r_b = 0;");
    Compiler.addLineT("int _r_c = 0;");
    Compiler.addLineT("int _r_d = 0;");
    Compiler.addLineT("int _r_e = 0;");
    Compiler.addLineT("int _r_f = 0;");
    Compiler.addLineT("int _r_g = 0;");
    Compiler.addLineT("int _r_h = 0;");
    Compiler.addLineT("int _r_var_ax = 0;");
    Compiler.addLineT("int _r_var_bx = 0;");
    Compiler.addLineT("int _r_var_cx = 0;");
    Compiler.addLineT("");
    Compiler.addLineT("int *ax = &_r_a;");
    Compiler.addLineT("int *bx = &_r_b;");
    Compiler.addLineT("int *cx = &_r_c;");
    Compiler.addLineT("int *dx = &_r_d;");
    Compiler.addLineT("int *ex = &_r_e;");
    Compiler.addLineT("int *fx = &_r_f;");
    Compiler.addLineT("int *gx = &_r_g;");
    Compiler.addLineT("int *hx = &_r_h;");
    Compiler.addLineT("int *var_ax = &_r_var_ax;");
    Compiler.addLineT("int *var_bx = &_r_var_bx;");
    Compiler.addLineT("int *var_cx = &_r_var_cx;");
    Compiler.addLineT("");
    Compiler.addLineT("std::stack<int> stack;");
    Compiler.addLineT("std::vector<int> list_ax;");
    Compiler.addLineT("std::vector<int> list_bx;");
    Compiler.addLineT("std::vector<int> list_cx;");
    Compiler.addLineT("std::string _str_sys_tmp_ = \"\";");
    Compiler.addLineT("");

    std::string file = "a.asm";
    std::string binary = "a.out";
    bool _static = false;

    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg[0] == '-')
        {
            if (arg[1] == 'o')
            {
                if ((i+1) >= argc)
                {
                    help();
                }

                binary = argv[i+1];
                i++;
                continue;
            }
            else if (arg[1] == 's')
            {
                if ((i+1) < argc && std::string(argv[i+1])[0] != '-')
                {
                    help();
                    std::cout << "Option: -s does not need a argument!" << std::endl;
                    return 0;
                }

                _static = true;
                continue;
            }
			else if (arg[1] == 'v')
			{
				Runtime.Verbose = true;
			}
            else if (arg[1] == '-')
            {
                if (arg == "--static")
                {
                    if ((i+1) < argc && std::string(argv[i+1])[0] != '-')
                    {
                        help();
                        return 0;
                    }

                    _static = true;
                    continue;
                }
                else if (arg == "--output")
                {
                    if ((i+1) >= argc)
                    {
                        help();
                    }

                    binary = argv[i+1];
                    i++;
                    continue;
                }
				else if (arg == "--verbose")
				{
					Runtime.Verbose = true;
				}
            }
            else
            {
                help();
                return 1;
            }
        }
        else
        {
            file = arg;
        }
    }

    if (argc == 1)
    {
        help();
        return 1;
    }

    Runtime.Compile = true;
    Compiler.COMPILE_STATIC = _static;

    Runtime.M_File = std::ifstream(file, std::ios::in);
    Runtime.M_Binary = binary;
    file_read(file);
    file_parse(file);

    if (!Labels.existsLabel("main"))
    {
        std::cout << "ERROR: MAIN_NOT_FOUND: Main Function not declared!" << std::endl;
        exit(1);
    }

    Compiler.compile(file, binary);
    return 0;
}

void help()
{
    std::cout << "BASM 0.1.5a Alpha\n\nUSAGE:\n\tbasm <file> ...\n" << 
std::endl;
    std::cout << "\t-o <file> : set binary output file name" << std::endl;
    std::cout << "\t-s        : static linking" << std::endl;
    std::cout << "\t-v        : verbose compiling" << std::endl;
    std::cout << "\nStatic Linking makes a standalone executable and does not need\n" <<
    "the GCC librarys. But it makes the executable bigger (for example: a non-static executable\n" <<
    "is 30 KB large but with static linking it would be 2 MB.)" << std::endl;
}
