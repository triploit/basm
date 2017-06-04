#ifndef FILE_LEX
#define FILE_LEX

#include <iostream>
#include <string>
#include <algorithm>

#include "../rte/runtime.hpp"
#include "../rte/compiler.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

void file_parse(std::string __file)
{
    Runtime.M_Line = "";
    Runtime.LineNumber = 0;
    Runtime.M__M = "[NOTH]";

    for (int i = 0; i < Runtime.M_Code.size(); i++)
    {
        if (Runtime.M_Code[i] == ((char) 236))
        {
            Runtime.LineNumber++;

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
                    break;
                }
                else
                {
                    tmp = tmp + Runtime.M_Line[i];
                }
            }

            l = tmp;
            l = l.trim();
            tri::string l2 = l;
            std::vector<tri::string> spl = l.split(' ');
            l = spl[0];
            int argc = 0;

            if (l.at(l.length() - 1) == ':' && l.at(0) != '.')
            {
                if ( Runtime.M__M != "[NOTH]")
                {
                    Compiler.addLine("return 0;");
                    Compiler.addLineT("}\n");
                }

                if (Runtime.Verbose)
                {
                    std::cout << "[RTE] Clearing Variables... New Scope " << l.cxs() << std::endl;
                    std::cout << "[RTE] " << Lists.getLists().size() << std::endl;
                }

                Variables.clearAll();
                Lists.clearAll();

                if (Runtime.Verbose)
                    std::cout << "[RTE] " << Lists.getLists().size() << std::endl;

                std::string mark = l.replace(":", "").cxs();
                // Compiler.addLineT(l.cxs());
                Runtime.M__M = mark;

                Labels.setAktLabel( Runtime.M__M);
                Runtime.AktScope = Runtime.M__M;

				if (Runtime.Verbose)
					std::cout << "[L]:[" << (i) << "/" << Runtime.LineNumber << "] " << mark << std::endl;

                Compiler.addLineT("int " + mark + "()");
                Compiler.addLineT("{");
                Runtime.M_Line = "";
            }
            else if (l.at(l.length() - 1) == ':' && l.at(0) == '.')
            {
				if (Runtime.Verbose)
					std::cout << "[LG]:[" << (i) << "/" << Runtime.LineNumber << "] " << l.replace(":", "").replace(".", "").cxs() << std::endl;

                Compiler.addLineT(l.replace(".", "").cxs());
                // Labels.addGoto(Goto(l.replace(".", "").replace(":", "").cxs(), i, Labels.getAktLabel()));
                Runtime.M_Line = "";
            }
            else
            {
                l = l2;
                // std::cout << l.cxs() << "L? " <<  l.cxs() << std::endl;
                Tokenizer.setCode(l.cxs());
                Tokenizer.doTokenize();
                Parser.setAll(Tokenizer.getCommand(), Tokenizer.getArgs());
                Parser.doParse();
            }

            Runtime.M_Line = "";
        }
        else
            Runtime.M_Line = Runtime.M_Line + Runtime.M_Code[i];
    }

    Compiler.addLine("return 0;");
    Compiler.addLineT("}");
}

#endif
