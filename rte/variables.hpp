#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <iostream>
#include <vector>
#include "objs/variable.hpp"

class Variables
{
private:
    std::vector<Variable> b_variables;

public:
    bool existsVariable(std::string name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if (b_variables[i].getName() == name)
                return true;
        }

        return false;
    }

    bool existsRealVariable(std::string real_name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if (b_variables[i].getRealName() == real_name)
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
                b_variables.erase(b_variables.begin()+i);
            }
        }
    }

    Variable getVariable(std::string name)
    {
        for (int i = 0; i < b_variables.size(); i++)
        {
            if (b_variables[i].getName() == name)
                return b_variables[i];
        }

        return Variable("[DOESNT_EXIST:99]", "[DOESNT_EXIST:99]");
    }

    void addVariable(Variable v)
    {
        b_variables.push_back(v);
    }

} Variables;

#endif
