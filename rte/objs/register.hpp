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

public:
    std::string getName()
    {
        return name;
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

    Register(std::string _name, int _value)
    {
        value = _value;
        name = _name;
    }
};

#endif
