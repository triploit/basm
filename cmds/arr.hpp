#ifndef ARR_HPP
#define ARR_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Arr : public Command
{
private:
    std::regex name = std::regex("((A|a)(R|r)(R|r))");
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
			List l(var);
			Lists.addList(l);

			Compiler.addLine("std::vector<int> "+var+";");
            // std::cout << "[V] New List: " << var << std::endl;
        }
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
