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

        if (afile.is_open())
        {
            int i = 0;
            while (std::getline(afile, line))
            {
                code = code + line + ((char) 236);
                i = code.size();
                tri::string l = line;
                l = l.trim();

                switch (Lexer.isNiceCommand(line))
                {
                    case 0:
                        std::cout << "LINE " << Runtime.LineNumber << ": OK." << std::endl;
                        break;
                    case 1:
                        std::cout << "ERROR: SYNTAX_ERROR: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                    case 2:
                        std::cout << "ERROR: COMMAND_NOT_FOUND: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
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

                if (l.at(l.length() - 1) == ':')
                {
                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "();");
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

        for (int i = 0; i < code.size(); i++)
        {
            if (code[i] == ((char) 236))
            {
                Tokenizer.clearAll();
                Parser.clearAll();
                tri::string l = line;
                l = l.trim();

                if (l.length() == 0)
                    continue;
                else if (l.cxs() == "(.r)")
                {
                    Registers.printRegisters();
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

                if (l.at(l.length() - 1) == ':')
                {
                    if (Labels.labelArrayIndex(l.replace(":", "").cxs()) != 0)
                        Compiler.addLineT("\treturn 0;\n}\n");
                    else
                        std::cout << l.replace(":", "").cxs() << " ] " << Labels.labelArrayIndex(l.replace(":", "").cxs()) << std::endl;

                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    // Compiler.addLineT(l.cxs());
                    std::cout << "[L]:[" << (i) << "] " << l.replace(":", "").cxs() << std::endl;

                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "()");
                    Compiler.addLineT("{");
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
    else if (argc == 3)
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

        std::ifstream afile(argv[1], std::ios::in);
        std::string binary;
        binary = argv[2];
        std::string code;
        std::string line;

        if (afile.is_open())
        {
            int i = 0;
            while (std::getline(afile, line))
            {
                code = code + line + ((char) 236);
                i = code.size();
                tri::string l = line;
                l = l.trim();

                switch (Lexer.isNiceCommand(l.cxs()))
                {
                    case 0:
                        // std::cout << " OK." << std::endl;
                        break;
                    case 1:
                        std::cout << "ERROR: SYNTAX_ERROR: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                    case 2:
                        std::cout << "ERROR: COMMAND_NOT_FOUND: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                }

                if (l.at(l.length() - 1) == ':')
                {
                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "();");
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

        for (int i = 0; i < code.size(); i++)
        {
            if (code[i] == ((char) 236))
            {
                Tokenizer.clearAll();
                Parser.clearAll();
                tri::string l = line;
                l = l.trim();

                if (l.length() == 0)
                    continue;
                else if (l.cxs() == "(.r)")
                {
                    Registers.printRegisters();
                    line = "";
                    continue;
                }

                if (l.at(l.length() - 1) == ':')
                {
                    if (Labels.labelArrayIndex(l.replace(":", "").cxs()) != 0)
                        Compiler.addLineT("\treturn 0;\n}\n");
                    else
                        std::cout << l.replace(":", "").cxs() << " ] " << Labels.labelArrayIndex(l.replace(":", "").cxs()) << std::endl;

                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    // Compiler.addLineT(l.cxs());
                    std::cout << "[L]:[" << (i) << "] " << l.replace(":", "").cxs() << std::endl;

                    Compiler.addLineT("int " + l.replace(":", "").cxs() + "()");
                    Compiler.addLineT("{");
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
    /*else if (argc == 2) // INTERPRETER =======================================================================================================
    {
        std::ifstream afile(argv[1], std::ios::in);
        std::string binary;
        binary = argv[3];
        std::string code;
        std::string line;

        if (afile.is_open())
        {
            int i = 0;
            while (std::getline(afile, line))
            {
                code = code + line + ((char) 236);
                i = code.size();
                tri::string l = line;
                l = l.trim();

                switch (Lexer.isNiceCommand(l.cxs()))
                {
                    case 0:
                        // std::cout << " OK." << std::endl;
                        break;
                    case 1:
                        std::cout << "ERROR: SYNTAX_ERROR: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                    case 2:
                        std::cout << "ERROR: COMMAND_NOT_FOUND: LINE " << Runtime.LineNumber << ": \"" << l.cxs() << "\"" << std::endl;
                        return 1;
                        break;
                }

                if (l.at(l.length() - 1) == ':')
                {
                    Labels.addLabel(l.replace(":", "").cxs(), i);
                    Compiler.addLineT(l.cxs());
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
        std::string lm = "";
        std::string m = "";

        for (int i = 0; i < code.size(); Labels.setI(Labels.getI() + 1))
        {
            std::cout << " [" << code[i] << ":" << i << "]" << std::endl;
            if ((i + 1) == code.size())
            {
                std::cout << "ENDE LM=" << Labels.getAktLabel() << " -> " << Labels.getLastLabel() << std::endl;
                if (Labels.getAktLabel() != "main" && Labels.getAktLabel() != "")
                {
                    Labels.setI(Labels.returnI());
                }

                line = "";
            }

            i = Labels.getI();

            if (code[i] == ((char) 236))
            {
                Tokenizer.clearAll();
                Parser.clearAll();
                tri::string l = line;
                l = l.trim();

                if (l.length() == 0)
                    continue;
                else if (l.cxs() == "(.r)")
                {
                    Registers.printRegisters();
                    line = "";
                    continue;
                }

                if (l.at(l.length() - 1) == ':')
                {
                    Labels.setAktLabel(l.cxs());
                    if (Labels.getLastLabel() != "main" && Labels.getLastLabel() != "")
                    {
                        std::cout << "JMP LM=" << Labels.getAktLabel() << " -> " << Labels.getLastLabel() << std::endl;
                        Labels.setI(Labels.returnI());
                    }

                    line = "";
                }
                else
                {
                    // std::cout << l.cxs() << "L? " <<  l.at(l.length()-1) << std::endl;
                    Tokenizer.setCode(l.cxs());
                    Tokenizer.doTokenize();
                    Parser.setAll(Tokenizer.getCommand(), Tokenizer.getArgs());
                    Parser.doParse();

                    Runtime.LineNumber++;
                    line = "";
                }
            }
            else
                line = line + code[i];
        }
    }*/
    else
    {
        std::cout << "BASM 0.1.1 Alpha\n\nUSAGE:" << std::endl;
        std::cout << "\tbasm -c [InputFile] [OutputFile]" << std::endl;
        std::cout << "\tbasm [InputFile] [OutputFile]" << std::endl;
        // std::cout << "\tbasm [InputFile]" << std::endl;
    }

    return 0;
}
