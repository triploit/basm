#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <iostream>
#include <vector>

#include "objs/register.hpp"

class Registers
{
private:
    std::vector<Register> b_registers;

public:
    void initRegisters()
    {
        b_registers.push_back(Register("ax", 0));
        b_registers.push_back(Register("bx", 0));
        b_registers.push_back(Register("cx", 0));
        b_registers.push_back(Register("dx", 0));
        b_registers.push_back(Register("ex", 0));
        b_registers.push_back(Register("fx", 0));
        b_registers.push_back(Register("gx", 0));
        b_registers.push_back(Register("hx", 0));
    }

    void printRegisters()
    {
        for (int i = 0; i < b_registers.size(); i++)
        {
            std::cout << b_registers[i].getName() << ": " << b_registers[i].getValue();
            std::cout << std::endl;
        }
    }

    Register getRegister(std::string name)
    {
        for (int i = 0; i < b_registers.size(); i++)
        {
            if (b_registers[i].getName() == name)
                return b_registers[i];
        }

        return Register("[NL]", -999);
    }

    void setRegister(std::string name, int value)
    {
        for (int i = 0; i < b_registers.size(); i++)
        {
            if (b_registers[i].getName() == name)
            {
                b_registers[i].setValue(value);
                return;
            }
        }
    }
} Registers;

#endif
