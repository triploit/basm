#ifndef JQN_HPP
#define JQN_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/labels.hpp"
#include "../rte/compiler.hpp"
#include "../rte/registers.hpp"

class Jqn : public Command
{
private:
    std::regex name = std::regex("((J|j)(E|e)(N|n))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Labels.existsLabel(args[0]))
        {
            std::cout << "LINE " << Runtime.LineNumber << ": ERROR: (FUNCTION_)LABEL_NOT_FOUND: Label " << args[0] << " existiert nicht!" << std::endl;
            exit(0);
        }

        Compiler.addLine("\n\tif (hx == 0)\n\t\tfx = "+args[0]+"();\n");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
