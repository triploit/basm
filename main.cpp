#include <iostream>
#include <regex>
#include <fstream>
#include <stdlib.h>

#include "file/file_read.hpp"
#include "rte/compiler.hpp"

int main(int argc, char const *argv[])
{
    std::string inp;
    tri::string input;
    std::smatch s;

    Commands.initCommands();
    Registers.initRegisters();

    Tokenizer.clearAll();
    Parser.clearAll();
    Lexer Lexer;

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
    Compiler.addLineT("");
    Compiler.addLineT("int *ax = &_r_a;");
    Compiler.addLineT("int *bx = &_r_b;");
    Compiler.addLineT("int *cx = &_r_c;");
    Compiler.addLineT("int *dx = &_r_d;");
    Compiler.addLineT("int *ex = &_r_e;");
    Compiler.addLineT("int *fx = &_r_f;");
    Compiler.addLineT("int *gx = &_r_g;");
    Compiler.addLineT("int *hx = &_r_h;");
    Compiler.addLineT("");
    Compiler.addLineT("std::stack<int> stack;\n");

    if (argc == 4 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compile") == 0))
    {
        Runtime.Compile = true;
        Runtime.M_File = std::ifstream(argv[2], std::ios::in);
        // std::string binary;
        Runtime.M_Binary = argv[3];
        // std::string Runtime.M_Code;
        // std::string Runtime.M_Line;
        // std::string  Runtime.M__M = "[NOTH]";

        file_read();

        Compiler.addLine("return 0;");
        Compiler.addLineT("}");

        Compiler.compile(argv[2], argv[3]);
    }
    else if (argc == 5
            && (strcmp(argv[1], "-c") == 0 || strcmp(argv[2], "-c") == 0)
            && (strcmp(argv[2], "-s") == 0 || strcmp(argv[1], "-s") == 0))
    {
        Runtime.Compile = true;
        Compiler.COMPILE_STATIC = true;

        Runtime.M_File = std::ifstream(argv[3], std::ios::in);
        Runtime.M_Binary = argv[4];
        file_read();

        Compiler.addLine("return 0;");
        Compiler.addLineT("}");

        Compiler.compile(argv[3], argv[4]);

    }
    else
    {
        std::cout << "BASM 0.1.3 Alpha\n\nUSAGE:" << std::endl;
        std::cout << "\tNon-Static       basm -c <InputFile> <OutputFile>" << std::endl;
        std::cout << "\tStatic Linking:  basm -s -c <InputFile> <OutputFile>" << std::endl;
        std::cout << "\nStatic Linking makes a standalone executable and does not need\n" <<
        "the GCC librarys. But it makes the executable bigger (for example: a non-static executable\n" <<
        "is 30 KB large but with static linking it would be 2 MB.)" << std::endl;
    }

    return 0;
}
