#ifndef ADD_HPP
#define ADD_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Add : public Command // add x to y; add x, y
{
private:
    std::regex name = std::regex("^((A|a)(D|d)(D|d))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            return;

        if (Lists.existsList(args[0]) ||
            Lists.existsList(args[1]) ||
            std::regex_match(args[1], match, r_int))
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ADD: WRONG_TYPE: Field \"" << args[0] << "\" has the wrong type!" << std::endl;
        }

        if ((!Registers.existsRegister(args[0]) && !Variables.existsVariable(args[0])) &&
            !std::regex_match(args[0], match, r_int))
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ADD: XYZ_NOT_FOUND: Variable/Register \"" << args[0] << "\" doesn't exist!" << std::endl;
            exit(1);
        }

        if (!Registers.existsRegister(args[1]) && !Variables.existsVariable(args[1]))
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ADD: XYZ_NOT_FOUND: Variable/Register \"" << args[1] << "\" doesn't exist!" << std::endl;
            exit(1);
        }

        if (std::regex_match(args[0], match, r_int))
            Compiler.addLine("*"+args[1]+" = *"+args[1]+" + "+args[0]+";");
        else
            Compiler.addLine("*"+args[1]+" = *"+args[1]+" + *"+args[0]+";");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
