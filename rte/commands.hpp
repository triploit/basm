#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include <regex>

#include "objs/command.hpp"
#include "objs/label.hpp"
#include "labels.hpp"
#include "../cmds/push.hpp"
#include "../cmds/pop.hpp"
#include "../cmds/mov.hpp"
#include "../cmds/str.hpp"
#include "../cmds/rts.hpp"
#include "../cmds/out.hpp"
#include "../cmds/ptc.hpp"
#include "../cmds/outl.hpp"
#include "../cmds/jmp.hpp"
#include "../cmds/jln.hpp"
#include "../cmds/jnn.hpp"
#include "../cmds/jgn.hpp"
#include "../cmds/jqn.hpp"
#include "../cmds/add.hpp"
#include "../cmds/mul.hpp"
#include "../cmds/sub.hpp"
#include "../cmds/div.hpp"
#include "../cmds/mod.hpp"
#include "../cmds/hlt.hpp"
#include "../cmds/return.hpp"
#include "../cmds/gt.hpp"
#include "../cmds/gln.hpp"
#include "../cmds/gnn.hpp"
#include "../cmds/ggn.hpp"
#include "../cmds/gen.hpp"
#include "../cmds/var.hpp"
#include "../cmds/pushv.hpp"
#include "../cmds/ptr.hpp"
#include "../cmds/mvv.hpp"
#include "../cmds/inp.hpp"
#include "../cmds/eqi.hpp"
#include "../cmds/gqi.hpp"
#include "../cmds/lqi.hpp"
#include "../cmds/nqi.hpp"
#include "../cmds/arr.hpp"
#include "../cmds/ata.hpp"
#include "../cmds/aga.hpp"
#include "../cmds/ags.hpp"
#include "../cmds/asv.hpp"
#include "../cmds/arl.hpp"
#include "../cmds/asa.hpp"
#include "../cmds/rnd.hpp"

class Commands
{
private:
    std::vector<Command*> bin_commands;
    std::smatch s;

public:
	std::vector<Command*> getCommands()
	{
		return bin_commands;
	}

    void initCommands()
    {
        bin_commands.push_back(new Push());
		Runtime.defineName("push");
        bin_commands.push_back(new Pop());
		Runtime.defineName("pop");
        bin_commands.push_back(new Mov());
		Runtime.defineName("mov");
        bin_commands.push_back(new Outl());
		Runtime.defineName("outl");
        bin_commands.push_back(new Str());
		Runtime.defineName("str");
        bin_commands.push_back(new Ptc());
		Runtime.defineName("ptc");
        bin_commands.push_back(new Out());
		Runtime.defineName("out");
        bin_commands.push_back(new Rts());
		Runtime.defineName("rts");
        bin_commands.push_back(new Jmp());
		Runtime.defineName("jmp");
        bin_commands.push_back(new Jnn());
		Runtime.defineName("jnn");
        bin_commands.push_back(new Jln());
		Runtime.defineName("jln");
        bin_commands.push_back(new Jgn());
		Runtime.defineName("jgn");
        bin_commands.push_back(new Jqn());
		Runtime.defineName("jqn");
        bin_commands.push_back(new Mod());
		Runtime.defineName("mod");
        bin_commands.push_back(new Add());
		Runtime.defineName("add");
        bin_commands.push_back(new Sub());
		Runtime.defineName("sub");
        bin_commands.push_back(new Mul());
		Runtime.defineName("mul");
        bin_commands.push_back(new Hlt());
		Runtime.defineName("hlt");
        bin_commands.push_back(new Return());
		Runtime.defineName("return");
        bin_commands.push_back(new Gt());
		Runtime.defineName("gt");
        bin_commands.push_back(new Gnn());
		Runtime.defineName("gnn");
        bin_commands.push_back(new Gln());
		Runtime.defineName("gln");
        bin_commands.push_back(new Gen());
		Runtime.defineName("gen");
        bin_commands.push_back(new Ggn());
		Runtime.defineName("ggn");
        bin_commands.push_back(new Pushv());
		Runtime.defineName("pushv");
        bin_commands.push_back(new Ptr());
		Runtime.defineName("ptr");
        bin_commands.push_back(new Var());
		Runtime.defineName("var");
        bin_commands.push_back(new Mvv());
		Runtime.defineName("mvv");
        bin_commands.push_back(new Inp());
		Runtime.defineName("inp");
        bin_commands.push_back(new Eqi());
		Runtime.defineName("eqi");
        bin_commands.push_back(new Nqi());
		Runtime.defineName("nqi");
        bin_commands.push_back(new Gqi());
		Runtime.defineName("gqi");
        bin_commands.push_back(new Lqi());
		Runtime.defineName("lqi");
        bin_commands.push_back(new Arr());
		Runtime.defineName("arr");
        bin_commands.push_back(new Ata());
		Runtime.defineName("ata");
        bin_commands.push_back(new Aga());
		Runtime.defineName("aga");
        bin_commands.push_back(new Ags());
		Runtime.defineName("ags");
        bin_commands.push_back(new Asv());
		Runtime.defineName("asv");
        bin_commands.push_back(new Arl());
		Runtime.defineName("arl");
        bin_commands.push_back(new Asa());
		Runtime.defineName("asa");
        bin_commands.push_back(new Rnd());
		Runtime.defineName("rnd");
    }

    void runCommand(std::string command, std::vector<std::string> args)
    {
        if (Labels.existsLabel(command))
        {
            // std::cout << "AHA1! " << command << std::endl;

            if (Labels.getLabel(command).getArgCount() > 0)
            {
                // std::cout << "AHA2! " << command << std::endl;

                if (Labels.getLabel(command).getArgCount() == (args.size()))
                {
                    // std::cout << "AHA3! " << command << std::endl;
                    std::string lbl = command;
                    // std::cout << "BEG: " << lbl << std::endl;

                    for (int c = 0; c <= args.size(); c++)
                    {
                        if (Runtime.Verbose)
                            std::cout << "[RTE] PUSH-COMMAND: " << args[args.size()-1] << std::endl;
                        (new Push)->runFunction({args[args.size()-1]});
                        args.erase(args.end());
                    }

                    // std::cout << lbl << std::endl;
                    Compiler.addLine(lbl+"();\n");

                }
                else
                {
                    std::cout << "Error: INVALID_FUNCTION_CALL: Cant call function \"" << command << "\": To less/many arguments! (" << args.size() << "/" << Labels.getLabel(command).getArgCount() << ")" << std::endl;
                    exit(1);
                }
            }
            else
            {
                std::cout << "Error: INVALID_FUNCTION_CALL: Cant call function \"" << command << "\": No argument count in function definition!" << std::endl;
                exit(1);
            }
            return;
        }

        for (int i = 0; i < bin_commands.size(); i++)
        {
            if (std::regex_match(command, s, bin_commands[i]->getName()))
            {
                bin_commands[i]->runFunction(args);
                return;
            }
        }

        std::cout << "Error: COMMAND_NOT_FOUND: Command not found: " << command << std::endl;
        exit(1);
    }
} Commands;

#endif
