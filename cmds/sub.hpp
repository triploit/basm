#ifndef SUB_HPP
#define SUB_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Sub : public Command
{
private:
    std::regex name = std::regex("^((S|s)(U|u)(B|b))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (std::regex_match(args[0], match, r_int))
        {
            if (!Runtime.Compile)
                Registers.setRegister(args[1], Registers.getRegister(args[1]).getValue()-std::stoi(args[0]));
        }
        else if (std::regex_match(args[0], match, r_regs))
        {
            if (!Runtime.Compile)
                Registers.setRegister(args[1], Registers.getRegister(args[1]).getValue()-Registers.getRegister(args[0]).getValue());
        }

        Compiler.addLine(args[1]+" = "+args[1]+" - "+args[0]+";");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
