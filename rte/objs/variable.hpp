#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <iostream>

class Variable
{
private:
    std::string name;
    std::string real_name;
    std::string scope;

public:
    Variable(std::string _name, std::string _real_name, std::string _scope)
    {
        name = _name;
        real_name = _real_name;
        scope = _scope;
    }

    std::string getRealName()
    {
        return real_name;
    }

    std::string getScope()
    {
        return scope;
    }

    void setScope(std::string _scope)
    {
        scope = _scope;
    }

    void setRealName(std::string _rname)
    {
        real_name = _rname;
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string _name)
    {
        name = _name;
    }
};

#endif
