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

class Commands
{
private:
    std::vector<Command*> bin_commands;
    std::smatch s;

public:
    void initCommands()
    {
        bin_commands.push_back(new Push());
        bin_commands.push_back(new Pop());
        bin_commands.push_back(new Mov());
        bin_commands.push_back(new Outl());
        bin_commands.push_back(new Str());
        bin_commands.push_back(new Ptc());
        bin_commands.push_back(new Out());
        bin_commands.push_back(new Rts());
        bin_commands.push_back(new Jmp());
        bin_commands.push_back(new Jnn());
        bin_commands.push_back(new Jln());
        bin_commands.push_back(new Jgn());
        bin_commands.push_back(new Jqn());
        bin_commands.push_back(new Mod());
        bin_commands.push_back(new Add());
        bin_commands.push_back(new Sub());
        bin_commands.push_back(new Mul());
        bin_commands.push_back(new Hlt());
        bin_commands.push_back(new Return());
        bin_commands.push_back(new Gt());
        bin_commands.push_back(new Gnn());
        bin_commands.push_back(new Gln());
        bin_commands.push_back(new Gen());
        bin_commands.push_back(new Ggn());
        bin_commands.push_back(new Pushv());
        bin_commands.push_back(new Ptr());
        bin_commands.push_back(new Var());
        bin_commands.push_back(new Mvv());
        bin_commands.push_back(new Inp());
        bin_commands.push_back(new Eqi());
        bin_commands.push_back(new Nqi());
        bin_commands.push_back(new Gqi());
        bin_commands.push_back(new Lqi());
        bin_commands.push_back(new Arr());
        bin_commands.push_back(new Ata());
        bin_commands.push_back(new Aga());
        bin_commands.push_back(new Ags());
        bin_commands.push_back(new Asv());
        bin_commands.push_back(new Arl());
        bin_commands.push_back(new Asa());
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
