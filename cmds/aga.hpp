#ifndef AGA_HPP
#define AGA_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Aga : public Command
{
private:
    std::regex name = std::regex("((A|a)(G|g)(A|a))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::regex r_string = std::regex("\"(?:(?!\").)*\"");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        // std::cout << "VAR!" << std::endl;
        std::string var = args[0];
		// int index = 0;
		std::string val = args[1];
		std::string o_var = args[2];

		if (Lists.existsList(var))
		{
			if (std::regex_match(val, match, r_registers))
			{val = "*"+val;}
			else if (std::regex_match(val, match, r_int))
			{}
			else if (std::regex_match(val, match, r_variable))
			{
				if (Variables.existsVariable(val))
				{val = "*"+val;}
				else
				{
					std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: VARIABLE_NOT_FOUND: " << val << std::endl;
					exit(1);
				}
			}
			else
			{
				std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: INVALID_VALUE: " << val << std::endl;
				exit(1);
			}

			// ======================================================================================================================

			if (std::regex_match(o_var, match, r_registers))
			{
				Compiler.addLine("*"+o_var+" = "+var+"["+val+"];");
			}
			else if (std::regex_match(o_var, match, r_variable))
			{
				if (Variables.existsVariable(o_var))
				{
					Compiler.addLine("*"+o_var+" = "+var+"["+val+"];");
				}
				else
				{
					std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: VARIABLE(2)_NOT_FOUND: " << val << std::endl;
					exit(1);
				}
			}
			else
			{
				std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: INVALID_VALUE(2): " << val << std::endl;
				exit(1);
			}
		}
		else
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: ARRAY_NOT_FOUND: " << var << std::endl;
			exit(1);
		}
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
