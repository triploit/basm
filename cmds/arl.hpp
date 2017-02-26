#ifndef ARL_HPP
#define ARL_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Arl : public Command
{
private:
    std::regex name = std::regex("((A|a)(R|r)(L|l))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        // std::cout << "VAR!" << std::endl;
		std::string var = args[0];
        std::string val = args[1];

		if (!Lists.existsList(var))
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": AGA: ARRAY_NOT_FOUND: " << var << std::endl;
			exit(1);
		}

		if (std::regex_match(val, match, r_registers))
		{
			Compiler.addLine("\n\tfor (int _int_sys_i_ = 0; _int_sys_i_ < *"+val+"; _int_sys_i_++)\n\t\t"+var+".erase("+var+".end()-1);\n");
		}
		else if (std::regex_match(val, match, r_int))
		{
			Compiler.addLine("\n\tfor (int _int_sys_i_ = 0; _int_sys_i_ < "+val+"; _int_sys_i_++)\n\t\t"+var+".erase("+var+".end()-1);\n");
		}
		else if (std::regex_match(val, match, r_variable))
		{
			if (Variables.existsVariable(val))
			{
				Compiler.addLine("\n\tfor (int _int_sys_i_ = 0; _int_sys_i_ < *"+val+"; _int_sys_i_++)\n\t\t"+var+".erase("+var+".end()-1);\n");
			}
			else
			{
				std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ARL: VARIABLE_NOT_FOUND: " << val << std::endl;
				exit(1);
			}
		}
		else
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ARL: INVALID_VALUE: " << val << std::endl;
			exit(1);
		}
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
