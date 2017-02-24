#ifndef GQI_HPP
#define GQI_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"

class Gqi : public Command
{
private:
    std::regex name = std::regex("^((G|g)(Q|q)(I|i))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        std::string var1 = args[0];
        std::string var2 = args[1];
        int nice;

        if (Variables.existsVariable(var1))
        {
            nice = 0;
            nice++;
        }
        else if (Registers.existsRegister(var1))
        {
            nice = 0;
            nice++;
        }
        else if (std::regex_match(var1, match, r_int))
        {
            nice = 0;
            nice++;
        }
        else
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": GQI: INVALID_ARGUMENT_1: \"" << var1 << "\"" << std::endl;
            exit(1);
        }

        if (Variables.existsVariable(var2))
        {
            nice++;
        }
        else if (Registers.existsRegister(var2))
        {
            nice++;
        }
        else if (std::regex_match(var1, match, r_int))
        {
            nice++;
        }
        else
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": GQI: INVALID_ARGUMENT_2: \"" << var2 << "\"" << std::endl;
            exit(1);
        }

        if (nice == 2)
        {
            Compiler.addLine("if ("+var1+" > "+var2+")\n\t\t*hx = 1;\n\telse\n\t\t*hx = 0;");
            nice = 0;
        }
        else
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": GQI: INVALID_ARGUMENTS: \"" << var1 << "\"" << "/\"" << var2 << "\"" << std::endl;
            exit(1);
        }
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
