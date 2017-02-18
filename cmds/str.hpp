#ifndef STR_HPP
#define STR_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Str : public Command
{
private:
    std::regex name = std::regex("^((S|s)(T|t)(R|r))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            Registers.setRegister(args[0], Runtime.peekStack());

        Compiler.addLine(args[0]+" = stack.top();");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
