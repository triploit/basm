#ifndef PUSH_HPP
#define PUSH_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Push : public Command
{
private:
    std::regex name = std::regex("^((P|p)(U|u)(S|s)(H|h))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (std::regex_match(args[0], match, r_int))
        {
            if (!Runtime.Compile)
                Runtime.pushStack(std::stoi(args[0]));

            Compiler.addLine("stack.push("+args[0]+");");
        }
        else if (std::regex_match(args[0], match, r_regs))
        {
            if (!Runtime.Compile)
                Runtime.pushStack(Registers.getRegister(args[0]).getValue());

            Compiler.addLine("stack.push(*"+args[0]+");");
        }
        else
        {
            for (int i = (args[0].size()-1); i >= 0; i--)
            {
                if (!Runtime.Compile)
                    Runtime.pushStack((int) args[0][i]);
            }

            Compiler.addLine("for (int _int_sys_i_ = std::string(\""+args[0]+"\").size(); _int_sys_i_ >= 0; _int_sys_i_--)");
            Compiler.addLine("\tstack.push((int) std::string(\""+args[0]+"\")[_int_sys_i_]);");
        }
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
