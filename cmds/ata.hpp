#ifndef ATA_HPP
#define ATA_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Ata : public Command // Add element To Array; ata array, x; ata array, "Hello World!" -> ['H','e','l','l','o',' ','W','o','r','l','d','!']
{
private:
    std::regex name = std::regex("((A|a)(T|t)(A|a))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::regex r_string = std::regex("(\"(?:(?!\").)*\"|(?:(?!\").)*)");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        // std::cout << "VAR!" << std::endl;
        std::string var = args[0];
		std::string val = args[1];

		if (Lists.existsList(args[0]))
		{
			if (std::regex_match(val, match, r_registers))
			{
				Compiler.addLine(var+".push_back(*"+val+");");
			}
			else if (std::regex_match(val, match, r_int))
			{
				Compiler.addLine(var+".push_back("+val+");");
			}
			else if (std::regex_match(val, match, r_variable))
			{
				if (Variables.existsVariable(val))
				{
					Compiler.addLine(var+".push_back(*"+val+");");
				}
				else
				{
					std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ATA: VARIABLE_NOT_FOUND: " << val << std::endl;
					exit(1);
				}
			}
			else if (std::regex_match(val, match, r_string))
			{
				Compiler.addCode("\n\tfor (int _int_sys_i_ = 0; _int_sys_i_ < std::string(\""+val+"\").size(); _int_sys_i_++)\n\t\t"+var+".push_back((int) std::string(\""+val+"\")[_int_sys_i_]);\n");
			}
			else
			{
				std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ATA: INVALID_VALUE: " << val << std::endl;
				exit(1);
			}
		}
		else
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ATA: ARRAY_NOT_FOUND: " << var << std::endl;
			exit(1);
		}
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
