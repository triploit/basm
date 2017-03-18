#ifndef GT_HPP
#define GT_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/labels.hpp"
#include "../rte/compiler.hpp"
#include "../rte/registers.hpp"

class Gt : public Command // goto x
{
private:
    std::regex name = std::regex("((G|g)(T|t))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Labels.existsGoto(args[0]))
        {
            std::cout << "LINE " << Runtime.LineNumber << ": ERROR: GOTO_NOT_FOUND: Goto-Label " << args[0] << " existiert nicht!" << std::endl;
            exit(0);
        }

        Compiler.addLine("goto "+args[0]+";\n");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
