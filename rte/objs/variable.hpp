#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <iostream>

class Variable
{
private:
    std::string name;
    std::string real_name;

public:
    Variable(std::string _name, std::string _real_name)
    {
        name = _name;
        real_name = _real_name;
    }

    std::string getRealName()
    {
        return real_name;
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
