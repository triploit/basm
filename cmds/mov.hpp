#ifndef MOV_HPP
#define MOV_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Mov : public Command
{
private:
    std::regex name = std::regex("^((M|m)(O|o)(V|v))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (std::regex_match(args[0], match, r_int))
            Compiler.addLine("*"+args[1]+" = "+args[0]+";");
        else
            Compiler.addLine("*"+args[1]+" = *"+args[0]+";");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
