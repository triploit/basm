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
        b_registers.push_back(Register("ax", "_r_a", 0));
        b_registers.push_back(Register("bx", "_r_b", 0));
        b_registers.push_back(Register("cx", "_r_c", 0));
        b_registers.push_back(Register("dx", "_r_d", 0));
        b_registers.push_back(Register("ex", "_r_e", 0));
        b_registers.push_back(Register("fx", "_r_f", 0));
        b_registers.push_back(Register("gx", "_r_g", 0));
        b_registers.push_back(Register("hx", "_r_h", 0));
    }

    bool existsRegister(std::string name)
    {
        for (int i = 0; i < b_registers.size(); i++)
        {
            if (b_registers[i].getName() == name)
                return true;
        }
        return false;
    }

    bool existsRealRegister(std::string name)
    {
        for (int i = 0; i < b_registers.size(); i++)
        {
            if (b_registers[i].getRealName() == name)
                return true;
        }
        return false;
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

        return Register("[NL]", "[NL]", -999);
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
