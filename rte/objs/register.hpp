// Datentyp Register
#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <iostream>
#include <vector>

class Register
{
private:
    int value;
    std::string name;
    std::string real_name;

public:
    std::string getName()
    {
        return name;
    }

    void setRealName(std::string rname)
    {
        real_name = rname;
    }

    std::string getRealName()
    {
        return real_name;
    }

    int getValue()
    {
        return value;
    }

    void setValue(int i)
    {
        value = i;
    }

    void setName(std::string _name)
    {
        name = _name;
    }

    Register(std::string _name, std::string _real_name, int _value)
    {
        value = _value;
        real_name = _real_name;
        name = _name;
    }
};

#endif
