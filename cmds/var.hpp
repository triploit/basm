#ifndef VAR_HPP
#define VAR_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Var : public Command
{
private:
    std::regex name = std::regex("((V|v)(A|a)(R|r))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        // std::cout << "VAR!" << std::endl;
        std::string var = args[0];

        if (Variables.existsVariable(var) || Variables.existsRealVariable(var)
            || Registers.existsRegister(var) || Registers.existsRealRegister(var)
			|| Lists.existsList(var))
        {
            std::cout << "ERROR: LINE " << Runtime.LineNumber << ": INVALID_VARIABLE_NAME: \"" << var << "\": Variable/Register already exists!" << std::endl;
            exit(1);
        }
        else
        {
            Compiler.addLine("int __realINT_"+var+";");
            Compiler.addLine("int *"+var+" = &__realINT_"+var+";");
            Variables.addVariable(Variable(var, std::string("__realINT_"+var)));
            // std::cout << "[V] New Variable: " << var << "::" << std::string("__realINT_"+var) << std::endl;
        }
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
