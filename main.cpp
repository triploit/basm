#include <iostream>
#include <regex>
#include <fstream>
#include <stdlib.h>

#include "tstring.hpp"
#include "rte/compiler.hpp"
#include "file/lexer.hpp"
#include "file/tokenizer.hpp"
#include "file/parser.hpp"
#include "rte/runtime.hpp"
#include "rte/commands.hpp"
#include "rte/registers.hpp"
#include "rte/labels.hpp"

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

    if (argc == 4 && strcmp(argv[1], "-c") == 0)
    {
        Runtime.Compile = true;
        Compiler.addLineT("#include <iostream>");
        Compiler.addLineT("#include <stack>");
        Compiler.addLineT("#include <vector>");
        Compiler.addLineT("");
        Compiler.addLineT("int ax = 0;");
        Compiler.addLineT("int bx = 0;");
        Compiler.addLineT("int cx = 0;");
        Compiler.addLineT("int dx = 0;");
        Compiler.addLineT("int ex = 0;");
        Compiler.addLineT("int fx = 0;");
        Compiler.addLineT("int gx = 0;");
        Compiler.addLineT("int hx = 0;");
        Compiler.addLineT("");
        Compiler.addLineT("std::stack<int> stack;\n");

        std::ifstream afile(argv[2], std::ios::in);
        std::string binary;
        binary = argv[3];
        std::string code;
        std::string line;
        std::string _m = "[NOTH]";

        if (afile.is_open())
        {
            int i = 0;
            while (std::getline(afile, line))
            {
                code = code + line + ((char) 236);
                i = code.size();
                tri::string l = line;
                l = l.trim();

                std::cout << "LINE " << Runtime.LineNumber << ": ";
                switch (Lexer.isNiceCommand(l.cxs()))
                {
                    case 0:
                        if (_m == "[NOTH]")
                        {
                            if (Runtime.CommandType != "FUNCTION" && Runtime.CommandType != "NOTHING")
                            {
                                std::cout << "ERROR: MEANING_ERROR: \"" << l.cxs() <<
                                "\" \n(Use Commands ONLY in Functions! There must be a main function!)" << std::endl;
                                return 1;
                            }
                            else
                            {
                                std::cout << " OK." << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << " OK." << std::endl;
                        }
                        break;
                    case 1:
                        std::cout << "ERROR: SYNTAX_ERROR: \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                    case 2:
                        std::cout << "ERROR: COMMAND_NOT_FOUND: \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                }

                std::string tmp = "";
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == '#')
                    {
                        // std::cout << "COMMAND: " << tmp << std::endl;
                        break;
                    }
                    else
                    {
                        tmp = tmp + line[i];
                    }
                }

                l = tmp;
                l = l.trim();

                if (l.at(l.length() - 1) == ':' && l.at(0) != '.')
                {
                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "();");
                    _m = l.replace(":", "").cxs();
                    // std::cout << "[L]:[" << (i) << "] " << l.replace(":", "").cxs() << std::endl;
                }

                Runtime.LineNumber++;
            }

            Runtime.LineNumber = 1;
            afile.close();
        }
        else
        {
            std::cerr << "ERROR: Unable to open file\n";
        }

        line = "";
        _m = "[NOTH]";

        for (int i = 0; i < code.size(); i++)
        {
            if (code[i] == ((char) 236))
            {
                // std::cout << Compiler.getCode();
                Tokenizer.clearAll();
                Parser.clearAll();
                tri::string l = line;
                l = l.trim();

                if (l.length() == 0)
                    continue;
                else if (l.cxs() == "(.r)")
                {
                    Compiler.addLine("\n\tstd::cout << \"AX=\" << ax << std::endl;");
                    Compiler.addLine("std::cout << \"BX=\" << bx << std::endl;");
                    Compiler.addLine("std::cout << \"CX=\" << cx << std::endl;");
                    Compiler.addLine("std::cout << \"DX=\" << dx << std::endl;");
                    Compiler.addLine("std::cout << \"EX=\" << ex << std::endl;");
                    Compiler.addLine("std::cout << \"FX=\" << fx << std::endl;");
                    Compiler.addLine("std::cout << \"GX=\" << gx << std::endl;");
                    Compiler.addLine("std::cout << \"HX=\" << hx << std::endl;\n");
                    line = "";
                    continue;
                }

                std::string tmp = "";
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == '#')
                    {
                        // std::cout << "COMMAND: " << tmp << std::endl;
                        break;
                    }
                    else
                    {
                        tmp = tmp + line[i];
                    }
                }

                l = tmp;
                l = l.trim();

                if (l.at(l.length() - 1) == ':' && l.at(0) != '.')
                {
                    if (_m != "[NOTH]")
                    {
                        Compiler.addLine("return 0;");
                        Compiler.addLineT("}\n");
                    }

                    // Compiler.addLineT(l.cxs());
                    _m = l.replace(":", "").cxs();
                    Labels.setAktLabel(_m);
                    std::cout << "[L]:[" << (i) << "] " << l.replace(":", "").cxs() << std::endl;

                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "()");
                    Compiler.addLineT("{");
                    line = "";
                }
                else if (l.at(l.length() - 1) == ':' && l.at(0) == '.')
                {
                    std::cout << "[LG]:[" << (i) << "] " << l.replace(":", "").replace(".", "").cxs() << std::endl;

                    Compiler.addLineT(l.replace(".", "").cxs());
                    Labels.addGoto(Goto(l.replace(".", "").replace(":", "").cxs(), i, Labels.getAktLabel()));
                    line = "";
                }
                else
                {
                    // std::cout << l.cxs() << "L? " <<  l.at(l.length()-1) << std::endl;
                    Tokenizer.setCode(l.cxs());
                    Tokenizer.doTokenize();
                    Parser.setAll(Tokenizer.getCommand(), Tokenizer.getArgs());
                    Parser.doParse();
                }

                Runtime.LineNumber++;
                line = "";
            }
            else
                line = line + code[i];
        }

        Compiler.addLine("return 0;");
        Compiler.addLineT("}");

        Compiler.compile(argv[2], argv[3]);
    }
    else
    {
        std::cout << "BASM 0.1.2 Alpha\n\nUSAGE:" << std::endl;
        std::cout << "\tbasm -c [InputFile] [OutputFile]" << std::endl;
    }

    return 0;
}
