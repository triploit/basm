#ifndef MVV_HPP
#define MVV_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"

class Mvv : public Command
{
private:
    std::regex name = std::regex("^((M|m)(V|v)(V|v))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Variables.existsVariable(args[1]))
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": VARIABLE_NOT_FOUND: " << args[1] << std::endl;
            exit(1);
        }

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
