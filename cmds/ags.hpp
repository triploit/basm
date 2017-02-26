#ifndef AGS_HPP
#define AGS_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Ags : public Command
{
private:
    std::regex name = std::regex("((A|a)(G|g)(S|s))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
		// std::cout << "VAR!" << std::endl;
		std::string var = args[0];
        std::string o_var = args[1];

		if (!Lists.existsList(var))
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: ARRAY_NOT_FOUND: " << var << std::endl;
			exit(1);
		}

		if (std::regex_match(o_var, match, r_registers))
		{
			Compiler.addLine("*"+o_var+" = "+var+".size();");
		}
		else if (std::regex_match(o_var, match, r_variable))
		{
			if (Variables.existsVariable(o_var))
			{
				Compiler.addLine("*"+o_var+" = "+var+".size();");
			}
			else
			{
				std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ARL: VARIABLE_NOT_FOUND: " << o_var << std::endl;
				exit(1);
			}
		}
		else
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ARL: INVALID_VALUE: " << o_var << std::endl;
			exit(1);
		}
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
