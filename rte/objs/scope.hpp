#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <iostream>
#include <vector>
#include "variable.hpp"
#include "../runtime.hpp"

class Scope
{
private:
    std::vector<Variable> b_variables;
    std::string name;

public:
    Scope(std::string s)
    {
        name = s;
    }

    void clearAll()
    {
        b_variables.clear();
        b_variables = {};
    }

    std::string getName()
    {
        return name;
    }

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

    Variable getVariable(std::string name)
    {
        if (!existsVariable(name))
        {
            std::cout << "FATAL_ERROR: LINE " << Runtime.LineNumber << ": Variable " << name << " not found!" << std::endl;
            exit(0);
        }

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
};

#endif
