#ifndef JMP_HPP
#define JMP_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/labels.hpp"
#include "../rte/compiler.hpp"

class Jmp : public Command
{
private:
    std::regex name = std::regex("((J|j)(M|m)(P|p))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            Labels.gotoLabel(args[0], Labels.getI());

        Compiler.addLine("fx = "+args[0]+"();");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
