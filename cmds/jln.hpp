#ifndef JLN_HPP
#define JLN_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/labels.hpp"
#include "../rte/compiler.hpp"
#include "../rte/registers.hpp"

class Jln : public Command
{
private:
    std::regex name = std::regex("((J|j)(L|l)(N|n))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
        {
            if (Registers.getRegister("hx").getValue() < 0)
                Labels.gotoLabel(args[0], Labels.getI());
        }

        Compiler.addLine("\n\tif (hx < 0)\n\t\tfx = "+args[0]+"();\n");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
