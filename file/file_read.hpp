#ifndef FILE_READ_HPP
#define FILE_READ_HPP

#include "../tstring.hpp"
#include "../rte/compiler.hpp"
#include "../rte/runtime.hpp"
#include "../rte/commands.hpp"
#include "../rte/registers.hpp"
#include "../rte/labels.hpp"

#include "lexer.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

int file_read()
{
    Lexer Lexer;
    if (Runtime.M_File.is_open())
    {
        int i = 0;
        while (std::getline(Runtime.M_File, Runtime.M_Line))
        {
            Runtime.M_Code = Runtime.M_Code + Runtime.M_Line + ((char) 236);
            i = Runtime.M_Code.size();
            tri::string l = Runtime.M_Line;
            l = l.trim();

            std::cout << "[LEX] LINE " << Runtime.LineNumber << ": ";
            switch (Lexer.isNiceCommand(l.cxs()))
            {
                case 0:
                    if ( Runtime.M__M == "[NOTH]")
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
            for (int i = 0; i < Runtime.M_Line.size(); i++)
            {
                if (Runtime.M_Line[i] == '#')
                {
                    // std::cout << "COMMAND: " << tmp << std::endl;
                    break;
                }
                else
                {
                    tmp = tmp + Runtime.M_Line[i];
                }
            }

            l = tmp;
            l = l.trim();

            if (l.at(l.length() - 1) == ':' && l.at(0) != '.')
            {
                Labels.addLabel(l.replace(":", "").cxs(), i);
                Compiler.addLineT("int " + l.replace(":", "").cxs() + "();");
                 Runtime.M__M = l.replace(":", "").cxs();
                // std::cout << "[L]:[" << (i) << "] " << l.replace(":", "").cxs() << std::endl;
            }

            Runtime.LineNumber++;
        }

        if (!Labels.existsLabel("main"))
        {
            std::cout << "ERROR: MAIN_NOT_FOUND: Main Function not declared!" << std::endl;
            exit(1);
        }

        Runtime.LineNumber = 1;
        Runtime.M_File.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to open file\n";
    }

    Runtime.M_Line = "";
     Runtime.M__M = "[NOTH]";

    for (int i = 0; i < Runtime.M_Code.size(); i++)
    {
        if (Runtime.M_Code[i] == ((char) 236))
        {
            // std::cout << Compiler.getCode();
            Tokenizer.clearAll();
            Parser.clearAll();
            tri::string l = Runtime.M_Line;
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
                Runtime.M_Line = "";
                continue;
            }

            std::string tmp = "";
            for (int i = 0; i < Runtime.M_Line.size(); i++)
            {
                if (Runtime.M_Line[i] == '#')
                {
                    // std::cout << "COMMAND: " << tmp << std::endl;
                    break;
                }
                else
                {
                    tmp = tmp + Runtime.M_Line[i];
                }
            }

            l = tmp;
            l = l.trim();

            if (l.at(l.length() - 1) == ':' && l.at(0) != '.')
            {
                if ( Runtime.M__M != "[NOTH]")
                {
                    Compiler.addLine("return 0;");
                    Compiler.addLineT("}\n");
                }

                std::string mark = l.replace(":", "").cxs();
                // Compiler.addLineT(l.cxs());
                 Runtime.M__M = mark;
                Labels.setAktLabel( Runtime.M__M);
                std::cout << "[L]:[" << (i) << "] " << mark<< std::endl;

                Compiler.addLineT("int " + mark + "()");
                Compiler.addLineT("{");
                Runtime.M_Line = "";
            }
            else if (l.at(l.length() - 1) == ':' && l.at(0) == '.')
            {
                std::cout << "[LG]:[" << (i) << "] " << l.replace(":", "").replace(".", "").cxs() << std::endl;

                Compiler.addLineT(l.replace(".", "").cxs());
                Labels.addGoto(Goto(l.replace(".", "").replace(":", "").cxs(), i, Labels.getAktLabel()));
                Runtime.M_Line = "";
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
            Runtime.M_Line = "";
        }
        else
            Runtime.M_Line = Runtime.M_Line + Runtime.M_Code[i];
    }

}

#endif
