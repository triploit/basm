#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include <regex>

#include "objs/command.hpp"
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
    }

    void runCommand(std::string command, std::vector<std::string> args)
    {
        for (int i = 0; i < bin_commands.size(); i++)
        {
            if (std::regex_match(command, s, bin_commands[i]->getName()))
            {
                bin_commands[i]->runFunction(args);
            }
        }
    }
} Commands;

#endif
