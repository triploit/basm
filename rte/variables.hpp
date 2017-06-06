#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <iostream>
#include <vector>
#include "objs/variable.hpp"
#include "runtime.hpp"
#include "registers.hpp"

class Variables
{
private:
    std::vector<Variable> b_variables;

public:
    bool existsVariable(std::string name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if ((b_variables[i].getName() == name ||
                b_variables[i].getScope() == "_sys_public__SCOPE_") &&
                Runtime.M__M == b_variables[i].getScope())
                return true;
        }

        return false;
    }

    std::vector<Variable> getVariables()
    {
        return b_variables;
    }

    bool existsRealVariable(std::string real_name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if ((b_variables[i].getRealName() == real_name ||
                b_variables[i].getScope() == "_sys_public__SCOPE_") &&
                Runtime.M__M == b_variables[i].getScope())
                return true;
        }

        return false;
    }

    void clearAll()
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if (b_variables[i].getName() != "var_ax" &&
                b_variables[i].getName() != "var_bx" &&
                b_variables[i].getName() != "var_cx")
            {
                if (Runtime.Verbose)
                    std::cout << "[RTE] Erase Variable: " << b_variables[i].getName() << std::endl;

                b_variables.erase(b_variables.begin()+i);
            }
        }
    }

    Variable getVariable(std::string name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if ((b_variables[i].getName() == name ||
                b_variables[i].getScope() == "_sys_public__SCOPE_") &&
                Runtime.M__M == b_variables[i].getScope())
                return b_variables[i];
        }

        return Variable("[DOESNT_EXIST:99]", "[DOESNT_EXIST:99]", "[DOESNT_EXIST:99]");
    }

    void addVariable(Variable v)
    {
		if (Runtime.Verbose)
			std::cout << "[RTE] Add Variable (" << v.getScope() << "): " << v.getName() << std::endl;

		if (Runtime.nameDefined(v.getName()))
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": VARIABLE_CREATE: NAME_ALREADY_DEFINED: Name is already defined: " << v.getName() << std::endl;
			exit(1);
		}

	    b_variables.push_back(v);
		Runtime.defineName(v.getName());
    }

} Variables;

#endif
