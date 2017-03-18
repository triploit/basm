#ifndef ASA_HPP
#define ASA_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Asa : public Command // Set Array To Array; arr x, y; x = y
{
private:
    std::regex name = std::regex("((A|a)(S|s)(A|a))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::regex r_string = std::regex("\"(?:(?!\").)*\"");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        if (Runtime.Verbose)
            std::cout << "ASA " << args[0] << " " << args[1] << std::endl;
        std::string var = args[0];
		std::string o_var = args[1];

		if (Lists.existsList(var))
		{
			if (Lists.existsList(o_var))
            {
                Compiler.addLine(o_var+" = "+var+";");
            }
		}
		else
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": ASV: ARRAY_NOT_FOUND: " << var << std::endl;
			exit(1);
		}
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
