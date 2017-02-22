#ifndef RTS_HPP
#define RTS_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Rts : public Command
{
private:
    std::regex name = std::regex("^((R|r)(T|t)(S|s))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            Runtime.pushStack(Registers.getRegister(args[0]).getValue());
        Compiler.addLine("stack.push(*"+args[0]+");");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
