#ifndef FILE_READ_HPP
#define FILE_READ_HPP

#include "../tstring.hpp"
#include "../rte/compiler.hpp"
#include "../rte/runtime.hpp"
#include "../rte/commands.hpp"
#include "../rte/registers.hpp"
#include "../rte/labels.hpp"
#include "../rte/files.hpp"

#include "lexer.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

void file_read(std::string __file)
{
    Lexer Lexer;
    std::ifstream _file(__file);
    // std::cout << "COMPILE: " << __file << std::endl;
	Files.addFile(File(__file));

    if (_file.is_open())
    {
        Runtime.LineNumber = 0;
        int i = 0;

        while (std::getline(_file, Runtime.M_Line))
        {
            Runtime.LineNumber++;
            tri::string s = Runtime.M_Line;
            s = s.trim();
            if (s.at(0) == '%')
            {
                if (s.at(1) == '%')
                {
                    std::string __afile = s.cxs().substr(2, s.length()-1);
					if (Runtime.Verbose)
			        	std::cout << "[INC] File: " << __afile << std::endl;

					if (Files.existsFile(__file))
					{
						if (!Files.getFile(__file).existsFile(__afile))
						{
		                    file_read(__afile);
		                    Runtime.M_Line = "";
							Files.addIncludeFile(__file, __afile);
							// Files.listIncludeFiles(__file);
						}
						else
						{
							std::cout << "[FILE] Ignore Include-File \"" << __afile << "\", file was already included to the file." << std::endl;
						}
					}
                }
                else
                {
                    std::string __afile = s.cxs().substr(1, s.length()-1);

					if (Runtime.Verbose)
			        	std::cout << "[INC] File: " << __afile << std::endl;

					#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
					    __afile = "C:\\basm\\" + __afile;
					#else
					   	__afile = "/usr/include/basm/" + __afile;
					#endif

					if (Files.existsFile(__file))
					{
						if (!Files.getFile(__file).existsFile(__afile))
						{
							file_read(__afile);
							Runtime.M_Line = "";
							Files.addIncludeFile(__file, __afile);
							// Files.listIncludeFiles(__file);
						}
						else
						{
							if (Runtime.Verbose)
					        	std::cout << "[FILE] Ignore Include-File \"" << __afile << "\", file was already included to the file." << std::endl;
						}
					}
                }
                continue;
            }
            else if (s.at(0) == '#')
            {
    			if (Runtime.Verbose)
    				std::cout << "[LEX] ignore line: " << Runtime.LineNumber << ": is a comment" << std::endl;
                continue;
            }

            Runtime.M_Code = Runtime.M_Code + Runtime.M_Line + ((char) 236);
            i = Runtime.M_Code.size();
            tri::string l = Runtime.M_Line;
            l = l.trim();

			if (Runtime.Verbose)
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
                            exit(1);
                        }
                        else
                        {
							if (Runtime.Verbose)
								std::cout << " OK." << std::endl;
                        }
                    }
                    else
                    {
						if (Runtime.Verbose)
							std::cout << " OK." << std::endl;
                    }
                    break;
                case 1:
                    std::cout << "ERROR: LINE " << Runtime.LineNumber << ": SYNTAX_ERROR: \"" << l.cxs() << "\"" << std::endl;
                    exit(1);
                    break;
                case 2:
                    std::cout << "ERROR: LINE " << Runtime.LineNumber << ": COMMAND_NOT_FOUND: \"" << l.cxs() << "\"" << std::endl;
                    exit(1);
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
            std::vector<tri::string> spl = l.split();

            if (l.cxs() == "" || l.length() == 0)
                continue;

            // std::cout << "AHA: " << spl[0].cxs() << "/" << spl[0].at(spl[0].length() - 1) << std::endl;

            if (spl[0].at(spl[0].length() - 1) == ':' && l.at(0) != '.')
            {
                l = spl[0];
                int argc = 0;

                if (spl.size() > 1)
                    argc = std::stoi(spl[1].replace("<", "").replace(">", "").cxs());

                // std::cout << "ADD LABEL: " << l.replace(":", "").cxs() << std::endl;
                Labels.addLabel(l.replace(":", "").cxs(), i, argc);

                Compiler.addLineT("int " + l.replace(":", "").cxs() + "();");
                Runtime.M__M = l.replace(":", "").cxs();
                Labels.setAktLabel(l.replace(":", "").cxs());
            }
            else if (l.at(l.length() - 1) == ':' && l.at(0) == '.')
            {
                Labels.addGoto(Goto(l.replace(".", "").replace(":", "").cxs(), i, Labels.getAktLabel()));
            }
        }

        // Runtime.LineNumber = 1;
        Labels.setAktLabel("");
        _file.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to open file " << __file << "\n";
        exit(1);
    }
}

#endif
